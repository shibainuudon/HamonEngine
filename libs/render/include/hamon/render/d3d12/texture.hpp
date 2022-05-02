/**
 *	@file	texture.hpp
 *
 *	@brief	Texture
 */

#ifndef HAMON_RENDER_D3D12_TEXTURE_HPP
#define HAMON_RENDER_D3D12_TEXTURE_HPP

#include <hamon/render/texture.hpp>
#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/d3d12/device.hpp>
#include <hamon/render/d3d12/command_allocator.hpp>
#include <hamon/render/d3d12/command_list.hpp>
#include <hamon/render/d3d12/command_queue.hpp>
#include <hamon/render/d3d12/fence.hpp>
#include <hamon/render/d3d12/texture_format.hpp>
#include <hamon/render/d3d12/resource.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class Texture
{
private:
	static void MemcpySubresource(
		::D3D12_MEMCPY_DEST const& dst,
		::D3D12_SUBRESOURCE_DATA const& src,
		::UINT64 row_size_in_bytes,
		::UINT num_rows,
		::UINT num_slices)
	{
		for (::UINT z = 0; z < num_slices; ++z)
		{
			auto dst_slice = static_cast<std::uint8_t*>(dst.pData) + dst.SlicePitch * z;
			auto src_slice = static_cast<std::uint8_t const*>(src.pData) + src.SlicePitch * z;
			for (::UINT y = 0; y < num_rows; ++y)
			{
				std::memcpy(
					dst_slice + dst.RowPitch * y,
					src_slice + src.RowPitch * y,
					row_size_in_bytes);
			}
		}
	}

public:
	explicit Texture(
		d3d12::Device* device,
		d3d12::CommandAllocator* command_allocator,
		d3d12::CommandList* command_list,
		d3d12::CommandQueue* command_queue,
		d3d12::Fence* fence,
		render::Texture const& texture)
	{
		::D3D12_HEAP_PROPERTIES props{};
		props.Type                 = D3D12_HEAP_TYPE_DEFAULT;
		props.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		props.CreationNodeMask     = 1;
		props.VisibleNodeMask      = 1;

		::D3D12_RESOURCE_DESC desc{};
		desc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		desc.Alignment          = 0;
		desc.Width              = texture.GetWidth();
		desc.Height             = texture.GetHeight();
		desc.DepthOrArraySize   = 1;
		desc.MipLevels          = static_cast<::UINT16>(texture.GetMipmapCount());
		desc.Format             = d3d12::TextureFormat(texture.GetFormat());
		desc.SampleDesc.Count   = 1;
		desc.SampleDesc.Quality = 0;
		desc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		desc.Flags              = D3D12_RESOURCE_FLAG_NONE;

		m_resource = device->CreateCommittedResource(
			&props,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr);

		auto const num_subresources = texture.GetMipmapCount();
		std::vector<::D3D12_PLACED_SUBRESOURCE_FOOTPRINT> footprints(num_subresources);
		std::vector<::UINT> num_rows(num_subresources);
		std::vector<::UINT64> row_size_in_bytes(num_subresources);
		::UINT64 required_size = 0;
		device->GetCopyableFootprints(
			&desc,
			0,
			num_subresources,
			0,
			footprints.data(),
			num_rows.data(),
			row_size_in_bytes.data(),
			&required_size);

		d3d12::Resource intermediate_resource(device, required_size, nullptr);
		{
			auto dst = static_cast<std::uint8_t*>(intermediate_resource.Map(0, nullptr));

			auto const format = texture.GetFormat();
			auto width = texture.GetWidth();
			auto height = texture.GetHeight();
			auto src = static_cast<std::uint8_t const*>(texture.GetData());
			for (std::uint32_t i = 0; i < num_subresources; ++i)
			{
				::D3D12_SUBRESOURCE_DATA src_data{};
				src_data.pData = src;
				src_data.RowPitch = GetBytesPerPixel(format) * width;
				src_data.SlicePitch = src_data.RowPitch * height;

				::D3D12_MEMCPY_DEST dst_data{};
				dst_data.pData = dst + footprints[i].Offset;
				dst_data.RowPitch = footprints[i].Footprint.RowPitch;
				dst_data.SlicePitch = dst_data.RowPitch * num_rows[i];

				MemcpySubresource(
					dst_data,
					src_data,
					row_size_in_bytes[i],
					num_rows[i],
					footprints[i].Footprint.Depth);

				src += GetSizeInBytes(format, width, height);
				width  = std::max(width  / 2, 1u);
				height = std::max(height / 2, 1u);
			}

			intermediate_resource.Unmap(0, nullptr);
		}

		command_allocator->Reset();
		command_list->Reset(command_allocator);

		for (std::uint32_t i = 0; i < num_subresources; ++i)
		{
			::D3D12_TEXTURE_COPY_LOCATION dst{};
			dst.pResource        = m_resource.Get();
			dst.Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
			dst.SubresourceIndex = i;

			::D3D12_TEXTURE_COPY_LOCATION src{};
			src.pResource        = intermediate_resource.Get();
			src.Type             = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
			src.PlacedFootprint  = footprints[i];

			command_list->CopyTextureRegion(
				&dst,
				0,
				0,
				0,
				&src,
				nullptr);
		}

		command_list->Close();
		command_queue->ExecuteCommandList(command_list);
		fence->WaitForGpu(command_queue, 0);
	}

	::ID3D12Resource1* GetResource(void) const
	{
		return m_resource.Get();
	}

	::D3D12_SHADER_RESOURCE_VIEW_DESC GetShaderResourceViewDesc(void) const
	{
		auto const desc = m_resource->GetDesc();

		::D3D12_SHADER_RESOURCE_VIEW_DESC srv_desc;
		srv_desc.Format = desc.Format;
		srv_desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srv_desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srv_desc.Texture2D.MipLevels = desc.MipLevels;
		srv_desc.Texture2D.MostDetailedMip = 0;
		srv_desc.Texture2D.PlaneSlice = 0;
		srv_desc.Texture2D.ResourceMinLODClamp = 0;

		return srv_desc;
	}

private:
	ComPtr<::ID3D12Resource1>	m_resource;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_TEXTURE_HPP

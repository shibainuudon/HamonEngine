/**
 *	@file	input_layout.hpp
 *
 *	@brief	InputLayout
 */

#ifndef HAMON_RENDER_D3D12_INPUT_LAYOUT_HPP
#define HAMON_RENDER_D3D12_INPUT_LAYOUT_HPP

#include <hamon/render/d3d/d3d12.hpp>
#include <hamon/render/vertex_layout.hpp>
//#include <hamon/render/d3d12/device.hpp>
//#include <hamon/render/d3d/throw_if_failed.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d12
{

class InputLayout
{
public:
	explicit InputLayout(render::VertexLayout const& vertex_layout)
	{
		for (auto const& attribute : vertex_layout.GetAttributes())
		{
			::D3D12_INPUT_ELEMENT_DESC desc;
			desc.SemanticName         = GetSemanticName(attribute.semantic);
			desc.SemanticIndex        = 0;
			desc.Format               = GetD3D12Format(attribute.type, attribute.element_num);
			desc.InputSlot            = 0;
			desc.AlignedByteOffset    = D3D12_APPEND_ALIGNED_ELEMENT;
			desc.InputSlotClass       = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
			desc.InstanceDataStepRate = 0;
			m_descs.push_back(desc);
		}
	}

	::D3D12_INPUT_LAYOUT_DESC Get(void) const
	{
		return { m_descs.data(), static_cast<::UINT>(m_descs.size()) };
	}

private:
	static const char* GetSemanticName(render::Semantic semantic)
	{
		switch (semantic)
		{
		case render::Semantic::Position:		return "POSITION";
		case render::Semantic::Normal:			return "NORMAL";
		case render::Semantic::Color:			return "COLOR";
		case render::Semantic::TexCoord:		return "TEXCOORD";
		case render::Semantic::Binormal:		return "BINORMAL";
		case render::Semantic::BlendIndices:	return "BLENDINDICES";
		case render::Semantic::BlendWeights:	return "BLENDWEIGHT";
		case render::Semantic::PointSize:		return "PSIZE";
		case render::Semantic::Tangent:			return "TANGENT";
		}
		return "";
	}

	static ::DXGI_FORMAT GetD3D12Format(render::Type type, std::size_t element_num)
	{
		switch (element_num)
		{
		case 1:
			switch (type)
			{
			case hamon::render::Type::Int8:		return DXGI_FORMAT_R8_SINT;
			case hamon::render::Type::Int16:	return DXGI_FORMAT_R16_SINT;
			case hamon::render::Type::Int32:	return DXGI_FORMAT_R32_SINT;
			case hamon::render::Type::UInt8:	return DXGI_FORMAT_R8_UINT;
			case hamon::render::Type::UInt16:	return DXGI_FORMAT_R16_UINT;
			case hamon::render::Type::UInt32:	return DXGI_FORMAT_R32_UINT;
			case hamon::render::Type::Float:	return DXGI_FORMAT_R32_FLOAT;
			}
			break;
		case 2:
			switch (type)
			{
			case hamon::render::Type::Int8:		return DXGI_FORMAT_R8G8_SINT;
			case hamon::render::Type::Int16:	return DXGI_FORMAT_R16G16_SINT;
			case hamon::render::Type::Int32:	return DXGI_FORMAT_R32G32_SINT;
			case hamon::render::Type::UInt8:	return DXGI_FORMAT_R8G8_UINT;
			case hamon::render::Type::UInt16:	return DXGI_FORMAT_R16G16_UINT;
			case hamon::render::Type::UInt32:	return DXGI_FORMAT_R32G32_UINT;
			case hamon::render::Type::Float:	return DXGI_FORMAT_R32G32_FLOAT;
			}
			break;
		case 3:
			switch (type)
			{
			case hamon::render::Type::Int8:		return DXGI_FORMAT_UNKNOWN;//DXGI_FORMAT_R8G8B8_SINT;
			case hamon::render::Type::Int16:	return DXGI_FORMAT_UNKNOWN;//DXGI_FORMAT_R16G16B16_SINT;
			case hamon::render::Type::Int32:	return DXGI_FORMAT_R32G32B32_SINT;
			case hamon::render::Type::UInt8:	return DXGI_FORMAT_UNKNOWN;//DXGI_FORMAT_R8G8B8_UINT;
			case hamon::render::Type::UInt16:	return DXGI_FORMAT_UNKNOWN;//DXGI_FORMAT_R16G16B16_UINT;
			case hamon::render::Type::UInt32:	return DXGI_FORMAT_R32G32B32_UINT;
			case hamon::render::Type::Float:	return DXGI_FORMAT_R32G32B32_FLOAT;
			}
			break;
		case 4:
			switch (type)
			{
			case hamon::render::Type::Int8:		return DXGI_FORMAT_R8G8B8A8_SINT;
			case hamon::render::Type::Int16:	return DXGI_FORMAT_R16G16B16A16_SINT;
			case hamon::render::Type::Int32:	return DXGI_FORMAT_R32G32B32A32_SINT;
			case hamon::render::Type::UInt8:	return DXGI_FORMAT_R8G8B8A8_UINT;
			case hamon::render::Type::UInt16:	return DXGI_FORMAT_R16G16B16A16_UINT;
			case hamon::render::Type::UInt32:	return DXGI_FORMAT_R32G32B32A32_UINT;
			case hamon::render::Type::Float:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
			break;
		}
		return DXGI_FORMAT_UNKNOWN;
	}

private:
	std::vector<::D3D12_INPUT_ELEMENT_DESC>	m_descs;
};

}	// namespace d3d12

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D12_INPUT_LAYOUT_HPP

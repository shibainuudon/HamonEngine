/**
 *	@file	texture.hpp
 *
 *	@brief	Texture
 */

#ifndef HAMON_RENDER_VULKAN_TEXTURE_HPP
#define HAMON_RENDER_VULKAN_TEXTURE_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/vulkan/texture_format.hpp>
#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/image.hpp>
#include <hamon/render/vulkan/image_view.hpp>
#include <hamon/render/vulkan/command_buffer.hpp>
#include <hamon/render/vulkan/queue.hpp>
#include <hamon/render/vulkan/resource.hpp>
#include <hamon/render/texture.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class Texture
{
public:
	explicit Texture(
		vulkan::Device* device,
		vulkan::CommandPool* command_pool,
		render::Texture const& texture)
	{
		m_image = std::make_unique<vulkan::Image>(
			device,
			vulkan::TextureFormat(texture.GetFormat()),
			::VkExtent3D{texture.GetWidth(), texture.GetHeight(), 1},
			texture.GetMipmapCount(),
			VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT);

		m_device_memory = std::make_unique<vulkan::DeviceMemory>(
			device,
			device->GetImageMemoryRequirements(m_image->Get()),
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		m_device_memory->BindImage(m_image->Get(), 0);

		m_image_view = std::make_unique<vulkan::ImageView>(
			device,
			m_image->Get(),
			m_image->GetFormat());

		auto const size = GetMipmappedSizeInBytes(
			texture.GetFormat(),
			texture.GetWidth(),
			texture.GetHeight(),
			texture.GetMipmapCount());
		vulkan::Resource staging_buffer(
			device,
			size,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		{
			void* dst = staging_buffer.Map(0, size, 0);
			std::memcpy(dst, texture.GetData(), size);
			staging_buffer.Unmap();
		}

		vulkan::CommandBuffer command_buffer(command_pool);
		vulkan::Queue queue = command_pool->GetQueue();
		command_buffer.Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
		{
			m_image->TransitionLayout(&command_buffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
			m_image->CopyFromBuffer(&command_buffer, staging_buffer.GetBuffer());
			m_image->TransitionLayout(&command_buffer, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		}
		command_buffer.End();
		queue.Submit(
			command_buffer.Get(),
			VK_NULL_HANDLE,
			VK_NULL_HANDLE);
		queue.WaitIdle();
	}

	~Texture()
	{
	}

	::VkImageLayout GetLayout(void) const
	{
		return m_image->GetLayout();
	}

	::VkImageView const& GetView(void) const
	{
		return m_image_view->Get();
	}

private:
	std::unique_ptr<vulkan::Image>			m_image;
	std::unique_ptr<vulkan::DeviceMemory>	m_device_memory;
	std::unique_ptr<vulkan::ImageView>		m_image_view;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_TEXTURE_HPP

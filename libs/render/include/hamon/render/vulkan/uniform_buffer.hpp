/**
 *	@file	uniform_buffer.hpp
 *
 *	@brief	UniformBuffer
 */

#ifndef HAMON_RENDER_VULKAN_UNIFORM_BUFFER_HPP
#define HAMON_RENDER_VULKAN_UNIFORM_BUFFER_HPP

#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/resource.hpp>
#include <hamon/render/vulkan/vulkan.hpp>
#include <cstdint>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class UniformBuffer
{
	static ::VkDeviceSize RoundUp(::VkDeviceSize x, ::VkDeviceSize align)
	{
		return (x + (align - 1)) & ~(align - 1);
	}
public:
	explicit UniformBuffer(vulkan::Device* device, ::VkDeviceSize size)
		: m_resource(
			device,
			size,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	{
		m_mapped_buffer = static_cast<std::uint8_t*>(m_resource.Map(0, size, 0));

		auto physical_device = device->GetPhysicalDevice();
		auto properties = physical_device->GetProperties();
		m_alignemnt = properties.limits.minUniformBufferOffsetAlignment;
	}
	
	struct Subresource
	{
		std::uint8_t*	mapped_buffer;
		::VkDeviceSize	offset;
	};

	Subresource Allocate(::VkDeviceSize size)
	{
		auto const offset = m_offset;
		m_offset += RoundUp(size, m_alignemnt);
		return
		{
			m_mapped_buffer + offset,
			offset
		};
	}

	void Reset(void)
	{
		m_offset = 0;
	}
	
	::VkBuffer const& GetBuffer(void) const
	{
		return m_resource.GetBuffer();
	}

private:
	vulkan::Resource		m_resource;
	std::uint8_t*			m_mapped_buffer;
	::VkDeviceSize			m_offset{};
	::VkDeviceSize			m_alignemnt{};
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_UNIFORM_BUFFER_HPP

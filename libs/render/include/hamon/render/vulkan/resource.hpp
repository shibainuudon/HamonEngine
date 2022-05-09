/**
 *	@file	resource.hpp
 *
 *	@brief	Resource
 */

#ifndef HAMON_RENDER_VULKAN_RESOURCE_HPP
#define HAMON_RENDER_VULKAN_RESOURCE_HPP

#include <hamon/render/vulkan/buffer.hpp>
#include <hamon/render/vulkan/device_memory.hpp>
#include <hamon/render/vulkan/vulkan.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

/**
 *	BufferとDeviceMemoryを合わせたクラス
 * 
 *	BufferとDeviceMemoryはたいてい一緒に作られて使われるので、
 *	まとめたクラスを作ったほうが使いやすい。
 * 
 *	TODO: Resourceという名前はあまりしっくりきていないので
 *	いい名前があったら変更したい
 */
class Resource
{
public:
	explicit Resource(
		vulkan::Device* device,
		::VkDeviceSize size,
		::VkBufferUsageFlags usage,
		::VkFlags requirements_mask)
		: m_buffer(device, size, usage)
		, m_device_memory(device, m_buffer.GetMemoryRequirements(), requirements_mask)
	{
		m_device_memory.BindBuffer(m_buffer.Get(), 0);
	}
	
	::VkBuffer const& GetBuffer(void) const
	{
		return m_buffer.Get();
	}

	void* Map(
		::VkDeviceSize     offset,
		::VkDeviceSize     size,
		::VkMemoryMapFlags flags)
	{
		return m_device_memory.Map(offset, size, flags);
	}

	void Unmap(void)
	{
		return m_device_memory.Unmap();
	}

private:
	vulkan::Buffer			m_buffer;
	vulkan::DeviceMemory	m_device_memory;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_RESOURCE_HPP

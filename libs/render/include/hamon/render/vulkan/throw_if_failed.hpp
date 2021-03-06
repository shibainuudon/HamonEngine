/**
 *	@file	throw_if_failed.hpp
 *
 *	@brief	ThrowIfFailed関数
 */

#ifndef HAMON_RENDER_VULKAN_THROW_IF_FAILED_HPP
#define HAMON_RENDER_VULKAN_THROW_IF_FAILED_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <string>
#include <stdexcept>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

class ResultException : public std::runtime_error
{
public:
	explicit ResultException(::VkResult res)
		: std::runtime_error(ToString(res))
	{}

private:
	static std::string ToString(::VkResult res)
	{
#define HAMON_VK_RESULT_KVP(x)	case x: return #x
		switch (res)
		{
		HAMON_VK_RESULT_KVP(VK_ERROR_OUT_OF_HOST_MEMORY);
		HAMON_VK_RESULT_KVP(VK_ERROR_OUT_OF_DEVICE_MEMORY);
		HAMON_VK_RESULT_KVP(VK_ERROR_INITIALIZATION_FAILED);
		HAMON_VK_RESULT_KVP(VK_ERROR_DEVICE_LOST);
		HAMON_VK_RESULT_KVP(VK_ERROR_MEMORY_MAP_FAILED);
		HAMON_VK_RESULT_KVP(VK_ERROR_LAYER_NOT_PRESENT);
		HAMON_VK_RESULT_KVP(VK_ERROR_EXTENSION_NOT_PRESENT);
		HAMON_VK_RESULT_KVP(VK_ERROR_FEATURE_NOT_PRESENT);
		HAMON_VK_RESULT_KVP(VK_ERROR_INCOMPATIBLE_DRIVER);
		HAMON_VK_RESULT_KVP(VK_ERROR_TOO_MANY_OBJECTS);
		HAMON_VK_RESULT_KVP(VK_ERROR_FORMAT_NOT_SUPPORTED);
		HAMON_VK_RESULT_KVP(VK_ERROR_FRAGMENTED_POOL);
		HAMON_VK_RESULT_KVP(VK_ERROR_UNKNOWN);
		HAMON_VK_RESULT_KVP(VK_ERROR_OUT_OF_POOL_MEMORY);
		HAMON_VK_RESULT_KVP(VK_ERROR_INVALID_EXTERNAL_HANDLE);
		HAMON_VK_RESULT_KVP(VK_ERROR_FRAGMENTATION);
		HAMON_VK_RESULT_KVP(VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS);
		HAMON_VK_RESULT_KVP(VK_ERROR_SURFACE_LOST_KHR);
		HAMON_VK_RESULT_KVP(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
		HAMON_VK_RESULT_KVP(VK_ERROR_OUT_OF_DATE_KHR);
		HAMON_VK_RESULT_KVP(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
		HAMON_VK_RESULT_KVP(VK_ERROR_VALIDATION_FAILED_EXT);
		HAMON_VK_RESULT_KVP(VK_ERROR_INVALID_SHADER_NV);
		HAMON_VK_RESULT_KVP(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
		HAMON_VK_RESULT_KVP(VK_ERROR_NOT_PERMITTED_KHR);
		HAMON_VK_RESULT_KVP(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT);
//		HAMON_VK_RESULT_KVP(VK_ERROR_OUT_OF_POOL_MEMORY_KHR);
//		HAMON_VK_RESULT_KVP(VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR);
//		HAMON_VK_RESULT_KVP(VK_ERROR_FRAGMENTATION_EXT);
//		HAMON_VK_RESULT_KVP(VK_ERROR_NOT_PERMITTED_EXT);
//		HAMON_VK_RESULT_KVP(VK_ERROR_INVALID_DEVICE_ADDRESS_EXT);
//		HAMON_VK_RESULT_KVP(VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR);
//		HAMON_VK_RESULT_KVP(VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT);
		default: break;
		}
#undef HAMON_VK_RESULT_KVP
		return "";
	}
};

inline ::VkResult ThrowIfFailed(::VkResult res)
{
	if (res < 0)
	{
		throw ResultException(res);
	}
	return res;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_THROW_IF_FAILED_HPP

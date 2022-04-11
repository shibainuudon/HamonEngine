/**
 *	@file	logic_operation.hpp
 *
 *	@brief	LogicOperation
 */

#ifndef HAMON_RENDER_VULKAN_LOGIC_OPERATION_HPP
#define HAMON_RENDER_VULKAN_LOGIC_OPERATION_HPP

#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/logic_operation.hpp>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkLogicOp
LogicOperation(render::LogicOperation op)
{
	switch (op)
	{
	case render::LogicOperation::Clear:			return VK_LOGIC_OP_CLEAR;
	case render::LogicOperation::Set:			return VK_LOGIC_OP_SET;
	case render::LogicOperation::Copy:			return VK_LOGIC_OP_COPY;
	case render::LogicOperation::CopyInverted:	return VK_LOGIC_OP_COPY_INVERTED;
	case render::LogicOperation::Noop:			return VK_LOGIC_OP_NO_OP;
	case render::LogicOperation::Invert:		return VK_LOGIC_OP_INVERT;
	case render::LogicOperation::And:			return VK_LOGIC_OP_AND;
	case render::LogicOperation::Nand:			return VK_LOGIC_OP_NAND;
	case render::LogicOperation::Or:			return VK_LOGIC_OP_OR;
	case render::LogicOperation::Nor:			return VK_LOGIC_OP_NOR;
	case render::LogicOperation::Xor:			return VK_LOGIC_OP_XOR;
	case render::LogicOperation::Equiv:			return VK_LOGIC_OP_EQUIVALENT;
	case render::LogicOperation::AndReverse:	return VK_LOGIC_OP_AND_REVERSE;
	case render::LogicOperation::AndInverted:	return VK_LOGIC_OP_AND_INVERTED;
	case render::LogicOperation::OrReverse:		return VK_LOGIC_OP_OR_REVERSE;
	case render::LogicOperation::OrInverted:	return VK_LOGIC_OP_OR_INVERTED;
	}

	return VK_LOGIC_OP_NO_OP;
}

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_LOGIC_OPERATION_HPP

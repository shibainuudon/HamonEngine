/**
 *	@file	logic_operation.hpp
 *
 *	@brief	LogicOperation
 */

#ifndef HAMON_RENDER_D3D11_LOGIC_OPERATION_HPP
#define HAMON_RENDER_D3D11_LOGIC_OPERATION_HPP

#include <hamon/render/logic_operation.hpp>
#include <hamon/render/d3d/d3d11.hpp>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

inline ::D3D11_LOGIC_OP LogicOperation(render::LogicOperation op)
{
	switch (op)
	{
	case render::LogicOperation::Clear:			return D3D11_LOGIC_OP_CLEAR;
	case render::LogicOperation::Set:			return D3D11_LOGIC_OP_SET;
	case render::LogicOperation::Copy:			return D3D11_LOGIC_OP_COPY;
	case render::LogicOperation::CopyInverted:	return D3D11_LOGIC_OP_COPY_INVERTED;
	case render::LogicOperation::Noop:			return D3D11_LOGIC_OP_NOOP;
	case render::LogicOperation::Invert:		return D3D11_LOGIC_OP_INVERT;
	case render::LogicOperation::And:			return D3D11_LOGIC_OP_AND;
	case render::LogicOperation::Nand:			return D3D11_LOGIC_OP_NAND;
	case render::LogicOperation::Or:			return D3D11_LOGIC_OP_OR;
	case render::LogicOperation::Nor:			return D3D11_LOGIC_OP_NOR;
	case render::LogicOperation::Xor:			return D3D11_LOGIC_OP_XOR;
	case render::LogicOperation::Equiv:			return D3D11_LOGIC_OP_EQUIV;
	case render::LogicOperation::AndReverse:	return D3D11_LOGIC_OP_AND_REVERSE;
	case render::LogicOperation::AndInverted:	return D3D11_LOGIC_OP_AND_INVERTED;
	case render::LogicOperation::OrReverse:		return D3D11_LOGIC_OP_OR_REVERSE;
	case render::LogicOperation::OrInverted:	return D3D11_LOGIC_OP_OR_INVERTED;
	}
	return D3D11_LOGIC_OP_NOOP;
}

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_LOGIC_OPERATION_HPP

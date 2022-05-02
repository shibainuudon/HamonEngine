/**
 *	@file	device_context.hpp
 *
 *	@brief	DeviceContext
 */

#ifndef HAMON_RENDER_D3D11_DEVICE_CONTEXT_HPP
#define HAMON_RENDER_D3D11_DEVICE_CONTEXT_HPP

#include <hamon/render/d3d/d3d11.hpp>
#include <vector>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class DeviceContext
{
public:
	explicit DeviceContext(ComPtr<ID3D11DeviceContext4> device_context)
		: m_device_context(device_context)
	{
	}

	void ClearState(void)
	{
		m_device_context->ClearState();
	}

	void ClearRenderTargetView(
		::ID3D11RenderTargetView* render_target_view,
		::FLOAT const* color_rgba)
	{
		m_device_context->ClearRenderTargetView(render_target_view, color_rgba);
	}

	void IASetVertexBuffers(
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* vertex_buffers,
		const ::UINT* strides,
		const ::UINT* offsets)
	{
		m_device_context->IASetVertexBuffers(start_slot, num_buffers, vertex_buffers, strides, offsets);
	}

	void IASetIndexBuffer(
		::ID3D11Buffer* index_buffer,
		::DXGI_FORMAT   format,
		::UINT          offset)
	{
		m_device_context->IASetIndexBuffer(index_buffer, format, offset);
	}

	void IASetPrimitiveTopology(
		::D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		m_device_context->IASetPrimitiveTopology(topology);
	}

	void IASetInputLayout(::ID3D11InputLayout* input_layout)
	{
		m_device_context->IASetInputLayout(input_layout);
	}

	void VSSetShader(::ID3D11VertexShader* vertex_shader)
	{
		m_device_context->VSSetShader(vertex_shader, nullptr, 0u);
	}

	void PSSetShader(::ID3D11PixelShader* pixel_shader)
	{
		m_device_context->PSSetShader(pixel_shader, nullptr, 0u);
	}

	void GSSetShader(::ID3D11GeometryShader* geometry_shader)
	{
		m_device_context->GSSetShader(geometry_shader, nullptr, 0u);
	}

	void HSSetShader(::ID3D11HullShader* hull_shader)
	{
		m_device_context->HSSetShader(hull_shader, nullptr, 0u);
	}

	void DSSetShader(::ID3D11DomainShader* domain_shader)
	{
		m_device_context->DSSetShader(domain_shader, nullptr, 0u);
	}

	void CSSetShader(::ID3D11ComputeShader* compute_shader)
	{
		m_device_context->CSSetShader(compute_shader, nullptr, 0u);
	}

	void RSSetState(::ID3D11RasterizerState* rasterizer_state)
	{
		m_device_context->RSSetState(rasterizer_state);
	}

	void RSSetViewports(
		::UINT                  num_viewports,
		::D3D11_VIEWPORT const* viewports)
	{
		m_device_context->RSSetViewports(num_viewports, viewports);
	}

	void OMSetRenderTargets(
		::UINT                           num_views,
		::ID3D11RenderTargetView* const* render_target_views,
		::ID3D11DepthStencilView*        depth_stencil_view)
	{
		m_device_context->OMSetRenderTargets(num_views, render_target_views, depth_stencil_view);
	}

	void OMSetBlendState(
		::ID3D11BlendState* blend_state,
		const ::FLOAT       blend_factor[4],
		::UINT              sample_mask)
	{
		m_device_context->OMSetBlendState(blend_state, blend_factor, sample_mask);
	}

	void OMSetDepthStencilState(
		::ID3D11DepthStencilState* depth_stencil_state,
		::UINT                     stencil_ref)
	{
		m_device_context->OMSetDepthStencilState(depth_stencil_state, stencil_ref);
	}

	void VSSetConstantBuffers(
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers)
	{
		m_device_context->VSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void PSSetConstantBuffers(
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers)
	{
		m_device_context->PSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void GSSetConstantBuffers(
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers)
	{
		m_device_context->GSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void HSSetConstantBuffers(
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers)
	{
		m_device_context->HSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void DSSetConstantBuffers(
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers)
	{
		m_device_context->DSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}
	
	void CSSetConstantBuffers(
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers)
	{
		m_device_context->CSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void VSSetSamplers(
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers)
	{
		m_device_context->VSSetSamplers(start_slot, num_samplers, samplers);
	}

	void PSSetSamplers(
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers)
	{
		m_device_context->PSSetSamplers(start_slot, num_samplers, samplers);
	}

	void GSSetSamplers(
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers)
	{
		m_device_context->GSSetSamplers(start_slot, num_samplers, samplers);
	}

	void HSSetSamplers(
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers)
	{
		m_device_context->HSSetSamplers(start_slot, num_samplers, samplers);
	}

	void DSSetSamplers(
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers)
	{
		m_device_context->DSSetSamplers(start_slot, num_samplers, samplers);
	}

	void CSSetSamplers(
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers)
	{
		m_device_context->CSSetSamplers(start_slot, num_samplers, samplers);
	}

	void VSSetShaderResources(
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views)
	{
		m_device_context->VSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

	void PSSetShaderResources(
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views)
	{
		m_device_context->PSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

	void GSSetShaderResources(
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views)
	{
		m_device_context->GSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

	void HSSetShaderResources(
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views)
	{
		m_device_context->HSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

	void DSSetShaderResources(
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views)
	{
		m_device_context->DSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

	void CSSetShaderResources(
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views)
	{
		m_device_context->CSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

	void UpdateSubresource(
		::ID3D11Resource*  dst_resource,
		::UINT             dst_subresource,
		const ::D3D11_BOX* dst_box,
		const void*        src_data,
		::UINT             src_row_pitch,
		::UINT             src_depth_pitch)
	{
		m_device_context->UpdateSubresource(
			dst_resource,
			dst_subresource,
			dst_box,
			src_data,
			src_row_pitch,
			src_depth_pitch);
	}

	void Draw(
		::UINT vertex_count,
		::UINT start_vertex_location)
	{
		m_device_context->Draw(vertex_count, start_vertex_location);
	}

	void DrawIndexed(
		::UINT index_count,
		::UINT start_index_location,
		::INT  base_vertex_location)
	{
		m_device_context->DrawIndexed(index_count, start_index_location, base_vertex_location);
	}

private:
	ComPtr<ID3D11DeviceContext4>	m_device_context;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_DEVICE_CONTEXT_HPP

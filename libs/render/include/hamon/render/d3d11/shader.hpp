/**
 *	@file	shader.hpp
 *
 *	@brief	Shader
 */

#ifndef HAMON_RENDER_D3D11_SHADER_HPP
#define HAMON_RENDER_D3D11_SHADER_HPP

 #include <hamon/render/shader.hpp>
 #include <hamon/render/texture.hpp>
 #include <hamon/render/sampler.hpp>
 #include <hamon/render/d3d11/device.hpp>
 #include <hamon/render/d3d11/device_context.hpp>
 #include <hamon/render/d3d11/constant_buffer.hpp>
 #include <hamon/render/d3d11/shader_reflection.hpp>
 #include <hamon/render/d3d11/resource_map.hpp>
 #include <hamon/render/d3d/d3d11.hpp>
 #include <hamon/render/d3d/d3dcompiler.hpp>
 #include <hamon/render/d3d/com_ptr.hpp>
 #include <iostream>

namespace hamon
{

inline namespace render
{

namespace d3d11
{

class Shader
{
public:
	void Create(d3d11::Device* device, render::Shader const& shader)
	{
		auto micro_code = Compile(GetTargetString(), shader);

		d3d11::ShaderReflection reflection(micro_code.Get());

		Initialize(device, micro_code.Get(), reflection);
		CreateConstantBuffers(device, reflection);
	}

	virtual ~Shader(){}

	virtual void Bind(d3d11::DeviceContext* device_context) = 0;

	void LoadUniforms(
		d3d11::Device* device,
		d3d11::DeviceContext* device_context,
		d3d11::ResourceMap* resource_map,
		render::Uniforms const& uniforms)
	{
		for (auto& constant_buffer : m_constant_buffers)
		{
			constant_buffer.LoadUniforms(device_context, uniforms);

			auto buffer = constant_buffer.GetBuffer();
			this->SetConstantBuffers(device_context,
				constant_buffer.GetBindPoint(),
				1,
				&buffer);
		}

		for (auto const& sampler_desc : m_samplers)
		{
			auto uniform = uniforms[sampler_desc.Name];
			if (uniform == nullptr)
			{
				continue;
			}

			using type = render::Sampler;
			auto data = static_cast<type const*>(uniform->GetData());
			auto sampler = resource_map->GetSampler(device, *data);
			auto sampler_state = sampler->GetState();
			this->SetSamplers(
				device_context,
				sampler_desc.BindPoint,
				1,
				&sampler_state);
		}

		for (auto const& texture_desc : m_textures)
		{
			auto uniform = uniforms[texture_desc.Name];
			if (uniform == nullptr)
			{
				continue;
			}

			using type = render::Texture;
			auto data = static_cast<type const*>(uniform->GetData());
			auto texture = resource_map->GetTexture(device, *data);
			auto srv = texture->GetShaderResourceView();
			this->SetShaderResources(
				device_context,
				texture_desc.BindPoint,
				1,
				&srv);
		}
	}

private:
	virtual const char* GetTargetString(void) = 0;

	virtual void Initialize(
		d3d11::Device* device,
		::ID3DBlob* micro_code,
		d3d11::ShaderReflection const& reflection) = 0;
	
	virtual void SetConstantBuffers(
		d3d11::DeviceContext*  device_context,
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers) = 0;
	
	virtual void SetSamplers(
		d3d11::DeviceContext*        device_context,
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers) = 0;

	virtual void SetShaderResources(
		d3d11::DeviceContext*			   device_context,
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views) = 0;

private:
	static ComPtr<::ID3DBlob>
	Compile(const char* target, render::Shader const& shader)
	{
		::UINT flags1 =
			D3DCOMPILE_ENABLE_STRICTNESS |
			D3DCOMPILE_DEBUG |
			0;

		ComPtr<::ID3DBlob>	micro_code;
		ComPtr<::ID3DBlob>	error_msgs;
		auto const hr = ::D3DCompile(
			shader.GetSource().c_str(),
			shader.GetSource().size(),
			nullptr,	// source_name
			nullptr,	// defines
			nullptr,	// include
			shader.GetEntryPoint().c_str(),
			target,
			flags1,
			0,			// flags2
			&micro_code,
			&error_msgs);

		if (error_msgs)
		{
			std::cout << static_cast<const char*>(error_msgs->GetBufferPointer()) << std::endl;
		}

		if (FAILED(hr))
		{
			return {};
		}

		return micro_code;
	}
	
	void CreateConstantBuffers(d3d11::Device* device, d3d11::ShaderReflection const& reflection)
	{
		auto const shader_desc = reflection.GetDesc();

		for (::UINT i = 0; i < shader_desc.BoundResources; ++i)
		{
			auto const input_bind_desc = reflection.GetResourceBindingDesc(i);

			switch (input_bind_desc.Type)
			{
			case D3D_SIT_CBUFFER:
				{
					auto cbuffer = reflection.GetConstantBufferByName(input_bind_desc.Name);
					::D3D11_SHADER_BUFFER_DESC cbuffer_desc;
					cbuffer->GetDesc(&cbuffer_desc);
					m_constant_buffers.emplace_back(
						device,
						cbuffer,
						cbuffer_desc,
						input_bind_desc.BindPoint);
				}
				break;
			case D3D_SIT_TEXTURE:
				m_textures.push_back(input_bind_desc);
				break;
			case D3D_SIT_SAMPLER:
				m_samplers.push_back(input_bind_desc);
				break;
			}
		}
	}

private:
	std::vector<d3d11::ConstantBuffer>		m_constant_buffers;
	std::vector<::D3D11_SHADER_INPUT_BIND_DESC>	m_textures;
	std::vector<::D3D11_SHADER_INPUT_BIND_DESC>	m_samplers;
};

class VertexShader : public Shader
{
private:
	const char* GetTargetString(void) override
	{
		return "vs_5_0";
	}

	void Initialize(
		d3d11::Device* device,
		::ID3DBlob* micro_code,
		d3d11::ShaderReflection const& reflection) override
	{
		m_shader = device->CreateVertexShader(micro_code);
		m_input_layout = CreateInputLayout(device, micro_code, reflection);
	}

	void Bind(d3d11::DeviceContext* device_context) override
	{
		device_context->VSSetShader(m_shader.Get());
		device_context->IASetInputLayout(m_input_layout.Get());
	}

	void SetConstantBuffers(
		d3d11::DeviceContext*  device_context,
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers) override
	{
		device_context->VSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void SetSamplers(
		d3d11::DeviceContext*        device_context,
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers) override
	{
		device_context->VSSetSamplers(start_slot, num_samplers, samplers);
	}

	void SetShaderResources(
		d3d11::DeviceContext*			   device_context,
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views) override
	{
		device_context->VSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

private:
	static ComPtr<::ID3D11InputLayout>
	CreateInputLayout(Device* device, ::ID3DBlob* micro_code, d3d11::ShaderReflection const& reflection)
	{
		auto const shader_desc = reflection.GetDesc();

		std::vector<::D3D11_INPUT_ELEMENT_DESC> input_element_descs(shader_desc.InputParameters);

		for (::UINT i = 0; i < shader_desc.InputParameters; ++i)
		{
			auto const param_desc = reflection.GetInputParameterDesc(i);

			auto& desc = input_element_descs[i];
			desc.SemanticName         = param_desc.SemanticName;
			desc.SemanticIndex        = param_desc.SemanticIndex;
			desc.Format               = GetFormat(param_desc.Mask, param_desc.ComponentType);
			desc.InputSlot            = 0;
			desc.AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
			desc.InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
			desc.InstanceDataStepRate = 0;
		}

		return device->CreateInputLayout(
			input_element_descs.data(),
			static_cast<::UINT>(input_element_descs.size()),
			micro_code);
	}

	static ::DXGI_FORMAT GetFormat(::BYTE mask, ::D3D_REGISTER_COMPONENT_TYPE component_type)
	{
		if (mask == 1)
		{
			switch (component_type)
			{
			case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32_UINT;
			case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32_SINT;
			case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32_FLOAT;
			default: break;
			}
		}
		else if (mask <= 3)
		{
			switch (component_type)
			{
			case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32G32_UINT;
			case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32G32_SINT;
			case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32_FLOAT;
			default: break;
			}
		}
		else if (mask <= 7)
		{
			switch (component_type)
			{
			case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32G32B32_UINT;
			case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32G32B32_SINT;
			case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32B32_FLOAT;
			default: break;
			}
		}
		else if (mask <= 15)
		{
			switch (component_type)
			{
			case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32G32B32A32_UINT;
			case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32G32B32A32_SINT;
			case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
			default: break;
			}
		}

		return DXGI_FORMAT_UNKNOWN;
	}

private:
	ComPtr<::ID3D11VertexShader>	m_shader;
	ComPtr<::ID3D11InputLayout>		m_input_layout;
};

class GeometryShader : public Shader
{
private:
	const char* GetTargetString(void) override
	{
		return "gs_5_0";
	}

	void Initialize(
		d3d11::Device* device,
		::ID3DBlob* micro_code,
		d3d11::ShaderReflection const& /*reflection*/) override
	{
		m_shader = device->CreateGeometryShader(micro_code);
	}

	void Bind(d3d11::DeviceContext* device_context) override
	{
		device_context->GSSetShader(m_shader.Get());
	}

	void SetConstantBuffers(
		d3d11::DeviceContext*  device_context,
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers) override
	{
		device_context->GSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void SetSamplers(
		d3d11::DeviceContext*        device_context,
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers) override
	{
		device_context->GSSetSamplers(start_slot, num_samplers, samplers);
	}

	void SetShaderResources(
		d3d11::DeviceContext*			   device_context,
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views) override
	{
		device_context->GSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

private:
	ComPtr<::ID3D11GeometryShader>	m_shader;
};

class PixelShader : public Shader
{
private:
	const char* GetTargetString(void) override
	{
		return "ps_5_0";
	}

	void Initialize(
		d3d11::Device* device,
		::ID3DBlob* micro_code,
		d3d11::ShaderReflection const& /*reflection*/) override
	{
		m_shader = device->CreatePixelShader(micro_code);
	}

	void Bind(d3d11::DeviceContext* device_context) override
	{
		device_context->PSSetShader(m_shader.Get());
	}

	void SetConstantBuffers(
		d3d11::DeviceContext*  device_context,
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers) override
	{
		device_context->PSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void SetSamplers(
		d3d11::DeviceContext*        device_context,
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers) override
	{
		device_context->PSSetSamplers(start_slot, num_samplers, samplers);
	}

	void SetShaderResources(
		d3d11::DeviceContext*			   device_context,
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views) override
	{
		device_context->PSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

private:
	ComPtr<::ID3D11PixelShader>		m_shader;
};

class HullShader : public Shader
{
private:
	const char* GetTargetString(void) override
	{
		return "hs_5_0";
	}

	void Initialize(
		d3d11::Device* device,
		::ID3DBlob* micro_code,
		d3d11::ShaderReflection const& /*reflection*/) override
	{
		m_shader = device->CreateHullShader(micro_code);
	}

	void Bind(d3d11::DeviceContext* device_context) override
	{
		device_context->HSSetShader(m_shader.Get());
	}

	void SetConstantBuffers(
		d3d11::DeviceContext*  device_context,
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers) override
	{
		device_context->HSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void SetSamplers(
		d3d11::DeviceContext*        device_context,
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers) override
	{
		device_context->HSSetSamplers(start_slot, num_samplers, samplers);
	}

	void SetShaderResources(
		d3d11::DeviceContext*			   device_context,
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views) override
	{
		device_context->HSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

private:
	ComPtr<::ID3D11HullShader>		m_shader;
};

class DomainShader : public Shader
{
private:
	const char* GetTargetString(void) override
	{
		return "ds_5_0";
	}

	void Initialize(
		d3d11::Device* device,
		::ID3DBlob* micro_code,
		d3d11::ShaderReflection const& /*reflection*/) override
	{
		m_shader = device->CreateDomainShader(micro_code);
	}

	void Bind(d3d11::DeviceContext* device_context) override
	{
		device_context->DSSetShader(m_shader.Get());
	}

	void SetConstantBuffers(
		d3d11::DeviceContext*  device_context,
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers) override
	{
		device_context->DSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void SetSamplers(
		d3d11::DeviceContext*        device_context,
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers) override
	{
		device_context->DSSetSamplers(start_slot, num_samplers, samplers);
	}

	void SetShaderResources(
		d3d11::DeviceContext*			   device_context,
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views) override
	{
		device_context->DSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

private:
	ComPtr<::ID3D11DomainShader>		m_shader;
};

class ComputeShader : public Shader
{
private:
	const char* GetTargetString(void) override
	{
		return "cs_5_0";
	}

	void Initialize(
		d3d11::Device* device,
		::ID3DBlob* micro_code,
		d3d11::ShaderReflection const& /*reflection*/) override
	{
		m_shader = device->CreateComputeShader(micro_code);
	}

	void Bind(d3d11::DeviceContext* device_context) override
	{
		device_context->CSSetShader(m_shader.Get());
	}

	void SetConstantBuffers(
		d3d11::DeviceContext*  device_context,
		::UINT                 start_slot,
		::UINT                 num_buffers,
		::ID3D11Buffer* const* constant_buffers) override
	{
		device_context->CSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
	}

	void SetSamplers(
		d3d11::DeviceContext*        device_context,
		::UINT                       start_slot,
		::UINT                       num_samplers,
		::ID3D11SamplerState* const* samplers) override
	{
		device_context->CSSetSamplers(start_slot, num_samplers, samplers);
	}

	void SetShaderResources(
		d3d11::DeviceContext*			   device_context,
		::UINT                             start_slot,
		::UINT                             num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views) override
	{
		device_context->CSSetShaderResources(start_slot, num_views, shader_resource_views);
	}

private:
	ComPtr<::ID3D11ComputeShader>		m_shader;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_SHADER_HPP

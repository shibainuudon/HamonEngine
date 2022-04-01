/**
 *	@file	shader.hpp
 *
 *	@brief	Shader
 */

#ifndef HAMON_RENDER_D3D11_SHADER_HPP
#define HAMON_RENDER_D3D11_SHADER_HPP

 #include <hamon/render/shader.hpp>
 #include <hamon/render/d3d11/device.hpp>
 #include <hamon/render/d3d11/device_context.hpp>
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
	virtual ~Shader(){}

	virtual void Bind(DeviceContext* device_context) = 0;

protected:
	ComPtr<::ID3DBlob>
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
			"main",
			target,
			flags1,
			0,			// flags2
			&micro_code,
			&error_msgs);

		if (error_msgs)
		{
			std::cout << static_cast<const char*>(error_msgs->GetBufferPointer()) << std::endl;
		}

		return micro_code;
	}
};

class VertexShader : public Shader
{
public:
	VertexShader(Device* device, render::Shader const& shader)
	{
		auto micro_code = Compile("vs_5_0", shader);
		m_shader = device->CreateVertexShader(micro_code.Get());
		m_input_layout = CreateInputLayout(device, micro_code.Get());
	}

	void Bind(DeviceContext* device_context) override
	{
		device_context->VSSetShader(m_shader.Get());
		device_context->IASetInputLayout(m_input_layout.Get());
	}

private:
	ComPtr<::ID3D11InputLayout> CreateInputLayout(Device* device, ::ID3DBlob* micro_code)
	{
		ComPtr<::ID3D11ShaderReflection> reflection;
		ThrowIfFailed(::D3DReflect(
			micro_code->GetBufferPointer(),
			micro_code->GetBufferSize(),
			IID_PPV_ARGS(&reflection)));

		::D3D11_SHADER_DESC shader_desc;
		ThrowIfFailed(reflection->GetDesc(&shader_desc));

		std::vector<::D3D11_INPUT_ELEMENT_DESC> input_element_descs(shader_desc.InputParameters);

		for (::UINT i = 0; i < shader_desc.InputParameters; ++i)
		{
			::D3D11_SIGNATURE_PARAMETER_DESC param_desc;
			ThrowIfFailed(reflection->GetInputParameterDesc(i, &param_desc));

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

	static ::DXGI_FORMAT GetFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE component_type)
	{
		if (mask == 1)
		{
			switch (component_type)
			{
			case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32_UINT;
			case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32_SINT;
			case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32_FLOAT;
			}
		}
		else if (mask <= 3)
		{
			switch (component_type)
			{
			case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32G32_UINT;
			case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32G32_SINT;
			case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32_FLOAT;
			}
		}
		else if (mask <= 7)
		{
			switch (component_type)
			{
			case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32G32B32_UINT;
			case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32G32B32_SINT;
			case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32B32_FLOAT;
			}
		}
		else if (mask <= 15)
		{
			switch (component_type)
			{
			case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32G32B32A32_UINT;
			case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32G32B32A32_SINT;
			case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
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
public:
	GeometryShader(Device* device, render::Shader const& shader)
	{
		auto micro_code = Compile("gs_5_0", shader);
		m_shader = device->CreateGeometryShader(micro_code.Get());
	}

	void Bind(DeviceContext* device_context) override
	{
		device_context->GSSetShader(m_shader.Get());
	}

private:
	ComPtr<::ID3D11GeometryShader>	m_shader;
};

class PixelShader : public Shader
{
public:
	PixelShader(Device* device, render::Shader const& shader)
	{
		auto micro_code = Compile("ps_5_0", shader);
		m_shader = device->CreatePixelShader(micro_code.Get());
	}

	void Bind(DeviceContext* device_context) override
	{
		device_context->PSSetShader(m_shader.Get());
	}

private:
	ComPtr<::ID3D11PixelShader>		m_shader;
};

class HullShader : public Shader
{
public:
	HullShader(Device* device, render::Shader const& shader)
	{
		auto micro_code = Compile("hs_5_0", shader);
		m_shader = device->CreateHullShader(micro_code.Get());
	}

	void Bind(DeviceContext* device_context) override
	{
		device_context->HSSetShader(m_shader.Get());
	}

private:
	ComPtr<::ID3D11HullShader>		m_shader;
};

class DomainShader : public Shader
{
public:
	DomainShader(Device* device, render::Shader const& shader)
	{
		auto micro_code = Compile("ds_5_0", shader);
		m_shader = device->CreateDomainShader(micro_code.Get());
	}

	void Bind(DeviceContext* device_context) override
	{
		device_context->DSSetShader(m_shader.Get());
	}

private:
	ComPtr<::ID3D11DomainShader>		m_shader;
};

class ComputeShader : public Shader
{
public:
	ComputeShader(Device* device, render::Shader const& shader)
	{
		auto micro_code = Compile("cs_5_0", shader);
		m_shader = device->CreateComputeShader(micro_code.Get());
	}

	void Bind(DeviceContext* device_context) override
	{
		device_context->CSSetShader(m_shader.Get());
	}

private:
	ComPtr<::ID3D11ComputeShader>		m_shader;
};

}	// namespace d3d11

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_D3D11_SHADER_HPP

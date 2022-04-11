/**
 *	@file	shader.hpp
 *
 *	@brief	Shader
 */

#ifndef HAMON_RENDER_VULKAN_SHADER_HPP
#define HAMON_RENDER_VULKAN_SHADER_HPP

#include <hamon/render/vulkan/device.hpp>
#include <hamon/render/vulkan/vulkan.hpp>
#include <hamon/render/shader.hpp>
#include <glslang/SPIRV/GlslangToSpv.h>

namespace hamon
{

inline namespace render
{

namespace vulkan
{

inline ::VkShaderStageFlagBits ShaderStage(render::ShaderStage stage)
{
	switch (stage)
	{
	case render::ShaderStage::Compute:					return VK_SHADER_STAGE_COMPUTE_BIT;
	case render::ShaderStage::Vertex:					return VK_SHADER_STAGE_VERTEX_BIT;
	case render::ShaderStage::Geometry:					return VK_SHADER_STAGE_GEOMETRY_BIT;
	case render::ShaderStage::TessellationControl:		return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
	case render::ShaderStage::TessellationEvaluation:	return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
	case render::ShaderStage::Fragment:					return VK_SHADER_STAGE_FRAGMENT_BIT;
	}
	return VK_SHADER_STAGE_VERTEX_BIT;
}

class Shader
{
public:
	explicit Shader(vulkan::Device* device, render::Shader const& shader)
		: m_device(device)
		, m_stage(vulkan::ShaderStage(shader.GetStage()))
	{
		std::vector<std::uint32_t> spv = GLSLtoSPV(shader);

		::VkShaderModuleCreateInfo info{};
		info.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.codeSize = spv.size() * sizeof(std::uint32_t);
		info.pCode    = spv.data();

		m_shader_module = m_device->CreateShaderModule(info);
	}

	~Shader()
	{
		m_device->DestroyShaderModule(m_shader_module);
	}

	::VkShaderModule		GetModule(void) const { return m_shader_module; }
	::VkShaderStageFlagBits	GetStage(void) const { return m_stage; }

private:
	static EShLanguage ToEShLanguage(render::ShaderStage stage)
	{
		switch (stage)
		{
		case hamon::render::ShaderStage::Compute:					return EShLangCompute;
		case hamon::render::ShaderStage::Vertex:					return EShLangVertex;
		case hamon::render::ShaderStage::Geometry:					return EShLangGeometry;
		case hamon::render::ShaderStage::TessellationControl:		return EShLangTessControl;	
		case hamon::render::ShaderStage::TessellationEvaluation:	return EShLangTessEvaluation;
		case hamon::render::ShaderStage::Fragment:					return EShLangFragment;
		}
		return EShLangVertex;
	}

	static void InitResources(TBuiltInResource* resources)
	{
		resources->maxLights = 32;
		resources->maxClipPlanes = 6;
		resources->maxTextureUnits = 32;
		resources->maxTextureCoords = 32;
		resources->maxVertexAttribs = 64;
		resources->maxVertexUniformComponents = 4096;
		resources->maxVaryingFloats = 64;
		resources->maxVertexTextureImageUnits = 32;
		resources->maxCombinedTextureImageUnits = 80;
		resources->maxTextureImageUnits = 32;
		resources->maxFragmentUniformComponents = 4096;
		resources->maxDrawBuffers = 32;
		resources->maxVertexUniformVectors = 128;
		resources->maxVaryingVectors = 8;
		resources->maxFragmentUniformVectors = 16;
		resources->maxVertexOutputVectors = 16;
		resources->maxFragmentInputVectors = 15;
		resources->minProgramTexelOffset = -8;
		resources->maxProgramTexelOffset = 7;
		resources->maxClipDistances = 8;
		resources->maxComputeWorkGroupCountX = 65535;
		resources->maxComputeWorkGroupCountY = 65535;
		resources->maxComputeWorkGroupCountZ = 65535;
		resources->maxComputeWorkGroupSizeX = 1024;
		resources->maxComputeWorkGroupSizeY = 1024;
		resources->maxComputeWorkGroupSizeZ = 64;
		resources->maxComputeUniformComponents = 1024;
		resources->maxComputeTextureImageUnits = 16;
		resources->maxComputeImageUniforms = 8;
		resources->maxComputeAtomicCounters = 8;
		resources->maxComputeAtomicCounterBuffers = 1;
		resources->maxVaryingComponents = 60;
		resources->maxVertexOutputComponents = 64;
		resources->maxGeometryInputComponents = 64;
		resources->maxGeometryOutputComponents = 128;
		resources->maxFragmentInputComponents = 128;
		resources->maxImageUnits = 8;
		resources->maxCombinedImageUnitsAndFragmentOutputs = 8;
		resources->maxCombinedShaderOutputResources = 8;
		resources->maxImageSamples = 0;
		resources->maxVertexImageUniforms = 0;
		resources->maxTessControlImageUniforms = 0;
		resources->maxTessEvaluationImageUniforms = 0;
		resources->maxGeometryImageUniforms = 0;
		resources->maxFragmentImageUniforms = 8;
		resources->maxCombinedImageUniforms = 8;
		resources->maxGeometryTextureImageUnits = 16;
		resources->maxGeometryOutputVertices = 256;
		resources->maxGeometryTotalOutputComponents = 1024;
		resources->maxGeometryUniformComponents = 1024;
		resources->maxGeometryVaryingComponents = 64;
		resources->maxTessControlInputComponents = 128;
		resources->maxTessControlOutputComponents = 128;
		resources->maxTessControlTextureImageUnits = 16;
		resources->maxTessControlUniformComponents = 1024;
		resources->maxTessControlTotalOutputComponents = 4096;
		resources->maxTessEvaluationInputComponents = 128;
		resources->maxTessEvaluationOutputComponents = 128;
		resources->maxTessEvaluationTextureImageUnits = 16;
		resources->maxTessEvaluationUniformComponents = 1024;
		resources->maxTessPatchComponents = 120;
		resources->maxPatchVertices = 32;
		resources->maxTessGenLevel = 64;
		resources->maxViewports = 16;
		resources->maxVertexAtomicCounters = 0;
		resources->maxTessControlAtomicCounters = 0;
		resources->maxTessEvaluationAtomicCounters = 0;
		resources->maxGeometryAtomicCounters = 0;
		resources->maxFragmentAtomicCounters = 8;
		resources->maxCombinedAtomicCounters = 8;
		resources->maxAtomicCounterBindings = 1;
		resources->maxVertexAtomicCounterBuffers = 0;
		resources->maxTessControlAtomicCounterBuffers = 0;
		resources->maxTessEvaluationAtomicCounterBuffers = 0;
		resources->maxGeometryAtomicCounterBuffers = 0;
		resources->maxFragmentAtomicCounterBuffers = 1;
		resources->maxCombinedAtomicCounterBuffers = 1;
		resources->maxAtomicCounterBufferSize = 16384;
		resources->maxTransformFeedbackBuffers = 4;
		resources->maxTransformFeedbackInterleavedComponents = 64;
		resources->maxCullDistances = 8;
		resources->maxCombinedClipAndCullDistances = 8;
		resources->maxSamples = 4;
		resources->maxMeshOutputVerticesNV = 256;
		resources->maxMeshOutputPrimitivesNV = 512;
		resources->maxMeshWorkGroupSizeX_NV = 32;
		resources->maxMeshWorkGroupSizeY_NV = 1;
		resources->maxMeshWorkGroupSizeZ_NV = 1;
		resources->maxTaskWorkGroupSizeX_NV = 32;
		resources->maxTaskWorkGroupSizeY_NV = 1;
		resources->maxTaskWorkGroupSizeZ_NV = 1;
		resources->maxMeshViewCountNV = 4;
		resources->limits.nonInductiveForLoops = 1;
		resources->limits.whileLoops = 1;
		resources->limits.doWhileLoops = 1;
		resources->limits.generalUniformIndexing = 1;
		resources->limits.generalAttributeMatrixVectorIndexing = 1;
		resources->limits.generalVaryingIndexing = 1;
		resources->limits.generalSamplerIndexing = 1;
		resources->limits.generalVariableIndexing = 1;
		resources->limits.generalConstantMatrixVectorIndexing = 1;
	}

	static std::vector<std::uint32_t> GLSLtoSPV(render::Shader const& glsl_shader)
	{
		auto const  stage  = glsl_shader.GetStage();
		char const* source = glsl_shader.GetSource().c_str();

		glslang::InitializeProcess();

		EShLanguage esh_stage = ToEShLanguage(stage);

		TBuiltInResource resources = {};
		InitResources(&resources);

		// Enable SPIR-V and Vulkan rules when parsing GLSL
		EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);

		glslang::TShader shader(esh_stage);
		shader.setStrings(&source, 1);

		if (!shader.parse(&resources, 100, false, messages)) {
			puts(shader.getInfoLog());
			puts(shader.getInfoDebugLog());
			return {};  // something didn't work
		}

		glslang::TProgram program;
		program.addShader(&shader);

		//
		// Program-level processing...
		//

		if (!program.link(messages)) {
			puts(shader.getInfoLog());
			puts(shader.getInfoDebugLog());
			fflush(stdout);
			return {};
		}

		std::vector<std::uint32_t> spirv;
		glslang::GlslangToSpv(*program.getIntermediate(esh_stage), spirv);

		glslang::FinalizeProcess();

		return spirv;
	}

private:
	::VkShaderModule		m_shader_module;
	::VkShaderStageFlagBits	m_stage;
	vulkan::Device*			m_device;
};

}	// namespace vulkan

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_VULKAN_shader_HPP

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/ShaderBuilder/GLSL/GLSLShaderReflector.hpp>

#include <spirv_cross/spirv_glsl.hpp>

#include <Collections/Debug>

#include <Render/Base/Shader/RawShader.hpp>
#include <Render/Base/Shader/ShaderDescriptor.hpp>

namespace Sa::GLSL
{
	void ParseResources(ShaderDescriptor& _desc,
		const spirv_cross::Compiler& _comp,
		const spirv_cross::SmallVector<spirv_cross::Resource>& _resources,
		ShaderBindingType _type)
	{
		for (auto& res : _resources)
		{
			const uint32 set = _comp.get_decoration(res.id, spv::DecorationDescriptorSet);

			ShaderBindingDescriptor& desc = _desc.EmplaceBinding(set);
			
			desc.name = res.name;
			desc.type = _type;
			desc.binding = _comp.get_decoration(res.id, spv::DecorationBinding);
			desc.inAttachIndex = _comp.get_decoration(res.id, spv::DecorationInputAttachmentIndex);


			const spirv_cross::SPIRType& type = _comp.get_type(res.type_id);
			desc.num = std::max(1u, type.array[0]);	// Always at least 1 object (non array).
		}
	}

	void ParseVertexLayout(ShaderDescriptor& _desc,
		const spirv_cross::Compiler& _comp,
		const spirv_cross::SmallVector<spirv_cross::Resource>& _resources)
	{
		for (auto& res : _resources)
		{
			const uint32 location = _comp.get_decoration(res.id, spv::DecorationLocation);

			if (location == 0u)
				_desc.vertexLayout |= VertexComp::Position;
			else if (location == 1u)
				_desc.vertexLayout |= VertexComp::Normal;
			else if (location == 2u)
				_desc.vertexLayout |= VertexComp::Tangent;
			else if (location == 3u)
				_desc.vertexLayout |= VertexComp::Texture;
		}
	}

	void ParseSpecConstants(ShaderDescriptor& _desc, const spirv_cross::Compiler& _comp)
	{
		for (auto& spec : _comp.get_specialization_constants())
		{
			SpecConstantDescriptor& specConst = _desc.specConstants.emplace_back();

			specConst.id = spec.constant_id;
			specConst.name = _comp.get_name(spec.id);
			
			//const spirv_cross::SPIRConstant& value = _comp.get_constant(spec.id);
		}

		std::sort(_desc.specConstants.begin(), _desc.specConstants.end());
	}


	bool ShaderReflector::Reflect(RawShader& _raw, ShaderDescriptor& _desc) const
	{
		if (_raw.data.empty())
		{
			SA_LOG(L"Reflect empty shader code!", Error, SA/SDK/Asset);
			return false;
		}


		const spirv_cross::CompilerGLSL glsl(_raw.data);
		const spirv_cross::ShaderResources resources = glsl.get_shader_resources();


		ParseResources(_desc, glsl, resources.uniform_buffers, ShaderBindingType::UniformBuffer);
		ParseResources(_desc, glsl, resources.storage_buffers, ShaderBindingType::StorageBuffer);
		ParseResources(_desc, glsl, resources.subpass_inputs, ShaderBindingType::InputAttachment);
		ParseResources(_desc, glsl, resources.sampled_images, ShaderBindingType::ImageSampler2D);


		// Vertex binding layout.
		if (_desc.stage == ShaderStage::Vertex)
			ParseVertexLayout(_desc, glsl, resources.stage_inputs);

		ParseSpecConstants(_desc, glsl);

		return true;
	}
}

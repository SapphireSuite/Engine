// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Shader/ShaderReflector.hpp>

#include <spirv_cross/spirv_glsl.hpp>

#include <Collections/Debug>

namespace Sa
{
	void ParseResources(RawShader& _raw,
		const spirv_cross::Compiler& _comp,
		const spirv_cross::SmallVector<spirv_cross::Resource>& _resources,
		ShaderBindingType _type)
	{
		for (auto& res : _resources)
		{
			ShaderBindingDescriptor& desc = _raw.descriptor.bindings.emplace_back();
			
			desc.type = _type;
			desc.name = res.name;
			desc.set = _comp.get_decoration(res.id, spv::DecorationDescriptorSet);
			desc.binding = _comp.get_decoration(res.id, spv::DecorationBinding);
			desc.inAttachIndex = _comp.get_decoration(res.id, spv::DecorationInputAttachmentIndex);


			const spirv_cross::SPIRType& type = _comp.get_type(res.type_id);
			desc.num = type.array[0];
		}
	}

	void ParseVertexLayout(RawShader& _raw,
		const spirv_cross::Compiler& _comp,
		const spirv_cross::SmallVector<spirv_cross::Resource>& _resources)
	{
		for (auto& res : _resources)
		{
			const uint32 location = _comp.get_decoration(res.id, spv::DecorationLocation);

			if (location == 0u)
				_raw.descriptor.vertexLayout |= VertexComp::Position;
			else if (location == 1u)
				_raw.descriptor.vertexLayout |= VertexComp::Normal;
			else if (location == 2u)
				_raw.descriptor.vertexLayout |= VertexComp::Tangent;
			else if (location == 3u)
				_raw.descriptor.vertexLayout |= VertexComp::Texture;
		}
	}

	void ParseSpecConstants(RawShader& _raw, const spirv_cross::Compiler& _comp)
	{
		for (auto& spec : _comp.get_specialization_constants())
		{
			SpecConstantDescriptor& specConst = _raw.descriptor.specConstants.emplace_back();
			
			specConst.id = spec.constant_id;
			specConst.name = _comp.get_name(spec.id);

			//const spirv_cross::SPIRConstant& value = _comp.get_constant(spec.id);
		}
	}


	bool ShaderReflector::Reflect(RawShader& _raw)
	{
		if (_raw.data.empty())
		{
			SA_LOG(L"Reflect empty shader code!", Error, SA/SDK/Asset);
			return false;
		}


		const spirv_cross::CompilerGLSL glsl(_raw.data);
		const spirv_cross::ShaderResources resources = glsl.get_shader_resources();


		ParseResources(_raw, glsl, resources.uniform_buffers, ShaderBindingType::UniformBuffer);
		ParseResources(_raw, glsl, resources.storage_buffers, ShaderBindingType::StorageBuffer);
		ParseResources(_raw, glsl, resources.subpass_inputs, ShaderBindingType::InputAttachment);
		ParseResources(_raw, glsl, resources.sampled_images, ShaderBindingType::ImageSampler2D);


		// Vertex binding layout.
		if (_raw.descriptor.stage == ShaderStage::Vertex)
			ParseVertexLayout(_raw, glsl, resources.stage_inputs);

		ParseSpecConstants(_raw, glsl);

		return true;
	}
}

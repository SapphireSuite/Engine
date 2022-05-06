// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/ShaderBuilder/GLSL/GLSLShaderReflector.hpp>

#include <spirv_cross/spirv_glsl.hpp>

#include <SA/Collections/Debug>

#include <Render/Base/Shader/RawShader.hpp>
#include <Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

namespace Sa::GLSL
{
	void ParseResources(ShaderDescriptor& _desc,
		const spirv_cross::Compiler& _comp,
		const spirv_cross::SmallVector<spirv_cross::Resource>& _resources,
		ShaderBindingType _type)
	{
		for (auto& res : _resources)
		{
			const uint32_t set = _comp.get_decoration(res.id, spv::DecorationDescriptorSet);

			ShaderBindingDescriptor& desc = _desc.EmplaceBinding(set);

			desc.name = _comp.get_name(res.id);
			desc.type = _type;
			desc.binding = _comp.get_decoration(res.id, spv::DecorationBinding);
			desc.inAttachIndex = _comp.get_decoration(res.id, spv::DecorationInputAttachmentIndex);


			const spirv_cross::SPIRType& type = _comp.get_type(res.type_id);

			if(type.basetype == spirv_cross::SPIRType::BaseType::Struct)
				desc.dataTypeName = res.name;

			desc.num = std::max(1u, type.array[0]);	// Always at least 1 object (non array).
		}
	}

	void ParseVertexLayout(ShaderDescriptor& _desc,
		const spirv_cross::Compiler& _comp,
		const spirv_cross::SmallVector<spirv_cross::Resource>& _resources)
	{
		for (auto& res : _resources)
		{
			ShaderVertexLocationDescriptor& locDesc = _desc.layout.locations.emplace_back();

			locDesc.name = _comp.get_name(res.id);
			locDesc.location = _comp.get_decoration(res.id, spv::DecorationLocation);

			const spirv_cross::SPIRType& type = _comp.get_type(res.type_id);
			locDesc.size = type.width;
		}

		// Sort by location.
		std::sort(_desc.layout.locations.begin(), _desc.layout.locations.end());
	}

	void ParsePushConstants(ShaderDescriptor& _desc,
		const spirv_cross::Compiler& _comp,
		const spirv_cross::SmallVector<spirv_cross::Resource>& _resources)
	{
		for (auto& res : _resources)
		{
			// Query only used push constants.
			auto ranges = _comp.get_active_buffer_ranges(res.id);

			for (auto& range : ranges)
			{
				ShaderPushConstantDescriptor& pConstDesc = _desc.pushConstants.emplace_back();

				pConstDesc.name = _comp.get_member_name(res.base_type_id, range.index);
				pConstDesc.size = range.range;
				pConstDesc.offset = range.offset;
			}
		}

		// Sort by offset.
		std::sort(_desc.pushConstants.begin(), _desc.pushConstants.end());
	}

	void ParseSpecConstants(ShaderDescriptor& _desc, const spirv_cross::Compiler& _comp)
	{
		for (auto& spec : _comp.get_specialization_constants())
		{
			ShaderSpecConstantDescriptor& specConst = _desc.specConstants.emplace_back();

			specConst.id = spec.constant_id;
			specConst.name = _comp.get_name(spec.id);

			//const spirv_cross::SPIRConstant& value = _comp.get_constant(spec.id);
		}

		// Sort by ID.
		std::sort(_desc.specConstants.begin(), _desc.specConstants.end());
	}


	bool ShaderReflector::Reflect(const RawShader& _raw, ShaderDescriptor& _desc) const
	{
		if (_raw.data.empty())
		{
			SA_LOG(L"Reflect empty shader code!", Error, SA/Engine/SDK/Asset);
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

		ParsePushConstants(_desc, glsl, resources.push_constant_buffers);

		ParseSpecConstants(_desc, glsl);

		return true;
	}
}

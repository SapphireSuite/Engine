// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_BINDING_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_BINDING_DESCRIPTOR_GUARD

#include <SA/Core/Serialize/Serializer.hpp>

#include <SA/Render/Base/Shader/Bindings/ShaderBindingType.hpp>

namespace Sa
{
	struct ShaderBindingDescriptor
	{
		/// Type of binding.
		ShaderBindingType type = ShaderBindingType::UniformBuffer;


		/// Binding index in shader.
		uint32 binding = 0u;

		/// Descriptor set index in shader.
		uint32 set = 0;

		/// Number of elements (array).
		uint32 num = 1u;


		/// Input Attachment index (valid only if type == InputAttachment).
		uint32 inAttachIndex = ~uint32();
	};


	namespace Serialize
	{
		template <>
		struct Specs<ShaderBindingDescriptor>
		{
			static constexpr bool bContinuousData = true;
		};
	}
}

#endif // GUARD

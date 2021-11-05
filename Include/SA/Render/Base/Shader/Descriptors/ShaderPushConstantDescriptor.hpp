// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_PUSH_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_PUSH_CONSTANT_DESCRIPTOR_GUARD

#include <string>

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	struct ShaderPushConstantDescriptor
	{
		std::string name;

		uint32 size = 0u;

		uint32 offset = 0u;

		bool operator<(const ShaderPushConstantDescriptor& _rhs) const noexcept;
	};


	namespace Serialize
	{
		void ToBinary(const ShaderPushConstantDescriptor& _obj, std::string& _str);
		void FromBinary(ShaderPushConstantDescriptor& _obj, class Reader& _read);
	}
}

#endif // GUARD

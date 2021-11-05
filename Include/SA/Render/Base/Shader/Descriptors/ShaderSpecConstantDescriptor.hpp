// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_SPEC_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_SPEC_CONSTANT_DESCRIPTOR_GUARD

#include <string>

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	struct ShaderSpecConstantDescriptor
	{
		// Serialized

		std::string name;

		uint32 id = 0u;

		bool operator<(const ShaderSpecConstantDescriptor& _rhs) const noexcept;
	};


	namespace Serialize
	{
		void ToBinary(const ShaderSpecConstantDescriptor& _obj, std::string& _str);
		void FromBinary(ShaderSpecConstantDescriptor& _obj, class Reader& _read);
	}
}

#endif // GUARD

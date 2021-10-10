// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SPEC_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SPEC_CONSTANT_DESCRIPTOR_GUARD

#include <string>

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	struct SpecConstantDescriptor
	{
		// Serialized

		std::string name;

		uint32 id = 0u;

		bool operator<(const SpecConstantDescriptor& _rhs) const noexcept;
	};


	namespace Serialize
	{
		void ToBinary(const SpecConstantDescriptor& _obj, std::string& _str);
		void FromBinary(SpecConstantDescriptor& _obj, class Reader& _read);
	}
}

#endif // GUARD

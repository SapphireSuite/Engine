// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SPEC_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SPEC_CONSTANT_DESCRIPTOR_GUARD

#include <string>
//#include <memory>

#include <SA/Render/Base/Shader/SpecConstants/SpecConstant.hpp>

namespace Sa
{
	struct SpecConstantDescriptor
	{
		// non-serialized

		SpecConstantBase* value;
		//std::unique_ptr<SpecConstantBase> value;

		// Serialized

		uint32 id = 0u;
	};


	namespace Serialize
	{
		void ToBinary(const SpecConstantDescriptor& _obj, std::string& _str);
		void FromBinary(SpecConstantDescriptor& _obj, class Reader& _read);
	}
}

#endif // GUARD

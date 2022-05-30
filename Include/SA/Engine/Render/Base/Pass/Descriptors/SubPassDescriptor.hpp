// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SUBPASS_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SUBPASS_DESCRIPTOR_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Pass/Descriptors/SampleBits.hpp>
#include <SA/Engine/Render/Base/Pass/Descriptors/SubPassAttachmentDescriptor.hpp>

namespace SA
{
	struct SubPassDescriptor
	{
		// All color attachment must have the same sample count.
		SampleBits sampling = SampleBits::Sample1Bit;

		std::vector<SubPassAttachmentDescriptor> attachmentDescs;
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const SubPassDescriptor& _desc, std::string& _dst);

		template <>
		bool FromBinary(SubPassDescriptor& _desc, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD

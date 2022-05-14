// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SUBPASS_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SUBPASS_DESCRIPTOR_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Misc/Format.hpp>
#include <SA/Engine/Render/Base/Misc/Color.hpp>

#include <SA/Engine/Render/Base/Pass/SampleBits.hpp>

namespace SA
{
	enum class AttachmentLoadMode
	{
		None,

		Load,

		Clear,
	};

	struct SubPassAttachmentDescriptor
	{
		Format format = Format::RGBA_32;

		// Used as input attachment in next subpass.
		bool bInputNext = false;

		AttachmentLoadMode loadMode = AttachmentLoadMode::Clear;
		Color clearColor = Color{ 0.0f, 0.0f, 0.05f, 0.0f };
	};

	struct SubPassDescriptor
	{
		// All color attachment must have the same sample count.
		SampleBits sampling = SampleBits::Sample1Bit;

		std::vector<SubPassAttachmentDescriptor> attachmentDescs;
	};


#if SA_VULKAN

	namespace VK
	{
		VkAttachmentLoadOp API_GetAttachmentLoadOp(const AttachmentLoadMode _mode) noexcept;
	}

#endif
}

#endif // GUARD

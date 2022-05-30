// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SUB_PASS_ATTACHMENT_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SUB_PASS_ATTACHMENT_DESCRIPTOR_GUARD

#include <SA/Collections/SerializeBinary>

#include <SA/Engine/Render/Base/Misc/Format.hpp>
#include <SA/Engine/Render/Base/Misc/Color.hpp>

#include <SA/Engine/Render/Base/Pass/Descriptors/SubPassAttachmentLoadMode.hpp>

namespace SA
{
	struct SubPassAttachmentDescriptor
	{
		Format format;

		// Used as input attachment in next subpass.
		bool bInputNext = false;

		AttachmentLoadMode loadMode = AttachmentLoadMode::Clear;
		Color clearColor = Color{ 0.0f, 0.0f, 0.05f, 0.0f };
	};


	namespace Ser
	{
		template <>
		struct TypeSpecs<SubPassAttachmentDescriptor>
		{
			static constexpr bool bContinuousData = true;
		};
	}
}

#endif // GUARD

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pass/RenderPassDescriptor.hpp>

#include <Render/Base/Surface/ARenderSurface.hpp>

namespace SA
{
	RenderPassDescriptor RenderPassDescriptor::DefaultSingle(const ARenderSurface* _surface)
	{
		RenderPassDescriptor result{};

		result.subPassDescs.reserve(1u);

		// === Main Subpass ===
		{
			SubPassDescriptor& mainSubpassDesc = result.subPassDescs.emplace_back();
			mainSubpassDesc.sampling = SampleBits::Sample8Bits;

			mainSubpassDesc.attachmentDescs.reserve(2u);


			// Color and present attachment.
			SubPassAttachmentDescriptor& colorAttachDesc = mainSubpassDesc.attachmentDescs.emplace_back();
			colorAttachDesc.format = _surface ? _surface->GetFormat() : Format(FormatType::RGBA_32, FormatFlags::sRGB);


			// Depth attachment.
			SubPassAttachmentDescriptor& depthAttachDesc = mainSubpassDesc.attachmentDescs.emplace_back();
			depthAttachDesc.format.type = FormatType::Depth_16;
		}

		return result;
	}

	RenderPassDescriptor RenderPassDescriptor::DefaultPBR(const ARenderSurface* _surface)
	{
		RenderPassDescriptor result{};

		result.subPassDescs.reserve(2u);

		// === PBR Subpass ===
		{
			SubPassDescriptor& pbrSubpassDesc = result.subPassDescs.emplace_back();
			pbrSubpassDesc.sampling = SampleBits::Sample8Bits;

			// Deferred position attachment.
			SubPassAttachmentDescriptor& posAttachDesc = pbrSubpassDesc.attachmentDescs.emplace_back();
			posAttachDesc.bInputNext = true;

			// Deferred normal attachment.
			SubPassAttachmentDescriptor& normAttachDesc = pbrSubpassDesc.attachmentDescs.emplace_back();
			normAttachDesc.bInputNext = true;

			// Deferred albedo attachment.
			SubPassAttachmentDescriptor& albedoAttachDesc = pbrSubpassDesc.attachmentDescs.emplace_back();
			albedoAttachDesc.bInputNext = true;

			// Deferred PBR (Metallic, Roughness, Ambiant occlusion) attachment.
			SubPassAttachmentDescriptor& pbrAttachDesc = pbrSubpassDesc.attachmentDescs.emplace_back();
			pbrAttachDesc.bInputNext = true;

			SubPassAttachmentDescriptor& depthAttachDesc = pbrSubpassDesc.attachmentDescs.emplace_back();
			depthAttachDesc.format.type = FormatType::Depth_16;
		}


		// === Present Subpass ===
		{
			SubPassDescriptor& presentSubpassDesc = result.subPassDescs.emplace_back();
			presentSubpassDesc.sampling = SampleBits::Sample8Bits;

			SubPassAttachmentDescriptor& presentAttachDesc = presentSubpassDesc.attachmentDescs.emplace_back();
			presentAttachDesc.format = _surface ? _surface->GetFormat() : Format(FormatType::RGBA_32, FormatFlags::sRGB);
		}


		return result;
	}
}

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_PIPELINE_GUARD
#define SAPPHIRE_ENGINE_VK_PIPELINE_GUARD

#include <SA/Support/API/Vulkan.hpp>

#include <SA/Engine/Render/Base/Pipeline/ARenderPipeline.hpp>

namespace SA::VK
{
	class Device;
	class PipelineLayout;

	class Pipeline : public ARenderPipeline
	{
		VkPipeline mHandle = VK_NULL_HANDLE;

		using ARenderPipeline::Create; // overloaded.
		using ARenderPipeline::Destroy; // overloaded.

	public:
		void Create(const Device& _device, const RenderPipelineDescriptor& _desc, const PipelineLayout& _layout);
		void Destroy(const Device& _device);

		void Bind(ARenderFrame& _frame) override final;
	};
}

#endif // GUARD

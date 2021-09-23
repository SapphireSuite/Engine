// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDERPASS_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RENDERPASS_DESCRIPTOR_GUARD

#include <SA/Render/Base/Pass/SubPassDescriptor.hpp>

namespace Sa
{
	class ARenderSurface;

	class RenderPassDescriptor
	{
	public:
		std::vector<SubPassDescriptor> subPassDescs;

		/**
		*	\brief Create a default single-pass forward rendering renderpass descriptor.
		*/
		static RenderPassDescriptor DefaultSingle(const ARenderSurface* _surface = nullptr);

		/**
		*	\brief Create a default multi-pass PBR deferred rendering renderpass descriptor.
		*/
		static RenderPassDescriptor DefaultPBR(const ARenderSurface* _surface = nullptr);
	};
}

#endif // GUARD

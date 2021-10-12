// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDERPASS_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RENDERPASS_DESCRIPTOR_GUARD

#include <SA/Render/Base/Pass/SubPassDescriptor.hpp>

namespace Sa
{
	class ARenderSurface;

	struct RenderPassDescriptor
	{
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


	namespace Serialize
	{
		void ToBinary(const RenderPassDescriptor& _obj, std::string& _str);
		void FromBinary(RenderPassDescriptor& _obj, class Reader& _read);
	}
}

#endif // GUARD

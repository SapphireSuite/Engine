// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RENDERPASS_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_RENDERPASS_DESCRIPTOR_GUARD

#include <SA/Engine/Render/Base/Pass/Descriptors/SubPassDescriptor.hpp>

namespace SA
{
	class ARenderSurface;

	struct RenderPassDescriptor
	{
		std::vector<SubPassDescriptor> subPassDescs;


		void Clear();


		/**
		*	\brief Create a default single-pass forward rendering renderpass descriptor.
		*/
		static RenderPassDescriptor DefaultSingle(const ARenderSurface* _surface = nullptr);

		/**
		*	\brief Create a default multi-pass PBR deferred rendering renderpass descriptor.
		*/
		static RenderPassDescriptor DefaultPBR(const ARenderSurface* _surface = nullptr);
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const RenderPassDescriptor& _desc, std::string& _dst);

		template <>
		bool FromBinary(RenderPassDescriptor& _desc, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD

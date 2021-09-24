// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_SURFACE_GUARD
#define SAPPHIRE_RENDER_ARENDER_SURFACE_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Misc/Format.hpp>

namespace Sa
{
	class ARenderSystem;
	class ARenderDevice;

	class ARenderPass;
	struct RenderPassDescriptor;

	class ARenderSurface : public Abstract
	{
	public:
		virtual Format GetFormat() const = 0;

		virtual void Create(const ARenderDevice* _device) = 0;
		virtual void Destroy(const ARenderDevice* _device) = 0;

		virtual void CreateFrameBuffers(const ARenderDevice* _device, const ARenderPass* _renderPass, const RenderPassDescriptor& _renderPassDesc) = 0;
		virtual void DestroyFrameBuffers(const ARenderDevice* _device) = 0;
	};
}

#endif // GUARD

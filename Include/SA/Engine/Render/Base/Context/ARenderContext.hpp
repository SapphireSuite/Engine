// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_CONTEXT_GUARD
#define SAPPHIRE_ENGINE_ARENDER_CONTEXT_GUARD

#include <SA/Engine/Render/Base/Surface/ARenderSurface.hpp>
#include <SA/Engine/Render/Base/Pass/ARenderPass.hpp>
#include <SA/Engine/Render/Base/Context/ARenderResourceInitializer.hpp>

namespace Sa
{
	class AWindowSurface;

	class ARenderContext : protected HardwareInterface
	{
	public:
		virtual ARenderSurface* CreateSurface(AWindowSurface* _winSurface) = 0;
		virtual void DestroySurface(ARenderSurface* _surface) = 0;

		virtual ARenderPass* CreateRenderPass(const RenderPassDescriptor& _desc) = 0;
		virtual void DestroyRenderPass(ARenderPass* _pass) = 0;

		virtual void CreateFrameBuffers(ARenderSurface* _surface, ARenderPass* _pass, const RenderPassDescriptor& _desc) = 0;
		virtual void DestroyFrameBuffers(ARenderSurface* _surface) = 0;


		virtual ARenderResourceInitializer* CreateResourceInitializer() = 0;
		virtual void DestroyResourceInitializer(ARenderResourceInitializer* _resInit) = 0;
	};
}

#endif // GUARD

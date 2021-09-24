// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_SYSTEM_GUARD
#define SAPPHIRE_RENDER_ARENDER_SYSTEM_GUARD

#include <SA/Core/Types/Abstract.hpp>

namespace Sa
{
	class AWindowSystem;
	class AWindow;

	class ARenderDevice;
	struct AGraphicDeviceInfos;

	class ARenderSurface;

	class ARenderPass;
	struct RenderPassDescriptor;

	class ARenderPipeline;
	struct RenderPipelineCreateInfos;

	class ARenderResourceInitializer;

	class AShader;
	struct RawShader;

	class ATexture;
	struct RawTexture;


	class ARenderSystem : public Abstract
	{
	public:
		virtual void Create(const AWindowSystem& _winSys) = 0;
		virtual void Destroy() = 0;

		virtual ARenderDevice* CreateDevice(const AGraphicDeviceInfos& _infos) = 0;
		virtual void DestroyDevice(ARenderDevice* _device) = 0;

		virtual ARenderSurface* CreateWindowSurface(AWindow& _win) = 0;
		virtual void DestroyWindowSurface(AWindow& _win, ARenderSurface* _surface) = 0;

		virtual ARenderPass* CreateRenderPass(ARenderDevice* _device, const RenderPassDescriptor& _descriptor) = 0;
		virtual void DestroyRenderPass(ARenderDevice* _device, ARenderPass* _pass) = 0;

		virtual ARenderPipeline* CreatePipeline(ARenderDevice* _device, const RenderPipelineCreateInfos& _infos) = 0;
		virtual void DestroyPipeline(ARenderDevice* _device, ARenderPipeline* _pipeline) = 0;

		virtual ARenderResourceInitializer* CreateResourceInitializer(ARenderDevice* _device);
		virtual void DestroyResourceInitializer(ARenderResourceInitializer* _init);

		virtual AShader* CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw) = 0;
		virtual void DestroyShader(ARenderDevice* _device, AShader* _shader) = 0;

		virtual ATexture* CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw) = 0;
		virtual void DestroyTexture(ARenderDevice* _device, ATexture* _texture) = 0;
	};
}

#endif // GUARD

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
	struct RenderPipelineDescriptor;

	class ARenderResourceInitializer;

	class AShader;
	struct RawShader;

	class AStaticMesh;
	struct RawMesh;

	class ATexture;
	struct RawTexture;

	class ACubemap;
	struct RawCubemap;

	class ARenderMaterial;
	struct RenderMaterialCreateInfos;

	class ACamera;


	class ARenderSystem : public Abstract
	{
	public:
		virtual void Create(const AWindowSystem& _winSys) = 0;
		virtual void Destroy() = 0;

		virtual ARenderDevice* CreateDevice(const AGraphicDeviceInfos& _infos) = 0;
		virtual void DestroyDevice(ARenderDevice* _device) = 0;

		virtual ARenderSurface* MakeWindowSurface(AWindow* _win) = 0;
		virtual void DestroyWindowSurface(AWindow* _win, const ARenderDevice* _device, ARenderSurface* _surface) = 0;

		virtual ARenderPass* CreateRenderPass(const ARenderDevice* _device, const RenderPassDescriptor& _descriptor) = 0;
		virtual void DestroyRenderPass(const ARenderDevice* _device, ARenderPass* _pass) = 0;

		virtual ARenderPipeline* CreatePipeline(const ARenderDevice* _device, const RenderPipelineDescriptor& _desc) = 0;
		virtual void DestroyPipeline(const ARenderDevice* _device, ARenderPipeline* _pipeline) = 0;

//{ Resources

		virtual ARenderResourceInitializer* CreateResourceInitializer(const ARenderDevice* _device);
		virtual void DestroyResourceInitializer(ARenderResourceInitializer* _init);

		virtual AShader* CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw) = 0;
		virtual void DestroyShader(const ARenderDevice* _device, AShader* _shader) = 0;

		virtual AStaticMesh* CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw) = 0;
		virtual void DestroyStaticMesh(const ARenderDevice* _device, AStaticMesh* _mesh) = 0;

		virtual ATexture* CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw) = 0;
		virtual void DestroyTexture(const ARenderDevice* _device, ATexture* _texture) = 0;

		virtual ACubemap* CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw) = 0;
		virtual void DestroyCubemap(const ARenderDevice* _device, ACubemap* _cubemap) = 0;


		virtual ARenderMaterial* CreateMaterial(const ARenderDevice* _device, const RenderMaterialCreateInfos& _infos) = 0;
		virtual void DestroyMaterial(const ARenderDevice* _device, ARenderMaterial* _material) = 0;

		virtual ACamera* CreateCamera(const ARenderDevice* _device);
		virtual void DestroyCamera(const ARenderDevice* _device, ACamera* _camera);

//}
	};
}

#endif // GUARD

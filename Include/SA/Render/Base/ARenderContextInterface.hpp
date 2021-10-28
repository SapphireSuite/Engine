// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_CONTEXT_INTERFACE_GUARD
#define SAPPHIRE_RENDER_ARENDER_CONTEXT_INTERFACE_GUARD

#include <SA/Render/Base/Surface/WindowSurfaceHandle.hpp>
#include <SA/Render/Base/Surface/RenderSurfaceHandle.hpp>
#include <SA/Render/Base/Pass/RenderPassHandle.hpp>
#include <SA/Render/Base/Pass/RenderPassDescriptor.hpp>

//#include <SA/Render/Base/Surface/AWindowSurface.hpp>
//#include <SA/Render/Base/Pass/ARenderPass.hpp>
//#include <SA/Render/Base/Pipeline/ARenderPipeline.hpp>
//#include <SA/Render/Base/ARenderResourceInitializer.hpp>
//#include <SA/Render/Base/Mesh/AStaticMesh.hpp>
//#include <SA/Render/Base/Texture/ATexture.hpp>
//#include <SA/Render/Base/Texture/ACubemap.hpp>
//#include <SA/Render/Base/Material/ARenderMaterial.hpp>
//#include <SA/Render/Base/Camera/ACamera.hpp>
//
//#include <SA/Render/Base/Shader/ShaderHandle.hpp>
//#include <SA/Render/Base/Shader/RawShader.hpp>

namespace Sa
{
	class ARenderContextInterface
	{
	public:
		virtual ~ARenderContextInterface() = default;

		//virtual void Create() = 0;
		virtual void Destroy() = 0;

		virtual RenderSurfaceHandle CreateSurface(WindowSurfaceHandle _winHandle) = 0;
		virtual void DestroySurface(RenderSurfaceHandle& _handle) = 0;

		virtual RenderPassHandle CreateRenderPass(const RenderPassDescriptor& _descriptor) = 0;
		virtual void DestroyRenderPass(RenderPassHandle& _handle) = 0;

		virtual void CreateFrameBuffers(const RenderSurfaceHandle& _surface,
			const RenderPassHandle& _pass,
			const RenderPassDescriptor& _descriptor) = 0;
		virtual void DestroyFrameBuffers(const RenderSurfaceHandle& _surface) = 0;

		//virtual ARenderPipeline* CreatePipeline(const RenderPipelineDescriptor& _desc) = 0;
		//virtual void DestroyPipeline(ARenderPipeline* _pipeline) = 0;

//{ Resources

		//virtual ARenderResourceInitializer* CreateResourceInitializer() = 0;
		//virtual void DestroyResourceInitializer(ARenderResourceInitializer* _init) = 0;
		//virtual void SubmitResourceInitializer(ARenderResourceInitializer* _init) = 0;

		//virtual ShaderHandle CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw) = 0;
		//virtual void DestroyShader(ShaderHandle _shader) = 0;

		//virtual AStaticMesh* CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw) = 0;
		//virtual void DestroyStaticMesh(AStaticMesh* _mesh) = 0;

		//virtual ATexture* CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw) = 0;
		//virtual void DestroyTexture(ATexture* _texture) = 0;

		//virtual ACubemap* CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw) = 0;
		//virtual void DestroyCubemap(ACubemap* _cubemap) = 0;


		//virtual ARenderMaterial* CreateMaterial(const RenderMaterialCreateInfos& _infos) = 0;
		//virtual void DestroyMaterial(ARenderMaterial* _material) = 0;

		//virtual ACamera* CreateCamera() = 0;
		//virtual void DestroyCamera(ACamera* _camera) = 0;

//}
	};
}

#endif // GUARD
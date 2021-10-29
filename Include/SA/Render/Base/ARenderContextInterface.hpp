// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_CONTEXT_INTERFACE_GUARD
#define SAPPHIRE_RENDER_ARENDER_CONTEXT_INTERFACE_GUARD

#include <SA/Render/Base/Surface/WindowSurfaceHandle.hpp>
#include <SA/Render/Base/Surface/ARenderSurface.hpp>
//#include <SA/Render/Base/Surface/RenderSurfaceHandle.hpp>
#include <SA/Render/Base/Pass/RenderPassHandle.hpp>
#include <SA/Render/Base/Pass/RenderPassDescriptor.hpp>
#include <SA/Render/Base/RenderResourceInitializerHandle.hpp>
#include <SA/Render/Base/Shader/ShaderHandle.hpp>
#include <SA/Render/Base/Shader/RawShader.hpp>
#include <SA/Render/Base/Texture/TextureHandle.hpp>
#include <SA/Render/Base/Texture/RawTexture.hpp>
#include <SA/Render/Base/Texture/CubemapHandle.hpp>
#include <SA/Render/Base/Texture/RawCubemap.hpp>

//#include <SA/Render/Base/Pipeline/ARenderPipeline.hpp>
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

		//virtual RenderPassHandle CreateRenderPass(const RenderPassDescriptor& _descriptor) = 0;
		//virtual void DestroyRenderPass(RenderPassHandle& _handle) = 0;

		//virtual void CreateFrameBuffers(const RenderSurfaceHandle& _surface,
		//	const RenderPassHandle& _pass,
		//	const RenderPassDescriptor& _descriptor) = 0;
		//virtual void DestroyFrameBuffers(const RenderSurfaceHandle& _surface) = 0;

		//virtual ARenderPipeline* CreatePipeline(const RenderPipelineDescriptor& _desc) = 0;
		//virtual void DestroyPipeline(ARenderPipeline* _pipeline) = 0;

//{ Resources

		//virtual RenderResourceInitializerHandle CreateResourceInitializer() = 0;
		//virtual void DestroyResourceInitializer(RenderResourceInitializerHandle& _init) = 0;
		//virtual void SubmitResourceInitializer(const RenderResourceInitializerHandle& _init) = 0;

		//virtual ShaderHandle CreateShader(const RenderResourceInitializerHandle& _init,
		//	const RawShader& _raw) = 0;
		//virtual void DestroyShader(ShaderHandle& _shader) = 0;

		//virtual AStaticMesh* CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw) = 0;
		//virtual void DestroyStaticMesh(AStaticMesh* _mesh) = 0;

		//virtual TextureHandle CreateTexture(const RenderResourceInitializerHandle& _init, const RawTexture& _raw) = 0;
		//virtual void DestroyTexture(TextureHandle& _texture) = 0;

		//virtual CubemapHandle CreateCubemap(const RenderResourceInitializerHandle& _init, const RawCubemap& _raw) = 0;
		//virtual void DestroyCubemap(CubemapHandle& _cubemap) = 0;


		//virtual ARenderMaterial* CreateMaterial(const RenderMaterialCreateInfos& _infos) = 0;
		//virtual void DestroyMaterial(ARenderMaterial* _material) = 0;

		//virtual ACamera* CreateCamera() = 0;
		//virtual void DestroyCamera(ACamera* _camera) = 0;

//}
	};
}

#endif // GUARD

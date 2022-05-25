// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_CONTEXT_GUARD
#define SAPPHIRE_ENGINE_ARENDER_CONTEXT_GUARD

#include <SA/Engine/Render/Base/ARenderFrame.hpp>
#include <SA/Engine/Render/Base/Surface/ARenderSurface.hpp>
#include <SA/Engine/Render/Base/Pass/ARenderPass.hpp>
#include <SA/Engine/Render/Base/Context/ARenderResourceInitializer.hpp>
#include <SA/Engine/Render/Base/Shader/AShader.hpp>
#include <SA/Engine/Render/Base/Mesh/AStaticMesh.hpp>
#include <SA/Engine/Render/Base/Texture/ATexture.hpp>
#include <SA/Engine/Render/Base/Texture/ACubemap.hpp>
#include <SA/Engine/Render/Base/Pipeline/ARenderPipelineLayout.hpp>
#include <SA/Engine/Render/Base/Pipeline/ARenderPipeline.hpp>
#include <SA/Engine/Render/Base/Material/ARenderMaterial.hpp>

namespace SA
{
	class AWindowSurface;

	class ARenderContext : protected HardwareInterface
	{
	public:

//{ Surface

		virtual ARenderSurface* CreateSurface(AWindowSurface* _winSurface) = 0;
		virtual void DestroySurface(ARenderSurface* _surface) = 0;

		virtual void CreateFrameBuffers(ARenderSurface* _surface, ARenderPass* _pass, const RenderPassDescriptor& _desc) = 0;
		virtual void DestroyFrameBuffers(ARenderSurface* _surface) = 0;

		virtual ARenderFrame& BeginSurface(ARenderSurface* _surface) = 0;
		virtual void EndSurface(ARenderSurface* _surface) = 0;

//}


		virtual ARenderPass* CreateRenderPass(const RenderPassDescriptor& _desc) = 0;
		virtual void DestroyRenderPass(ARenderPass* _pass) = 0;


//{ Resources

		virtual ARenderResourceInitializer* CreateResourceInitializer() = 0;
		virtual void DestroyResourceInitializer(ARenderResourceInitializer* _resInit) = 0;
		virtual void SubmitResourceInitializer(ARenderResourceInitializer* _init) = 0;

		virtual AShader* CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw) = 0;
		virtual void DestroyShader(AShader* _shader) = 0;

		virtual AStaticMesh* CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw) = 0;
		virtual void DestroyStaticMesh(AStaticMesh* _mesh) = 0;

		virtual ATexture* CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw) = 0;
		virtual void DestroyTexture(ATexture* _texture) = 0;

		virtual ACubemap* CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw) = 0;
		virtual void DestroyCubemap(ACubemap* _texture) = 0;


		virtual ARenderPipelineLayout* CreatePipelineLayout(const RenderPipelineLayoutDescriptor& _desc) = 0;
		virtual void DestroyPipelineLayout(ARenderPipelineLayout* _pipLayout) = 0;

		virtual ARenderPipeline* CreatePipeline(const RenderPipelineDescriptor& _desc, const ARenderPipelineLayout* _pipLayout) = 0;
		virtual void DestroyPipeline(ARenderPipeline* _pip) = 0;


		virtual ARenderMaterial* CreateMaterial(const RenderPipelineLayoutDescriptor& _pipLayout,
			const RenderMaterialBindings& _bindings = RenderMaterialBindings()) = 0;
		virtual void DestroyMaterial(ARenderMaterial* _mat) = 0;
//}
	};
}

#endif // GUARD

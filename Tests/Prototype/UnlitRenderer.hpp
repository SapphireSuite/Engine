// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPIHRE_ENGINE_PROTO_UNLIT_RENDERER_GUARD
#define SAPPIHRE_ENGINE_PROTO_UNLIT_RENDERER_GUARD

#include "AssetLibraryHelper.hpp"

namespace SA
{
	class UnlitRenderer
	{
	public:
		AShader* vertShader = nullptr;
		AShader* fragShader = nullptr;

		ARenderPipelineLayout* pipLayout = nullptr;
		ARenderPipeline* pipeline = nullptr;

		void Create(ARenderContext* _renderContext,
			ARenderPass* _renderPass,
			const RenderPassDescriptor& _renderPassDesc,
			uint32_t _subPassIndex = 0u)
		{
			RenderPipelineDescriptor pipDesc;
			RenderPipelineLayoutDescriptor pipLayoutDesc;
			
			ARenderResourceInitializer* const resInit = _renderContext->CreateResourceInitializer();

			// Vertex Shader
			LoadImportCreateShader(_renderContext,
				resInit,
				vertShader,
				pipDesc,
				pipLayoutDesc,
				"Bin/Assets/Shaders/Forward/unlit_vert.spha",
				"Resources/Shaders/Forward/unlit.vert"
			);

			// Fragment Shader
			LoadImportCreateShader(_renderContext,
				resInit,
				fragShader,
				pipDesc,
				pipLayoutDesc,
				"Bin/Assets/Shaders/Forward/unlit_frag.spha",
				"Resources/Shaders/Forward/unlit.frag"
			);


			pipLayout = _renderContext->CreatePipelineLayout(pipLayoutDesc);

			pipDesc.passInfos.SetRenderPass(_renderPass, _renderPassDesc, _subPassIndex);
			pipDesc.shaderInfos.vertexLayoutDesc.BindVertexComponents<VertexPNTT, VertexPosition, VertexTexture>();
			pipeline = _renderContext->CreatePipeline(pipDesc, pipLayout);
		}

		void Destroy(ARenderContext* _renderContext)
		{
			_renderContext->DestroyPipeline(pipeline);
			pipeline = nullptr;

			_renderContext->DestroyPipelineLayout(pipLayout);
			pipLayout = nullptr;

			_renderContext->DestroyShader(vertShader);
			vertShader = nullptr;

			_renderContext->DestroyShader(fragShader);
			fragShader = nullptr;
		}
	};
}

#endif // GUARD

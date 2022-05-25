// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PROTO_ASSET_LIBRARY_HELPER_GUARD
#define SAPPHIRE_ENGINE_PROTO_ASSET_LIBRARY_HELPER_GUARD

#include <SA/Collections/Debug>
#include <SA/Collections/Render>

#include <SA/Engine/SDK/Assets/Render/ShaderAsset.hpp>
#include <SA/Engine/SDK/Assets/Render/TextureAsset.hpp>

namespace SA
{
	template <typename T>
	T LoadImportSaveAsset(const std::string& _assetPath, const std::string& _resPath)
	{
		T asset;

		if(!asset.Load(_assetPath))
		{
			if(asset.Import(_resPath))
				asset.Save(_assetPath);
			else
				SA_LOG(L"Import {" << _resPath << L"} Failed", Error, SA/Engine/Prototype);
		}

		return asset;
	}

	AShader* LoadImportSaveCreateShader(
		ARenderContext* _renderContext,
		ARenderResourceInitializer* _resInit, 
		RenderPipelineDescriptor& _pipDesc,
		RenderPipelineLayoutDescriptor& _pipLayoutDesc,
		const std::string& _assetPath,
		const std::string& _resPath)
	{
		SDK::ShaderAsset asset = LoadImportSaveAsset<SDK::ShaderAsset>(_assetPath, _resPath);

		AShader* shader = _renderContext->CreateShader(_resInit, asset.raw);
		_pipDesc.shaderInfos.AddShader(shader, asset.descriptor);
		_pipLayoutDesc.AddShader(asset.descriptor);

		return shader;
	}

	ATexture* LoadImportSaveCreateTexture(
		ARenderContext* _renderContext,
		ARenderResourceInitializer* _resInit,
		const std::string& _assetPath,
		const std::string& _resPath)
	{
		SDK::TextureAsset asset = LoadImportSaveAsset<SDK::TextureAsset>(_assetPath, _resPath);

		ATexture* const texture = _renderContext->CreateTexture(_resInit, asset.raw);
		
		return texture;
	}
}

#endif // GUARD

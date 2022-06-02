// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PROTO_ASSET_LIBRARY_HELPER_GUARD
#define SAPPHIRE_ENGINE_PROTO_ASSET_LIBRARY_HELPER_GUARD

#include <SA/Collections/Debug>
#include <SA/Collections/Render>
#include <SA/Collections/Assets>

namespace SA
{
	AShader* LoadImportSaveCreateShader(
		SDK::AssetMgr& _assetMgr,
		ARenderContext* _renderContext,
		ARenderResourceInitializer* _resInit, 
		PipelineDescriptor& _pipDesc,
		PipelineLayoutDescriptor& _pipLayoutDesc,
		const std::string& _assetPath,
		const std::string& _resPath)
	{
		std::shared_ptr<SDK::ShaderAsset> asset = _assetMgr.LoadOrImport<SDK::ShaderAsset>(_assetPath, _resPath);

		AShader* shader = nullptr;

		if(asset)
		{
			shader = _renderContext->CreateShader(_resInit, asset->raw);
			_pipDesc.shaderInfos.AddShader(shader, asset->descriptor);
			_pipLayoutDesc.AddShader(asset->descriptor);
		}

		return shader;
	}

	ATexture* LoadImportSaveCreateTexture(
		SDK::AssetMgr& _assetMgr,
		ARenderContext* _renderContext,
		ARenderResourceInitializer* _resInit,
		const std::string& _assetPath,
		const std::string& _resPath)
	{
		std::shared_ptr<SDK::TextureAsset> asset = _assetMgr.LoadOrImport<SDK::TextureAsset>(_assetPath, _resPath);

		ATexture* texture = nullptr;

		if(asset)
			texture = _renderContext->CreateTexture(_resInit, asset->raw);
		
		return texture;
	}


	// AStaticMesh* LoadImportSaveCreateMesh(
	// 	ARenderContext* _renderContext,
	// 	ARenderResourceInitializer* _resInit,
	// 	const std::string& _assetPath,
	// 	const std::string& _resPath)
	// {
	// 	SDK::MeshAsset meshAsset;

	// 	if(!meshAsset.Load(_assetPath))
	// 	{
	// 		SDK::ModelAsset modelAsset;

	// 		if(modelAsset.Import(_resPath))
	// 		{
	// 			meshAsset = modelAsset.meshes[0];
	// 			meshAsset.Save(_assetPath);
	// 		}
	// 		else
	// 			SA_LOG(L"Import {" << _resPath << L"} Failed", Error, SA/Engine/Prototype);
	// 	}


	// 	AStaticMesh* const mesh = _renderContext->CreateStaticMesh(_resInit, meshAsset.raw);
		
	// 	return mesh;
	// }
}

#endif // GUARD

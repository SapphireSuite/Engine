// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MODEL_ASSET_GUARD
#define SAPPHIRE_ENGINE_MODEL_ASSET_GUARD

#include <vector>

#include <SA/Engine/SDK/Assets/AssetMgr.hpp>
#include <SA/Engine/SDK/Assets/AssetHandle.hpp>

#include <SA/Engine/SDK/Assets/Render/ModelNode.hpp>
#include <SA/Engine/SDK/Assets/Render/MeshAsset.hpp>

// Assimp node.
struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

namespace SA::SDK
{
	class ModelAsset : public ARenderAsset
	{
		bool ParseScene(AssetMgr& _mgr, const std::string& _savedPath, const aiScene* _aiScene);
		bool ParseNode(AssetMgr& _mgr, const std::string& _savedPath, const aiScene* _aiScene, const aiNode* _aiNode);
		bool ParseSkeleton(AssetMgr& _mgr, const std::string& _savedPath, const aiMesh* aiMesh);
		bool ParseMaterial(AssetMgr& _mgr, const std::string& _savedPath, const aiMaterial* aiMat);
		bool ParseAnimations(AssetMgr& _mgr, const std::string& _savedPath, const aiScene* _aiScene);

		bool Load(AssetMgr& _mgr, const std::string& _path, std::string&& _bin) override final;
		bool Save(AssetMgr& _mgr, const std::string& _path, std::string& _bin) const override final;

	public:
		std::vector<ModelNode> nodes;

		bool Import(AssetMgr& _mgr, const std::string& _path);
	};


//{ Handle

	template <>
	class AssetHandle<ModelAsset> : public AssetHandleBase<ModelAsset>
	{
	public:
		using AssetHandleBase<ModelAsset>::AssetHandleBase;

		AssetHandle<MeshAsset> GetMesh(uint32_t _index);
		AssetHandle<MeshAsset> GetMesh(const std::string& _path);
	};

//}
}

#endif // GUARD

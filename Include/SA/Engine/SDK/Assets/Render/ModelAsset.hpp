// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MODEL_ASSET_GUARD
#define SAPPHIRE_ENGINE_MODEL_ASSET_GUARD

#include <vector>

#include <SA/Engine/SDK/Assets/Render/MeshAsset.hpp>

// Assimp node.
struct aiScene;
struct aiNode;

namespace SA::SDK
{
	class ModelAsset : public ARenderAsset
	{
	// 	bool ParseScene(const aiScene* _scene);
	// 	bool ParseNode(const aiScene* _scene, const aiNode* _node);

	// 	bool Load_Internal(std::string&& _bin) override final;
	// 	bool Save_Internal(std::fstream& _fstream) const override final;

	// public:
	// 	std::vector<MeshAsset> meshes;

	// 	bool IsValid() const override final;

	// 	void UnLoad() override final;

	// 	bool Import(const std::string& _path);
	};
}

#endif // GUARD

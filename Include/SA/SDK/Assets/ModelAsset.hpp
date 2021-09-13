// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_MODEL_ASSET_GUARD
#define SAPPHIRE_SDK_MODEL_ASSET_GUARD

#include <SA/SDK/Assets/AAsset.hpp>
#include <SA/SDK/Assets/MeshAsset.hpp>

// Assimp node.
struct aiScene;
struct aiNode;

namespace Sa
{
	class ModelAsset : public AAsset
	{
		bool ParseScene(const aiScene* _scene);
		bool ParseNode(const aiScene* _scene, const aiNode* _node);

	public:
		std::vector<MeshAsset> meshes;


		bool IsValid() const override final;

		bool Load(const std::string& _path) override final;
		void UnLoad() override final;

		bool Save(const std::string& _path) const override final;

		bool Import(const std::string& _path) override final;
	};
}

#endif // GUARD

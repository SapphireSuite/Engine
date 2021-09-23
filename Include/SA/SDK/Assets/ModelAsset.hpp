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

	protected:
		bool Load_Internal(std::string&& _bin) override final;
		bool Save_Internal(std::fstream& _fStream) const override final;
		bool Import_Internal(const std::string& _path) override final;

	public:
		std::vector<MeshAsset> meshes;


		bool IsValid() const override final;

		void UnLoad() override final;
	};
}

#endif // GUARD

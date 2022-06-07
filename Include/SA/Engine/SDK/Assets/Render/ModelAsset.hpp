// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MODEL_ASSET_GUARD
#define SAPPHIRE_ENGINE_MODEL_ASSET_GUARD

#include <vector>

#include <SA/Engine/SDK/Assets/Render/ARenderAsset.hpp>

#include <SA/Maths/Matrix/Matrix4.hpp>

// Assimp.
struct aiScene;
struct aiNode;


namespace SA::SDK
{
	class ModelAsset : public ARenderAsset
	{
	public:
		struct Node
		{
			Mat4f trMat;
			std::vector<std::string> meshPaths;

			std::vector<Node> children;
		};

		Node root;

//{ Import

		struct ImportInfos : public ARenderAsset::ImportInfos
		{
		};


		bool Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos);

	private:
		bool ParseScene(AssetMgr& _mgr, const std::string& _outBasePath, const aiScene* _aiScene);
		bool ParseNode(AssetMgr& _mgr, Node& _node, const std::string& _outBasePath, const aiScene* _aiScene, const aiNode* _aiNode);
		bool ParseAnimations(AssetMgr& _mgr, const std::string& _outBasePath, const aiScene* _aiScene);

//}

	};
}

#endif // GUARD

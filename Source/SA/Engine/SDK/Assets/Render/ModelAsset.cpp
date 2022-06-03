// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/ModelAsset.hpp>

#include <SA/Collections/Debug>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <SDK/Assets/AssetMgr.hpp>

namespace SA::SDK
{
//{ Load

	bool ModelAsset::Load(AssetMgr& _mgr, const std::string& _path, std::string&& _bin)
	{
		SA_LOG(L"Loading model [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		Ser::BinaryStream ser(std::move(_bin));

		ser >> nodes;


		// Import linked assets.
		for(const auto& node : nodes)
		{
			for(const auto& path : node.meshAssetPaths)
			{
				if(!_mgr.Load<MeshAsset>(path))
					return false;
			}
		}

		return true;
	}

//}


//{ Save

	bool ModelAsset::Save(AssetMgr& _mgr, const std::string& _path, std::string& _bin) const
	{
		SA_LOG(L"Saving model [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		Ser::BinaryStream ser;

		ser << nodes;

		_bin = std::move(ser.bin);


		// Save linked assets.
		for(const auto& node : nodes)
		{
			for(const auto& path : node.meshAssetPaths)
			{
				auto meshAsset = _mgr.Load<MeshAsset>(path);

				if (!meshAsset.Save(path))
					return false;
			}
		}

		return true;
	}
	
//}


//{ Import

	bool ModelAsset::Import(AssetMgr& _mgr, const std::string& _path)
	{
		SA_LOG(L"Importing model [" << _path << L"]", Infos, SA/Engine/SDK/Asset);
		
		Assimp::Importer importer;

		const aiScene* const aiScene = importer.ReadFile(_path, aiProcessPreset_TargetRealtime_MaxQuality);

		if (!aiScene)
		{
			SA_LOG(L"Assimp Error: " << importer.GetErrorString(), Error, SA/SDK/Asset);
			return false;
		}

		const std::string savedPath = _path.substr(0, _path.find_last_of('.')) + '_';

		return ParseScene(_mgr, savedPath, aiScene);
	}

	bool ModelAsset::ParseScene(AssetMgr& _mgr, const std::string& _savedPath, const aiScene* _aiScene)
	{
		nodes.reserve(_aiScene->mNumMeshes);

		return ParseNode(_mgr, _savedPath, _aiScene, _aiScene->mRootNode) &&
			ParseAnimations(_mgr, _savedPath, _aiScene);
	}

	bool ModelAsset::ParseNode(AssetMgr& _mgr, const std::string& _savedPath, const aiScene* _aiScene, const aiNode* _aiNode)
	{
		ModelNode& node = nodes.emplace_back();

		// Parsing meshes of this node.
		for (uint32_t i = 0u; i < _aiNode->mNumMeshes; ++i)
		{
			node.trMat = reinterpret_cast<const RMat4f&>(_aiNode->mTransformation);

			const aiMesh* const aiMesh = _aiScene->mMeshes[_aiNode->mMeshes[i]];
			const std::string pathName = (_savedPath + aiMesh->mName.C_Str()) + ".spha";


			// Import.
			MeshAsset meshAsset;

			if(!meshAsset.Import(aiMesh))
			{
				SA_LOG(L"Import mesh [" << pathName << "L] failed", Error, SA/Engine/SDK/Asset);
				return false;
			}


			// Emplace.
			_mgr.Emplace(std::make_shared<MeshAsset>(std::move(meshAsset)), pathName);
			node.meshAssetPaths.emplace_back(pathName);


			// Skeleton.
			if(!ParseSkeleton(_mgr, _savedPath, aiMesh))
			{
				SA_LOG(L"Import mesh skeleton [" << pathName << "L] failed", Error, SA/Engine/SDK/Asset);
				return false;
			}


			// Material.
			if(!ParseMaterial(_mgr, _savedPath, _aiScene->mMaterials[aiMesh->mMaterialIndex]))
			{
				SA_LOG(L"Import mesh material [" << pathName << "L] failed", Error, SA/Engine/SDK/Asset);

				return false;
			}
		}


		// Parsing children nodes.
		for (uint32_t i = 0; i < _aiNode->mNumChildren; ++i)
		{
			if(!ParseNode(_mgr, _savedPath, _aiScene, _aiNode->mChildren[i]))
				return false;
		}

		return true;
	}

	bool ModelAsset::ParseSkeleton(AssetMgr& _mgr, const std::string& _savedPath, const aiMesh* aiMesh)
	{
		// TODO: Implement.
		
		(void)_mgr;
		(void)_savedPath;

		for (uint32_t i = 0u; i < aiMesh->mNumBones; ++i)
		{
			const aiBone* const bone = aiMesh->mBones[i];

			(void)bone;
		}

		return true;
	}

	bool ModelAsset::ParseMaterial(AssetMgr& _mgr, const std::string& _savedPath, const aiMaterial* aiMat)
	{
		// TODO: Implement.
		
		(void)_mgr;
		(void)_savedPath;
		(void)aiMat;

		return true;
	}

	bool ModelAsset::ParseAnimations(AssetMgr& _mgr, const std::string& _savedPath, const aiScene* _scene)
	{
		// TODO: Implement.

		(void)_mgr;
		(void)_savedPath;

		// animAssetPaths.reserve(_scene->mNumAnimations);

		for (uint32_t i = 0u; i < _scene->mNumAnimations; ++i)
		{
			const aiAnimation* const anim = _scene->mAnimations[i];

			(void)anim;
		}

		return true;
	}

//}


//{ Handle

	AssetHandle<MeshAsset> AssetHandle<ModelAsset>::GetMesh(uint32_t _index)
	{
		for(const auto& node : mAssetPtr->nodes)
		{
			if(_index < node.meshAssetPaths.size())
				return mMgr->Load<MeshAsset>(node.meshAssetPaths[_index]);

			_index -= node.meshAssetPaths.size();
		}

		SA_ERROR(L"Index out of mesh array range!", SA/Engine/SDK/Asset);

		return AssetHandle<MeshAsset>(*mMgr);
	}

	AssetHandle<MeshAsset> AssetHandle<ModelAsset>::GetMesh(const std::string& _path)
	{
#if SA_DEBUG

		bool bFound = false;

		for(auto nodeIt = mAssetPtr->nodes.begin(); nodeIt != mAssetPtr->nodes.end() && !bFound; ++nodeIt)
		{
			for(auto pathIt = nodeIt->meshAssetPaths.begin(); pathIt != nodeIt->meshAssetPaths.end() && !bFound; ++pathIt)
			{
				if (*pathIt == _path)
					bFound = true;
			}
		}

		SA_ERROR(bFound, SA/Engine/SDK/Asset, L"Mesh at path [" << _path << L"] does not belong to this model!");

#endif

		return mMgr->Load<MeshAsset>(_path);
	}

//}
}

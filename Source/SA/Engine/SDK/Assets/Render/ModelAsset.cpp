// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/ModelAsset.hpp>

#include <SA/Collections/Debug>

#include <SDK/Assets/AssetManager.hpp>
#include <SDK/Assets/AssetHandle.hpp>
#include <SDK/Assets/Render/SkeletalMeshAsset.hpp>


#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace SA::SDK
{
//{ Import

	//{ Helpers
	
	bool ImportMesh(AssetMgr& _mgr,
		const aiScene* _aiScene,
		const aiMesh* _aiMesh,
		const std::string& _outBasePath,
		const std::string& _finalMeshPath)
	{
		SkeletalMeshAsset::ImportInfos importInfos;
		importInfos.SetMesh(_aiMesh);
		importInfos.matImport.mat = _aiScene->mMaterials[_aiMesh->mMaterialIndex];
		importInfos.outModelBasePath = _outBasePath;

		if(_aiMesh->mNumBones)
		{
			// Skeletal mesh.

			return _mgr.Import<SkeletalMeshAsset>(_finalMeshPath, importInfos);
		}
		else
		{
			// Static mesh.

			return _mgr.Import<MeshAsset>(_finalMeshPath, importInfos);
		}
	}

	//}


	bool ModelAsset::Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos)
	{
		SA_LOG(L"Importing model [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_infos;

		Assimp::Importer importer;
		const aiScene* const aiScene = importer.ReadFile(_path, aiProcessPreset_TargetRealtime_MaxQuality);

		if (!aiScene)
		{
			SA_LOG(importer.GetErrorString(), Error, SA/Engine/SDK/Asset/Model, L"Assimp import model [" << _path << L"] error");
			return false;
		}


		const std::string outBasePath = _path.substr(0, _path.find_last_of('.')) + '_';

		return ParseScene(_mgr, outBasePath, aiScene);
	}

	bool ModelAsset::ParseScene(AssetMgr& _mgr, const std::string& _outBasePath, const aiScene* _aiScene)
	{
		return ParseNode(_mgr, root, _outBasePath, _aiScene, _aiScene->mRootNode) &&
			ParseAnimations(_mgr, _outBasePath, _aiScene);
	}

	bool ModelAsset::ParseNode(AssetMgr& _mgr, Node& _node, const std::string& _outBasePath, const aiScene* _aiScene, const aiNode* _aiNode)
	{
		// Parsing meshes of this node.
		for (uint32_t i = 0u; i < _aiNode->mNumMeshes; ++i)
		{
			_node.trMat = reinterpret_cast<const RMat4f&>(_aiNode->mTransformation);

			const aiMesh* const aiMesh = _aiScene->mMeshes[_aiNode->mMeshes[i]];
			const std::string meshPathName = (_outBasePath + aiMesh->mName.C_Str()) + "_mesh";


			// Import.
			if(!ImportMesh(_mgr, _aiScene, aiMesh, _outBasePath, meshPathName))
			{
				SA_LOG(L"Import assimp mesh [" << meshPathName << "L] failed", Error, SA/Engine/SDK/Asset)
				return false;
			}


			// Emplace.
			// _mgr.Emplace(meshAsset, meshPathName); // Already emplaced by import.
			_node.meshPaths.emplace_back(meshPathName);
		}
	
		// Parsing children nodes.
		_node.children.resize(_aiNode->mNumChildren);

		for (uint32_t i = 0; i < _aiNode->mNumChildren; ++i)
		{
			if(!ParseNode(_mgr, _node.children[i], _outBasePath, _aiScene, _aiNode->mChildren[i]))
				return false;
		}

		return true;
	}

	bool ModelAsset::ParseAnimations(AssetMgr& _mgr, const std::string& _outBasePath, const aiScene* _aiScene)
	{
		(void)_mgr;
		(void)_outBasePath;
		(void)_aiScene;

		// TODO: Implement.

		return false;
	}

//}

}

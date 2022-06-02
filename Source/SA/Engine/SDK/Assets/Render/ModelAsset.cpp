// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/ModelAsset.hpp>

#include <SA/Collections/Debug>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace SA::SDK
{
	// bool ModelAsset::IsValid() const
	// {
	// 	return !meshes.empty();
	// }

	
	// bool ModelAsset::Load_Internal(std::string&& _bin)
	// {
	// 	(void)_bin;

	// 	// TODO: Implement.
	// 	return false;
	// }
	
	// void ModelAsset::UnLoad()
	// {
	// 	meshes.clear();
	// }

	
	// bool ModelAsset::Save_Internal(std::fstream& _fstream) const
	// {
	// 	(void)_fstream;

	// 	// TODO: Implement.
	// 	return false;
	// }

	
	// bool ModelAsset::Import(const std::string& _path)
	// {
	// 	SA_LOG(L"Importing model {" << _path << L"}", Infos, SA/SDK/Asset);

	// 	Assimp::Importer importer;

	// 	const aiScene* scene = importer.ReadFile(_path, aiProcessPreset_TargetRealtime_MaxQuality);

	// 	if (!scene)
	// 	{
	// 		SA_LOG(L"Assimp Error: " << importer.GetErrorString(), Error, SA/SDK/Asset);
	// 		return false;
	// 	}

	// 	return ParseScene(scene);
	// }


	// bool ModelAsset::ParseScene(const aiScene* _scene)
	// {
	// 	// Animations
	// 	{
	// 		// TODO: Parsing.

	// 		//for (uint32 i = 0u; i < _scene->mNumAnimations; ++i)
	// 		//{
	// 		//	_scene->mAnimations[i];
	// 		//}
	// 	}


	// 	return ParseNode(_scene, _scene->mRootNode);
	// }

	// bool ModelAsset::ParseNode(const aiScene* _scene, const aiNode* _node)
	// {
	// 	// Parsing meshes of this node.
	// 	for (uint32_t i = 0u; i < _node->mNumMeshes; ++i)
	// 	{
	// 		const aiMesh* const aiMesh = _scene->mMeshes[_node->mMeshes[i]];

	// 		// Static mesh
	// 		if(aiMesh->mNumBones == 0)
	// 		{
	// 			MeshAsset& meshAsset = meshes.emplace_back();
	// 			meshAsset.Import(aiMesh);
	// 		}
	// 		else
	// 		{
	// 			// Skeletal Mesh.

	// 			// TODO: Implement.

	// 			//for (uint32 j = 0u; j < aiMesh->mNumBones; ++j)
	// 			//{
	// 			//	const aiBone* bone = aiMesh->mBones[j];

	// 			//}
	// 		}


	// 		// Material
	// 		{
	// 			// TODO: Parsing.

	// 			//const aiMaterial* mat = _scene->mMaterials[aiMesh->mMaterialIndex];
	// 		}
	// 	}


	// 	// Parsing children nodes.
	// 	for (uint32_t i = 0; i < _node->mNumChildren; ++i)
	// 		ParseNode(_scene, _node->mChildren[i]);

	// 	return true;
	// }
}

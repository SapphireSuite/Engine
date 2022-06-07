// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/SkeletalMeshAsset.hpp>


#include <assimp/mesh.h>

namespace SA::SDK
{
//{ Load / Unload

	void SkeletalMeshAsset::Unload(AssetMgr& _mgr)
	{
		_mgr.Unload(skeletonPath);
	}

//}


//{ Import

	void SkeletalMeshAsset::ImportInfos::SetMesh(const aiMesh* _mesh)
	{
		mesh = _mesh;
		skelImport.mesh = _mesh;
	}


	bool SkeletalMeshAsset::Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos)
	{
		SA_LOG(L"Importing assimp skeletal mesh [" << _infos.mesh << L"] from path [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		if(!MeshAsset::Import(_mgr, _path, _infos))
			return false;

		return ImportSkeleton(_mgr, _path, _infos);
	}

	bool SkeletalMeshAsset::ImportSkeleton(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos)
	{
		const std::string impSkelPath = _path + "_skel";

		AssetHandle<SkeletonAsset> skelAsset = _mgr.Import<SkeletonAsset>(impSkelPath, _infos.skelImport);

		if(skelAsset)
			skeletonPath = impSkelPath;

		return skelAsset;
	}

//}
}

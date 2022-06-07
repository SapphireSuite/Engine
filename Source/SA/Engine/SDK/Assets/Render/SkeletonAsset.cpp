// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/SkeletonAsset.hpp>

#include <SA/Collections/Debug>


#include <assimp/mesh.h>

namespace SA::SDK
{
	bool SkeletonAsset::Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos)
	{
		SA_LOG(L"Importing assimp skeleton [" << _infos.mesh->mBones << L"] from path [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;

		// TODO: implement.

		return false;
	}
}

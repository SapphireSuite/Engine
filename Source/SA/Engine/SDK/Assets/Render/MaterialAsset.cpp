// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/MaterialAsset.hpp>

#include <SA/Collections/Debug>


#include <assimp/material.h>

namespace SA::SDK
{
	bool MaterialAsset::Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos)
	{
		SA_LOG(L"Importing assimp material [" << _infos.mat << L"] from path [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;
		(void)_infos;

		// TODO: Implement.

		return true;
	}
}

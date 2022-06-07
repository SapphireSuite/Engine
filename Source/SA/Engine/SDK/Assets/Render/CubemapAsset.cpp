// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/CubemapAsset.hpp>

namespace SA::SDK
{
//{ Import

	bool CubemapAsset::Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos)
	{
		SA_LOG(L"Importing cubemap [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;
		(void)_infos;

		// TODO: Implement.

		return false;
	}
	
//}
}

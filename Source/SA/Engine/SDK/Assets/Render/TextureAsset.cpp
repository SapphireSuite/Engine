// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/TextureAsset.hpp>

#include <SDK/Wrappers/StbImage.hpp>

namespace SA::SDK
{
//{ Import

	bool TextureAsset::Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos)
	{
		SA_LOG(L"Importing texture [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;
		(void)_infos;

		return StbImage::Import(_path, raw);
	}

//}
}

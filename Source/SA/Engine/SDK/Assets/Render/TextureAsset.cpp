// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/TextureAsset.hpp>

#include <SDK/Wrappers/StbImage.hpp>

namespace SA::SDK
{
	bool TextureAsset::Load(AssetMgr& _mgr, const std::string& _path, std::string&& _bin)
	{
		SA_LOG(L"Loading texture [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;
		(void)_path;

		Ser::BinaryStream ser(std::move(_bin));

		ser >> raw;

		return true;
	}

	bool TextureAsset::Save(AssetMgr& _mgr, const std::string& _path, std::string& _bin) const
	{
		SA_LOG(L"Saving texture [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;
		(void)_path;

		Ser::BinaryStream ser;

		ser << raw;

		_bin = std::move(ser.bin);

		return true;
	}


	bool TextureAsset::Import(AssetMgr& _mgr, const std::string& _path)
	{
		SA_LOG(L"Importing texture [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;

		return StbImage::Import(_path, raw);
	}
}

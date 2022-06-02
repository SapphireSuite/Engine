// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/RenderPassAsset.hpp>

#include <SA/Collections/Debug>

namespace SA::SDK
{
	bool RenderPassAsset::Load(AssetMgr& _mgr, const std::string& _path, std::string&& _bin)
	{
		SA_LOG(L"Loading RenderPass [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;
		(void)_path;

		Ser::BinaryStream ser(std::move(_bin));

		ser >> descriptor;

		return true;
	}
	
	bool RenderPassAsset::Save(AssetMgr& _mgr, const std::string& _path, std::string& _bin) const
	{
		SA_LOG(L"Saving RenderPass [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;
		(void)_path;

		Ser::BinaryStream ser;

		ser << descriptor;

		_bin = std::move(ser.bin);

		return true;
	}
}

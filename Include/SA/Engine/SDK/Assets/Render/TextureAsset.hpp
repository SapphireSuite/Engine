// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_TEXTURE_ASSET_GUARD
#define SAPPHIRE_ENGINE_TEXTURE_ASSET_GUARD

#include <SA/Engine/SDK/Assets/Render/ARenderAsset.hpp>

#include <SA/Engine/Render/Base/Texture/RawTexture.hpp>

namespace SA::SDK
{
	class TextureAsset : public ARenderAsset
	{
		bool Load(AssetMgr& _mgr, const std::string& _path, std::string&& _bin) override final;
		bool Save(AssetMgr& _mgr, const std::string& _path, std::string& _bin) const override final;

	public:
		RawTexture raw;

		bool Import(AssetMgr& _mgr, const std::string& _path);
	};
}

#endif // GUARD

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
	public:
		RawTexture raw;

//{ Import

		struct ImportInfos : public ARenderAsset::ImportInfos
		{
		};


		bool Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos);

//}
	};
}

#endif // GUARD

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
		bool Load_Internal(std::string&& _bin) override final;
		bool Save_Internal(std::fstream& _fstream) const override final;

	public:
		RawTexture raw;

		bool IsValid() const override final;

		void UnLoad() override final;

		bool Import(const std::string& _path);
	};
}

#endif // GUARD

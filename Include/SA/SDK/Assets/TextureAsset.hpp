// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_TEXTURE_ASSET_GUARD
#define SAPPHIRE_SDK_TEXTURE_ASSET_GUARD

#include <SA/SDK/Assets/AAsset.hpp>

#include <SA/Render/Base/Texture/RawTexture.hpp>

namespace Sa
{
	class TextureAsset : public AAsset
	{
	public:
		RawTexture raw;


		bool IsValid() const override final;

		bool Load(const std::string& _path) override final;
		void UnLoad() override final;

		bool Save(const std::string& _path) const override final;

		bool Import(const std::string& _path) override final;
	};
}

#endif // GUARD

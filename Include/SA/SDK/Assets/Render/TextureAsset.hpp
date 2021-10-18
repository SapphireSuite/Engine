// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_TEXTURE_ASSET_GUARD
#define SAPPHIRE_SDK_TEXTURE_ASSET_GUARD

#include <SA/SDK/Assets/Render/ARenderAsset.hpp>

#include <SA/Render/Base/Texture/RawTexture.hpp>

namespace Sa
{
	class TextureAsset : public ARenderAsset
	{
	protected:
		bool Load_Internal(Serialize::Reader&& _read, const std::string& _path) override final;
		bool Save_Internal(std::fstream& _fStream) const override final;
		bool Import_Internal(const std::string& _path) override final;

	public:
		RawTexture raw;


		bool IsValid() const override final;

		void UnLoad() override final;
	};
}

#endif // GUARD

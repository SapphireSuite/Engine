// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/TextureAsset.hpp>

#include <SDK/Wrappers/StbImage.hpp>

namespace SA::SDK
{
	bool TextureAsset::IsValid() const
	{
		return !raw.data.empty();
	}

	
	void TextureAsset::UnLoad()
	{
		raw.Clear();
	}
	
	bool TextureAsset::Load_Internal(std::string&& _bin)
	{
		Ser::BinaryStream ser(std::move(_bin));

		ser >> raw;

		return true;
	}

	
	bool TextureAsset::Save_Internal(std::fstream& _fstream) const
	{
		Ser::BinaryStream ser;

		ser << raw;

		_fstream << ser.bin;

		return true;
	}

	
	bool TextureAsset::Import(const std::string& _path)
	{
		return StbImage::Import(_path, raw);
	}
}

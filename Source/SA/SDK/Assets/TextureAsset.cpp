// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/TextureAsset.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <SDK/Wrappers/StbImage.hpp>

namespace Sa
{
	bool TextureAsset::IsValid() const
	{
		return !raw.data.empty();
	}

	
	bool TextureAsset::Load(const std::string& _path)
	{
		std::string bin;

		if (!ReadFile(_path, bin))
			return false;


		Serialize::Reader read = std::move(bin);

		Serialize::FromBinary(raw, read);

		return true;
	}
	
	void TextureAsset::UnLoad()
	{
		raw.Reset();
	}

	
	bool TextureAsset::Save(const std::string& _path) const
	{
		if (!AAsset::Save(_path))
			return false;


		std::fstream fStream(_path, std::fstream::binary | std::fstream::out | std::fstream::trunc);

		if (!fStream.is_open())
		{
			SA_LOG(L"Failed to open file {" << _path << L"}!", Error, SA/SDK/Asset);
			return false;
		}


		fStream << Serialize::ToBinary(raw);

		return true;
	}

	
	bool TextureAsset::Import(const std::string& _path)
	{
		return StbImage::Import(_path, raw);
	}
}

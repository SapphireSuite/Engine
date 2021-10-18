// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/TextureAsset.hpp>

#include <Core/Algorithms/SizeOf.hpp>
#include <Core/Serialize/Serializer.hpp>

#include <SDK/Wrappers/StbImage.hpp>

namespace Sa
{
	bool TextureAsset::IsValid() const
	{
		return !raw.data.empty();
	}

	
	bool TextureAsset::Load_Internal(Serialize::Reader&& _read, const std::string& _path)
	{
		(void)_path;

		Serialize::FromBinary(raw, _read);

		return true;
	}
	
	void TextureAsset::UnLoad()
	{
		raw.Reset();
	}

	
	bool TextureAsset::Save_Internal(std::fstream& _fStream) const
	{
		_fStream << Serialize::ToBinary(raw);

		return true;
	}

	
	bool TextureAsset::Import_Internal(const std::string& _path)
	{
		return StbImage::Import(_path, raw);
	}
}

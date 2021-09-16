// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/TextureAsset.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <SDK/Wrappers/StbImage.hpp>

namespace Sa
{
	bool TextureAsset::IsValid() const
	{
		return !rawData.data.empty();
	}

	
	bool TextureAsset::Load(const std::string& _path)
	{
		std::fstream fStream(_path, std::ios::binary | std::ios_base::in);

		if (!fStream.is_open())
		{
			SA_LOG("Failed to open file {" << _path << L"}!", Error, SA/SDK/Asset);
			return false;
		}


		{
			fStream.read(reinterpret_cast<char*>(&rawData.extent), sizeof(Vec2ui));
			fStream.read(reinterpret_cast<char*>(&rawData.mipLevels), sizeof(uint32));
			fStream.read(reinterpret_cast<char*>(&rawData.format), sizeof(Format));
		}


		// Data
		{
			uint32 size = 0u;
			fStream.read(reinterpret_cast<char*>(&size), sizeof(uint32));

			if (size == 0)
			{
				SA_LOG("Parsing file {" << _path << L"} error: Empty indices.", Error, SA/SDK/Asset);
				return false;
			}

			rawData.data.resize(size);
			fStream.read(rawData.data.data(), size);
		}

		return true;
	}
	
	void TextureAsset::UnLoad()
	{
		rawData.extent = Vec2ui::Zero;
		rawData.mipLevels = 1u;
		rawData.format = Format::RGBA_32;

		rawData.data.clear();
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


		{
			fStream.write(reinterpret_cast<const char*>(&rawData.extent), sizeof(Vec2ui));
			fStream.write(reinterpret_cast<const char*>(&rawData.mipLevels), sizeof(uint32));
			fStream.write(reinterpret_cast<const char*>(&rawData.format), sizeof(Format));
		}


		// Data
		{
			const uint32 dataSize = SizeOf<uint32>(rawData.data);
			fStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32));
			fStream.write(rawData.data.data(), dataSize);
		}

		return true;
	}

	
	bool TextureAsset::Import(const std::string& _path)
	{
		return StbImage::Import(_path, rawData);
	}
}

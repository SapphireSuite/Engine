// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/AAsset.hpp>

#include <filesystem>

#include <SA/Collections/Debug>

#include <SDK/Wrappers/ReadFile.hpp>

namespace SA::SDK
{
	void AAsset::CreateDirectory(const std::string& _path) const
	{
		// Create Directory.
		const size_t dirIndex = _path.find_last_of('/');

		if (dirIndex != size_t(-1))
		{
			const std::string dirPath = _path.substr(0, dirIndex);

			if (!dirPath.empty())
				std::filesystem::create_directories(dirPath);
		}
	}

	bool AAsset::Load(const std::string& _path)
	{
		std::string bin;

		if (!ReadBinaryFile(_path, bin))
			return false;

		return Load_Internal(std::move(bin));
	}
	
	bool AAsset::Save(const std::string& _path) const
	{
		CreateDirectory(_path);

		std::fstream fstream(_path, std::fstream::binary | std::fstream::out | std::fstream::trunc);

		if (!fstream.is_open())
		{
			SA_LOG(L"Failed to open file {" << _path << L"}!", Error, SA/Engine/SDK/Asset);
			return false;
		}


		return Save_Internal(fstream);
	}
}

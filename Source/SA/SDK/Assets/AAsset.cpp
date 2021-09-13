// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/AAsset.hpp>

#include <filesystem>

namespace Sa
{
	void AAsset::CreateDirectory(const std::string& _path) const
	{
		// Create Directory.
		const uint32 dirIndex = _path.find_last_of('/');

		if (dirIndex != uint32(-1))
		{
			const std::string dirPath = _path.substr(0, dirIndex);

			if (!dirPath.empty())
				std::filesystem::create_directories(dirPath);
		}
	}


	bool AAsset::Save(const std::string& _path) const
	{
		if (_path.empty())
		{
			SA_LOG(L"Try save asset at empty path!", Error, SA/SDK/Asset);
			return false;
		}

		CreateDirectory(_path);

		return true;
	}
}

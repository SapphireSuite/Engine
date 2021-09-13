// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/AAsset.hpp>

#include <filesystem>

namespace Sa
{
	bool AAsset::Open(const std::string& _path)
	{
		const uint32 extIndex = static_cast<uint32>(_path.find_last_of('.'));

		if (extIndex == uint32(-1))
		{
			SA_LOG(L"Asset {" << _path << L"} could not find extension.", Error, SA/SDK/Asset);
			return false;
		}

		const std::string ext = _path.substr(extIndex + 1);

		// Sapphire file.
		if (ext == "spha")
			return Load(_path);
		else
			return Import(_path);
	}


	void AAsset::CreateDirectory(const std::string& _path) const
	{
		// Create Directory.
		const uint32 dirIndex = static_cast<uint32>(_path.find_last_of('/'));

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

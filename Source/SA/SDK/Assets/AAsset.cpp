// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/AAsset.hpp>

#include <filesystem>

#include <Core/Algorithms/ReadFile.hpp>
#include <Core/Serialize/Serializer.hpp>

#include <SDK/EnvironmentVariable.hpp>

namespace Sa
{
	std::string AAsset::GetFullPath(const std::string& _path) const
	{
		return _path.starts_with("/Engine") ? EnvVar::path + _path.substr(7u) : _path;
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


	bool AAsset::Load(const std::string& _path)
	{
		const std::string fullPath = GetFullPath(_path);

		std::string bin;

		if (!ReadBinaryFile(fullPath, bin))
			return false;

		return Load_Internal(std::move(bin), fullPath);
	}

	bool AAsset::Save(const std::string& _path) const
	{
		if (_path.empty())
		{
			SA_LOG(L"Try save asset at empty path!", Error, SA/SDK/Asset);
			return false;
		}

		const std::string fullPath = GetFullPath(_path);

		CreateDirectory(fullPath);


		std::fstream fStream(fullPath, std::fstream::binary | std::fstream::out | std::fstream::trunc);

		if (!fStream.is_open())
		{
			SA_LOG(L"Failed to open file {" << fullPath << L"}!", Error, SA/SDK/Asset);
			return false;
		}


		return Save_Internal(fStream);
	}

	bool AAsset::Import(const std::string& _path)
	{
		const std::string fullPath = GetFullPath(_path);

		return Import_Internal(fullPath);
	}
}

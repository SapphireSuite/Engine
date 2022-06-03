// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/AssetMgr.hpp>

#include <fstream>
#include <filesystem>

#include <SDK/Assets/AAsset.hpp>

#include <SDK/Wrappers/ReadFile.hpp>

namespace SA::SDK
{
	void CreateDirectory(const std::string& _path)
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


	void AssetMgr::Clear()
	{
		mPathToAssetMap.clear();
	}


	void AssetMgr::Emplace(std::shared_ptr<AAsset> _assetPtr, const std::string& _path)
	{
		std::shared_ptr<AAsset>& emplAssetPtrRef = mPathToAssetMap[_path];

		SA_ERROR(!(emplAssetPtrRef && emplAssetPtrRef != _assetPtr), SA/Engine/SDK/Asset,
			"Asset at path [" << _path << L"] already registered with different value. Previous content erased.");

		emplAssetPtrRef = _assetPtr;
	}


//{ Load

	bool AssetMgr::Load_Internal(AAsset* _asset, const std::string& _path)
	{
		std::string bin;

		if (!ReadBinaryFile(_path, bin))
			return false;

		return _asset->Load(*this, _path, std::move(bin));
	}

//}


//{ Save

	bool AssetMgr::Save_Internal(AAsset* _asset, const std::string& _path)
	{
		CreateDirectory(_path);

		std::fstream fstream(_path, std::fstream::binary | std::fstream::out | std::fstream::trunc);

		if (!fstream.is_open())
		{
			SA_LOG(L"Failed to open file {" << _path << L"}!", Error, SA/Engine/SDK/Asset);
			return false;
		}


		std::string bin;

		if(!_asset->Save(*this, _path, bin))
			return false;


		fstream << bin;

		return true;
	}

	bool AssetMgr::Save(std::shared_ptr<AAsset> _asset, const std::string& _path)
	{
		SA_ASSERT(Nullptr, SA/Engine/SDK/Asset, _asset != nullptr, L"Try save null asset at path ["_L << _path << L"]");

		// Register at new path.
		Emplace(_asset, _path);

		return Save_Internal(_asset.get(), _path);
	}

//}
}

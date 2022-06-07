// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/AssetManager.hpp>

namespace SA::SDK
{
	void AssetMgr::Clear()
	{
		mPathToAssetMap.clear();
	}

	void AssetMgr::Emplace(std::shared_ptr<AAsset> _assetPtr, const std::string& _path)
	{
		std::shared_ptr<AAsset>& emplAssetPtrRef = mPathToAssetMap[_path];

		// Erase previously registered element path.
		if(emplAssetPtrRef && emplAssetPtrRef != _assetPtr)
		{
			SA_LOG(L"Asset at path [" << _path << L"] already registered with different value. Previous content erased.", Warning, SA/Engine/SDK/Asset);

			std::vector<std::string>& pathList = mAssetToPathsMap[emplAssetPtrRef];

			for(auto it = pathList.begin(); it != pathList.end(); ++it)
			{
				if(*it == _path)
				{
					pathList.erase(it);
					break;
				}
			}
		}

		emplAssetPtrRef = _assetPtr;
		mAssetToPathsMap[_assetPtr].emplace_back(_path);
	}


//{ Load / Unload

	void AssetMgr::Unload(std::shared_ptr<AAsset> _asset)
	{
		// Query all reference path for input asset.
		auto findIt = mAssetToPathsMap.find(_asset);

		if(findIt == mAssetToPathsMap.end())
		{
			SA_LOG(L"Asset not registered in this manager!", Error, SA/Engine/SDK/Asset);
			return;
		}


		// Unload every instance registered in paths
		for(const std::string& path : findIt->second)
		{
		#if SA_DEBUG

			auto pathFindIt = mPathToAssetMap.find(path);

			if(pathFindIt == mPathToAssetMap.end())
				SA_LOG(L"Can not find registered path [" << path << "] for unloading asset", Error, SA/Engine/SDK/Asset)

			// Find a different instance than expected?
			SA_ERROR(pathFindIt->second == _asset, L"Registered asset at path [" << path << L"] is different requested unload asset");

		#endif

			mPathToAssetMap.erase(path);
		}

		mAssetToPathsMap.erase(findIt);
	}

//}


//{ Save

	bool AssetMgr::Save(std::shared_ptr<AAsset> _asset, const std::string& _path)
	{
		SA_ASSERT(Nullptr, SA/Engine/SDK/Asset, _asset != nullptr, L"Try save null asset at path ["_L << _path << L"]");

		// TODO: Save using input serializer (JSON, Binary, etc).
		// Serializer create directory and open fstream itself.

		// CreateDirectory(_path);

		// std::fstream fstream(_path, std::fstream::binary | std::fstream::out | std::fstream::trunc);

		// if (!fstream.is_open())
		// {
		// 	SA_LOG(L"Failed to open file {" << _path << L"}!", Error, SA/Engine/SDK/Asset);
		// 	return false;
		// }


		// std::string bin;

		// if(!_asset->Save(*this, _path, bin))
		// 	return false;


		// fstream << bin;

		// Register at new path on success.
		Emplace(_asset, _path);

		return true;
	}

//}
}

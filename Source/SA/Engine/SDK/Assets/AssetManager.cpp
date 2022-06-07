// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/AssetManager.hpp>

#include <SDK/Assets/AAsset.hpp>

namespace SA::SDK
{
//{ Mapping

	void AssetMgr::Clear()
	{
		mPathToAssetMap.clear();
		mAssetToPathsMap.clear();
	}

	void AssetMgr::Emplace(std::shared_ptr<AAsset> _assetPtr, const std::string& _path)
	{
		SharedAsset& emplAssetPtrRef = mPathToAssetMap[_path];

		// Erase previously registered element path.
		if(emplAssetPtrRef.ptr && emplAssetPtrRef.ptr != _assetPtr)
		{
			SA_LOG(L"Asset at path [" << _path << L"] already registered with different value. Previous content erased.", Warning, SA/Engine/SDK/Asset);

			ErasePath(_assetPtr, _path);
		}

		emplAssetPtrRef.ptr = _assetPtr;
		mAssetToPathsMap[_assetPtr].emplace_back(_path);
	}

	void AssetMgr::ErasePath(std::shared_ptr<AAsset> _assetPtr, const std::string& _path)
	{
		auto pathListIt = mAssetToPathsMap.find(_assetPtr);

	#if SA_DEBUG

		if(pathListIt == mAssetToPathsMap.end())
		{
			SA_LOG(L"Asset ptr not registered in map.", Error, SA/Engine/SDK/Asset/Manager);
			return;
		}

	#endif

		std::list<std::string>& pathList = pathListIt->second;

		for(auto it = pathList.begin(); it != pathList.end(); ++it)
		{
			if(*it == _path)
			{
				pathList.erase(it);
				break;
			}
		}

		if (pathList.empty())
			mAssetToPathsMap.erase(pathListIt);
	}

//}


//{ Load / Unload

	void AssetMgr::Unload(const std::string& _path)
	{
		auto pathToAssetIt = mPathToAssetMap.find(_path);

	#if SA_DEBUG

		if(pathToAssetIt == mPathToAssetMap.end())
		{
			SA_LOG("Can not find registered path [" << _path << "] for unloading asset", Error, SA/Engine/SDK/Asset/Manager);
			return;
		}

	#endif

		// Save asset before map erasing.
		const std::shared_ptr<AAsset> asset = pathToAssetIt->second.ptr;


		// No more references?
		if(--(pathToAssetIt->second.refCount) == 0)
		{
			// Erase asset.
			mPathToAssetMap.erase(pathToAssetIt);

			ErasePath(pathToAssetIt->second.ptr, _path);
		}


		// Call asset reference unloading.
		asset->Unload(*this);
	}

	void AssetMgr::Unload(std::shared_ptr<AAsset> _asset)
	{
		// Query all reference path for input asset.
		auto assetToPathsIt = mAssetToPathsMap.find(_asset);

	#if SA_DEBUG

		if(assetToPathsIt == mAssetToPathsMap.end())
		{
			SA_LOG(L"Asset not registered in this manager!", Error, SA/Engine/SDK/Asset/Manager);
			return;
		}

	#endif


		std::list<std::string>& assetPaths = assetToPathsIt->second;

		// Decrement every shared instance registered in each path.
		for(auto pathIt = assetPaths.begin(); pathIt != assetPaths.end();)
		{
			auto pathToAssetIt = mPathToAssetMap.find(*pathIt);

		#if SA_DEBUG

			if(pathToAssetIt == mPathToAssetMap.end())
			{
				SA_LOG(L"Can not find registered path [" << *pathIt << "] for unloading asset", Error, SA/Engine/SDK/Asset/Manager);
				continue;
			}

			if(pathToAssetIt->second.ptr != _asset)
			{
				SA_LOG(L"Registered asset at path [" << *pathIt << L"] is different requested unload asset", Error, SA/Engine/SDK/Asset/Manager);
				continue;
			}

		#endif


			// No more references?
			if(--(pathToAssetIt->second.refCount) == 0)
			{
				// Erase asset.
				mPathToAssetMap.erase(pathToAssetIt);

				// Erase registered path.
				pathIt = assetPaths.erase(pathIt);
			}
			else
				pathIt++;
		}


		// No more path registered for this asset: erase asset ptr key.
		if(assetPaths.empty())
			mAssetToPathsMap.erase(assetToPathsIt);


		// Call asset reference unloading.
		_asset->Unload(*this);
	}

//}
}

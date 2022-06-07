// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

namespace SA::SDK
{
//{ SharedAssetPtr

	template <typename T>
	std::shared_ptr<T> AssetMgr::SharedAsset::Cast()
	{
		return std::dynamic_pointer_cast<T>(ptr);
	}

//}


//{ Mapping

	template <typename T>
	AssetMgr::SharedAsset* AssetMgr::FindAsset(const std::string& _path)
	{
		AssetMgr::SharedAsset* sharedAsset = nullptr;

		auto findIt = mPathToAssetMap.find(_path);
		
		if(findIt != mPathToAssetMap.end())
			sharedAsset = &findIt->second;

		return sharedAsset;
	}

//}


	template <typename T>
	AssetHandle<T> AssetMgr::Get(const std::string& _path)
	{
		SharedAsset* const sharedAsset = FindAsset<T>(_path);

		return AssetHandle<T>(*this, sharedAsset ? sharedAsset->Cast<T>() : nullptr);
	}


//{ Load / Unload

	template <typename T>
	AssetHandle<T> AssetMgr::Load(const std::string& _path)
	{
		std::shared_ptr<T> assetPtr;

		// Try find previously loaded.
		if(SharedAsset* const sharedAsset = FindAsset<T>(_path))
		{
			(sharedAsset->refCount)++;
			assetPtr = sharedAsset->Cast<T>();
		}
		else
		{
			// Not found: import new asset.

			T asset;
			
			// TODO: Implement asset load.
			// if(asset.Load(*this, _path))
			// {
			// 	// Emplace asset;
			// 	assetPtr = std::make_shared<T>(std::move(asset));

			// 	// Register asset at load path.
			// 	Emplace(assetPtr, _path);
			// }
		}

		return AssetHandle<T>(*this, assetPtr);
	}

//}


//{ Import

	template <typename T>
	AssetHandle<T> AssetMgr::Import(const std::string& _path, const typename T::ImportInfos& _infos)
	{
		std::shared_ptr<T> assetPtr;

		// Try find previously loaded.
		if(SharedAsset* const sharedAsset = FindAsset<T>(_path))
		{
			(sharedAsset->refCount)++;
			assetPtr = sharedAsset->Cast<T>();
		}
		else
		{
			// Not found: import new asset.

			T asset;
			
			if(asset.Import(*this, _path, _infos))
			{
				// Emplace asset;
				assetPtr = std::make_shared<T>(std::move(asset));

				// Register asset at import path.
				Emplace(assetPtr, _path);
			}
		}

		return AssetHandle<T>(*this, assetPtr);
	}


	template <typename T>
	AssetHandle<T> AssetMgr::LoadOrImport(const std::string& _assetPath,
		const std::string& _resPath,
		const typename T::ImportInfos& _infos)
	{
		AssetHandle<T> handle = Load<T>(_assetPath);

		if(handle)
		{
			// Also register asset at resource path.
			Emplace(handle.Get(), _resPath);
		}
		else
		{
			// Load failed: import.

			handle = Import<T>(_resPath, _infos);

			if(handle)
			{
				// Register only asset at asset path.
				Emplace(handle.Get(), _assetPath);
			}
		}

		return handle;
	}

//}
}

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

namespace SA::SDK
{
	template <typename T>
	std::shared_ptr<T> AssetMgr::FindTypedAsset(const std::string& _path)
	{
		std::shared_ptr<T> assetPtr;

		auto findIt = mPathToAssetMap.find(_path);
		
		if(findIt != mPathToAssetMap.end())
		{
			// Found cast.

			assetPtr = std::dynamic_pointer_cast<T>(findIt->second);

			SA_ASSERT(Nullptr, SA/Engine/SDK/Asset, assetPtr != nullptr, L"Imported asset ["_L << _path << "L] alread loaded with different type.");
		}

		return assetPtr;
	}


//{ Load / Unload

	template <typename T>
	AssetHandle<T> AssetMgr::Load(const std::string& _path)
	{
		std::shared_ptr<T> assetPtr;

		// Try find previously loaded.
		assetPtr = FindTypedAsset<T>(_path);

		if(!assetPtr)
		{
			// Not found: import new asset.

			T asset;
			
			if(asset.Load(*this, _path))
			{
				// Emplace asset;
				assetPtr = std::make_shared<T>(std::move(asset));

				// Register asset at load path.
				Emplace(assetPtr, _path);
			}
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
		assetPtr = FindTypedAsset<T>(_path);

		if(!assetPtr)
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
		const typename T::ImportInfosT& _infos,
		bool bSaveOnImport)
	{
		AssetHandle<T> handle = Load<T>(_assetPath);

		if(handle.IsValid())
		{
			// Also register asset at resource path.
			Emplace(handle.Get(), _resPath);
		}
		else
		{
			// Load failed: import.

			handle = Import<T>(_resPath, _infos);

			if(handle.IsValid())
			{
				// TODO: Implement.
				(void)bSaveOnImport;

				// if(bSaveOnImport)
				// {
				// 	// Save and register as new asset at _assetPath 
				// 	Save(handle.Get(), _assetPath);
				// }
				// else
				// {
				
				
				// Register only asset at asset path.
				Emplace(handle.Get(), _assetPath);
				
				
				// }
			}
		}

		return handle;
	}

//}
}

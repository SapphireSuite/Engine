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


	template <typename T>
	AssetHandle<T> AssetMgr::Load(const std::string& _path)
	{
		// Find previously loaded.

		if(std::shared_ptr<T> assetPtr = FindTypedAsset<T>(_path))
			return AssetHandle<T>(*this, assetPtr);


		// Not found: load new asset.

		AssetHandle<T> handle(*this);
		
		T asset;

		if(Load_Internal(&asset, _path))
		{
			// Emplace asset;
			std::shared_ptr<T> assetPtr = handle.Emplace(std::move(asset));

			// Register loaded asset.
			mPathToAssetMap[_path] = assetPtr;
		}

		return handle;
	}

	template <typename T>
	AssetHandle<T> AssetMgr::Import(const std::string& _path)
	{
		// Find previously loaded.

		if(std::shared_ptr<T> assetPtr = FindTypedAsset<T>(_path))
			return AssetHandle<T>(*this, assetPtr);


		// Not found: import new asset.

		AssetHandle<T> handle(*this);
		
		T asset;

		if(asset.Import(*this, _path))
		{
			// Emplace asset;
			std::shared_ptr<T> assetPtr = handle.Emplace(std::move(asset));

			// Register loaded asset.
			mPathToAssetMap[_path] = assetPtr;
		}

		return handle;
	}


	template <typename T>
	AssetHandle<T> AssetMgr::LoadOrImport(const std::string& _assetPath, const std::string& _resPath, bool bSaveOnImport)
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

			handle = Import<T>(_resPath);

			if(handle.IsValid())
			{
				if(bSaveOnImport)
				{
					// Save and register as new asset at _assetPath 
					Save(handle.Get(), _assetPath);
				}
				else
				{
					// Register only asset at asset path.
					Emplace(handle.Get(), _assetPath);
				}
			}
		}

		return handle;
	}
}

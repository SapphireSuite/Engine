// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

namespace SA::SDK
{
	template <typename T>
	bool AssetMgr::FindTypedAsset(const std::string& _path, std::shared_ptr<T>& _outAsset)
	{
		auto findIt = mPathToAssetMap.find(_path);
		
		if(findIt != mPathToAssetMap.end())
		{
			// Found cast.

			_outAsset = std::dynamic_pointer_cast<T>(findIt->second);

			SA_ASSERT(Nullptr, SA/Engine/SDK/Asset, _outAsset != nullptr, L"Imported asset ["_L << _path << "L] alread loaded with different type.");

			return true;
		}

		return false;
	}


//{ Load

	template <typename T>
	std::shared_ptr<T> AssetMgr::Load(const std::string& _path)
	{
		std::shared_ptr<T> asset;

		Load(_path, asset);

		return asset;
	}

	template <typename T>
	bool AssetMgr::Load(const std::string& _path, std::shared_ptr<T>& _outAsset)
	{
		// Already registered and loaded.
		if(FindTypedAsset(_path, _outAsset))
			return true;


		// Try Load.

		T asset;

		if(!Load_Internal(&asset, _path))
			return false;

		
		// Emplace on load succeed.

		_outAsset = std::make_shared<T>(std::move(asset));

		mPathToAssetMap[_path] = _outAsset;

		return true;
	}

//}


//{ Import

	template <typename T>
	std::shared_ptr<T> AssetMgr::Import(const std::string& _path)
	{
		std::shared_ptr<T> asset;

		Import(_path, asset);

		return asset;
	}

	template <typename T>
	bool AssetMgr::Import(const std::string& _path,std::shared_ptr<T>& _outAsset)
	{
		// Already registered and loaded.
		if(FindTypedAsset(_path, _outAsset))
			return true;


		// Try Import.

		T asset;

		if(!asset.Import(*this, _path))
			return false;

		
		// Emplace on load succeed.

		_outAsset = std::make_shared<T>(std::move(asset));

		mPathToAssetMap[_path] = _outAsset;

		return true;
	}

//}


//{ Helpers

	template <typename T>
	std::shared_ptr<T> AssetMgr::LoadOrImport(const std::string& _assetPath, const std::string& _resPath, bool bSaveOnImport)
	{
		std::shared_ptr<T> outAsset;

		LoadOrImport(_assetPath, _resPath, outAsset, bSaveOnImport);

		return outAsset;
	}

	template <typename T>
	bool AssetMgr::LoadOrImport(const std::string& _assetPath,
		const std::string& _resPath,
		std::shared_ptr<T>& _outAsset,
		bool bSaveOnImport)
	{
		if(Load(_assetPath, _outAsset))
			return true;

		if(Import(_resPath, _outAsset))
		{
			if(bSaveOnImport)
				Save(_outAsset, _assetPath); // Save as new asset at _assetPath.

			return true;
		}

		return false;
	}

//}
}

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

namespace SA::SDK
{
	template <typename T>
	AssetHandleBase<T>::AssetHandleBase(AssetMgr& _mgr, std::shared_ptr<T> _assetPtr) :
		mMgr{ &_mgr },
		mAssetPtr{ _assetPtr }
	{
	}


// { Valid

	template <typename T>
	std::shared_ptr<T> AssetHandleBase<T>::Get() const noexcept
	{
		return mAssetPtr;
	}

	template <typename T>
	bool AssetHandleBase<T>::IsValid() const noexcept
	{
		return mAssetPtr != nullptr;
	}

	template <typename T>
	AssetHandleBase<T>::operator bool() const noexcept
	{
		return IsValid();
	}

//}


//{ Accessor

	template <typename T>
	T& AssetHandleBase<T>::operator*() const
	{
		SA_ASSERT(Nullptr, SA/Engine/SDK/Asset, mAssetPtr);

		return *mAssetPtr;
	}

	template <typename T>
	T* AssetHandleBase<T>::operator->() const
	{
		return mAssetPtr.operator->();
	}

//}


//{ Management

	template <typename T>
	template <typename AssetT>
	AssetHandle<AssetT> AssetHandleBase<T>::QueryAsset(const std::string& _path)
	{
		AssetHandle<AssetT> asset = mMgr->Get<AssetT>(mAssetPtr->materialPath);

		if (!asset)
		{
			SA_LOG("Asset [" << _path << L"] as been previously unloaded!", Warning, SA/Engine/SDK/Asset/Manager);

			asset = mMgr->Load<AssetT>(mAssetPtr->materialPath);

			SA_ERROR(asset, SA/Engine/SDK/Asset/Manager, L"Asset [" << _path << "] force reload failed!");
		}

		return asset;
	}

	template <typename T>
	void AssetHandleBase<T>::Unload()
	{
		mMgr->Unload(mAssetPtr);
	}

//}
}

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
	std::shared_ptr<T> AssetHandleBase<T>::Get() const noexcept
	{
		return mAssetPtr;
	}


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


	template <typename T>
	std::shared_ptr<T> AssetHandleBase<T>::Emplace(T&& _asset)
	{
		mAssetPtr = std::make_shared<T>(std::move(_asset));

		return mAssetPtr;
	}

	template <typename T>
	bool AssetHandleBase<T>::Save(const std::string& _path)
	{
		return mMgr->Save(mAssetPtr, _path);
	}
}

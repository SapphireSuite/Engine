// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ASSET_HANDLE_GUARD
#define SAPPHIRE_ENGINE_ASSET_HANDLE_GUARD

#include <memory>

#include <SA/Collections/Debug>

namespace SA::SDK
{
	class AssetMgr;

	template <typename T>
	class AssetHandle;


	template <typename T>
	class AssetHandleBase
	{
	protected:

		AssetMgr* mMgr = nullptr;

		std::shared_ptr<T> mAssetPtr;

		template <typename AssetT>
		AssetHandle<AssetT> QueryAsset(const std::string& _path);

	public:

		AssetHandleBase(AssetMgr& _mgr, std::shared_ptr<T> _assetPtr = nullptr);

// { Valid

		std::shared_ptr<T> Get() const noexcept;

		bool IsValid() const noexcept;

		operator bool() const noexcept;

//}


//{ Accessor

		T& operator*() const;

		T* operator->() const;

//}


//{ Management

	/**
	 * @brief Unload handled asset.
	 * Every instance of this asset will be unloaded from manager.
	 */
	void Unload();

//}
	};


	template <typename T>
	class AssetHandle : public AssetHandleBase<T>
	{
	public:
		using AssetHandleBase<T>::AssetHandleBase;
	};
}

#include <SA/Engine/SDK/Assets/AssetHandle.inl>

#endif // GUARD

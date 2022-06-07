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
	class AssetHandle
	{
	protected:

		AssetMgr& mMgr;

		std::shared_ptr<T> mAssetPtr;
		
	public:

		AssetHandle(AssetMgr& _mgr, std::shared_ptr<T> _assetPtr = nullptr);

// { Valid

		bool IsValid() const noexcept;

		operator bool() const noexcept;

//}


//{ Accessor

		// std::shared_ptr<T> Get() const noexcept;

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
}

#include <SA/Engine/SDK/Assets/AssetHandle.inl>

#endif // GUARD

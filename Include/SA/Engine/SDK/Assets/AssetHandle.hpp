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
		AssetMgr* mMgr = nullptr;

		std::shared_ptr<T> mAssetPtr;
		
	public:

		AssetHandle(AssetMgr& _mgr, std::shared_ptr<T> _assetPtr = nullptr);

// { Valid

		bool IsValid() const noexcept;

		operator bool() const noexcept;

//}


//{ Accessor

		std::shared_ptr<T> Get() const noexcept;


		T& operator*() const;

		T* operator->() const;

//}

		
		std::shared_ptr<T> Emplace(T&& _asset);

		bool Save(const std::string& _path);

	};
}

#include <SA/Engine/SDK/Assets/AssetHandle.inl>

#endif // GUARD

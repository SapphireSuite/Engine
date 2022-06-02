// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ASSET_MGR_GUARD
#define SAPPHIRE_ENGINE_ASSET_MGR_GUARD

#include <memory>
#include <unordered_map>

#include <SA/Collections/Debug>

#include <SA/Engine/HI/Cast.hpp>

// #include <SA/Engine/SDK/Assets/AAsset.hpp>

namespace SA::SDK
{
	class AAsset;

	class AssetMgr
	{
		std::unordered_map<std::string, std::shared_ptr<AAsset>> mPathToAssetMap;

		template <typename T>
		bool FindTypedAsset(const std::string& _path, std::shared_ptr<T>& _outAsset);

		bool Load_Internal(AAsset* _asset, const std::string& _path);
		bool Save_Internal(AAsset* _asset, const std::string& _path);

	public:

		void Clear();


//{ Load

		template <typename T>
		std::shared_ptr<T> Load(const std::string& _path);

		template <typename T>
		bool Load(const std::string& _path, std::shared_ptr<T>& _outAsset);

//}


//{ Save

		void Save(std::shared_ptr<AAsset> _asset, const std::string& _path);

//}


//{ Import


		template <typename T>
		std::shared_ptr<T> Import(const std::string& _path);

		template <typename T>
		bool Import(const std::string& _path,std::shared_ptr<T>& _outAsset);

//}


//{ Helpers

		template <typename T>
		std::shared_ptr<T> LoadOrImport(const std::string& _assetPath, const std::string& _resPath, bool bSaveOnImport = true);

		template <typename T>
		bool LoadOrImport(const std::string& _assetPath,
			const std::string& _resPath,
			std::shared_ptr<T>& _outAsset,
			bool bSaveOnImport = true);

//}
	};
}

#include <SA/Engine/SDK/Assets/AssetMgr.inl>

#endif // GUARD

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ASSET_MANAGER_GUARD
#define SAPPHIRE_ENGINE_ASSET_MANAGER_GUARD

#include <string>
#include <memory>
#include <unordered_map>

#include <SA/Collections/Debug>

namespace SA::SDK
{
	class AAsset;

	template <typename T>
	class AssetHandle;

	class AssetMgr
	{
		std::unordered_map<std::string, std::shared_ptr<AAsset>> mPathToAssetMap;
		std::unordered_map<std::shared_ptr<AAsset>, std::vector<std::string>> mAssetToPathsMap;

		template <typename T>
		std::shared_ptr<T> FindTypedAsset(const std::string& _path);

		/**
		 * @brief Emplace asset at path.
		 * Internal use only.
		 * 
		 * @param _assetPtr 	Asset ptr to emplace in map.
		 * @param _path 		Path key to emplace in map.
		 */
		void Emplace(std::shared_ptr<AAsset> _assetPtr, const std::string& _path);

	public:
		void Clear();


//{ Load / Unload

		/**
		 * @brief Try found previously registered asset at path, otherwise load and register.
		 * 
		 * @tparam T 		Asset type to load
		 * @param _path 	asset path.
		 * @return 			AssetHandle<T> Handled asset ptr. Valid on load succees.
		 */
		template <typename T>
		AssetHandle<T> Load(const std::string& _path);

		void Unload(std::shared_ptr<AAsset> _asset);

//}


//{ Save

		/**
		 * @brief Asset Mgr save asset implementation.
		 * Use AssetHandle.Save() instead.
		 * 
		 * @param _asset 	Asset to register at new path and save.
		 * @param _path 	Path to register and save asset.
		 * @return 			true on save success.
		 */
		bool Save(std::shared_ptr<AAsset> _asset, const std::string& _path);

//}


//{ Import

		/**
		 * @brief Try found previously registered asset at path, otherwise import and register.
		 * 
		 * @tparam T 		Asset type to load
		 * @param _path 	asset resource path.
		 * @param _infos 	asset import infos.
		 * @return 			AssetHandle<T> Handled asset ptr. Valid on import succees.
		 */
		template <typename T>
		AssetHandle<T> Import(const std::string& _path, const typename T::ImportInfos& _infos = typename T::ImportInfos());

		/**
		 * @brief Try Load and try import on load failure.
		 * 
		 * @tparam T 			Asset type to load/import
		 * @param _assetPath 	asset path to load.
		 * @param _resPath 		resource path to import.
		 * @param _infos 		asset import infos.
		 * @return 				AssetHandle<T> Handled asset ptr. Valid on any success (load or import).
		 */
		template <typename T>
		AssetHandle<T> LoadOrImport(const std::string& _assetPath,
			const std::string& _resPath,
			const typename T::ImportInfosT& _infos = typename T::ImportInfosT(),
			bool bSaveOnImport = true);

//}

	};
}

#include <SA/Engine/SDK/Assets/AssetManager.inl>

#endif // GUARD

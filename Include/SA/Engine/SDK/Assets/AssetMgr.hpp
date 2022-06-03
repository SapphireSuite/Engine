// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ASSET_MGR_GUARD
#define SAPPHIRE_ENGINE_ASSET_MGR_GUARD

#include <string>
#include <memory>
#include <unordered_map>

namespace SA::SDK
{
	class AAsset;

	template <typename T>
	class AssetHandle;

	class AssetMgr
	{
		std::unordered_map<std::string, std::shared_ptr<AAsset>> mPathToAssetMap;

		template <typename T>
		std::shared_ptr<T> FindTypedAsset(const std::string& _path);

		bool Load_Internal(AAsset* _asset, const std::string& _path);
		bool Save_Internal(AAsset* _asset, const std::string& _path);

	public:
		void Clear();

		/**
		 * @brief Emplace asset at path.
		 * Internal use only: should not be called by user.
		 * 
		 * @param _assetPtr 	Asset ptr to emplace in map.
		 * @param _path 		Path key to emplace in map.
		 */
		void Emplace(std::shared_ptr<AAsset> _assetPtr, const std::string& _path);


		/**
		 * @brief Try found previously registered asset at path, otherwise load and register.
		 * 
		 * @tparam T 		Asset type to load
		 * @param _path 	asset path.
		 * @return 			AssetHandle<T> Handled asset ptr. Valid on load succees.
		 */
		template <typename T>
		AssetHandle<T> Load(const std::string& _path);

		/**
		 * @brief Asset Mgr save asset implementation.
		 * Use AssetHandle.Save() instead.
		 * 
		 * @param _asset 	Asset to register at new path and save.
		 * @param _path 	Path to register and save asset.
		 * @return 			true on save success.
		 */
		bool Save(std::shared_ptr<AAsset> _asset, const std::string& _path);

		/**
		 * @brief Try found previously registered asset at path, otherwise import and register.
		 * 
		 * @tparam T 		Asset type to load
		 * @param _path		asset path.
		 * @return 			AssetHandle<T> Handled asset ptr. Valid on import succees.
		 */
		template <typename T>
		AssetHandle<T> Import(const std::string& _path);

		/**
		 * @brief Try Load and try import on load failure.
		 * 
		 * @tparam T 			Asset type to load/import
		 * @param _assetPath 	asset path to load.
		 * @param _resPath 		resource path to import.
		 * @return 				AssetHandle<T> Handled asset ptr. Valid on any success (load or import).
		 */
		template <typename T>
		AssetHandle<T> LoadOrImport(const std::string& _assetPath, const std::string& _resPath, bool bSaveOnImport = true);
	};
}

#include <SA/Engine/SDK/Assets/AssetHandle.hpp>

#include <SA/Engine/SDK/Assets/AssetMgr.inl>

#endif // GUARD

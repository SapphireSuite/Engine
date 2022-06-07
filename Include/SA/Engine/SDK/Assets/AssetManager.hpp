// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ASSET_MANAGER_GUARD
#define SAPPHIRE_ENGINE_ASSET_MANAGER_GUARD

#include <string>
#include <memory>
#include <list>
#include <unordered_map>

namespace SA::SDK
{
	class AAsset;

	template <typename T>
	class AssetHandle;

	class AssetMgr
	{
		struct SharedAsset
		{
			std::shared_ptr<AAsset> ptr;

			/// Asset reference counter.
			uint32_t refCount = 1;

			template <typename T>
			std::shared_ptr<T> Cast();
		};

		std::unordered_map<std::string, SharedAsset> mPathToAssetMap;
		std::unordered_map<std::shared_ptr<AAsset>, std::list<std::string>> mAssetToPathsMap;

//{ Mapping

		template <typename T>
		SharedAsset* FindAsset(const std::string& _path);

		/**
		 * @brief Emplace asset at path.
		 * Internal use only.
		 * 
		 * @param _assetPtr 	Asset ptr to emplace in map.
		 * @param _path 		Path key to emplace in map.
		 */
		void Emplace(std::shared_ptr<AAsset> _assetPtr, const std::string& _path);

		/// Erase path from mAssetToPathsMap for asset ptr.
		void ErasePath(std::shared_ptr<AAsset> _assetPtr, const std::string& _path);

//}

	public:
		void Clear();

		/**
		 * @brief 
		 * Does \b not add asset reference count.
		 * 
		 * @tparam T 
		 * @param _path 
		 * @return AssetHandle<T> 
		 */
		template <typename T>
		AssetHandle<T> Get(const std::string& _path);
		

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

		/**
		 * @brief Unload asset previously registed at path.
		 * Any other reference of this asset loaded with another key path won't be decremented.
		 * 
		 * @param _path key path of the asset to unload.
		 */
		void Unload(const std::string& _path);

		/**
		 * @brief Unload asset previously registered.
		 * Every reference of this asset will be decremented once.
		 * 
		 * @param _asset Asset to unload.
		 */
		void Unload(std::shared_ptr<AAsset> _asset);

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
			const typename T::ImportInfos& _infos = typename T::ImportInfos());

//}


//{ Export



//}

	};
}

#include <SA/Engine/SDK/Assets/AssetHandle.hpp>
#include <SA/Engine/SDK/Assets/AssetManager.inl>

#endif // GUARD

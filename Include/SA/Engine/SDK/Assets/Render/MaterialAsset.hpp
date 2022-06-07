// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_ASSET_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_ASSET_GUARD

#include <string>

#include <SA/Engine/SDK/Assets/Render/ARenderAsset.hpp>

// Assimp
struct aiMaterial;


namespace SA::SDK
{
	struct MaterialImportInfos;

	class MaterialAsset : public ARenderAsset
	{
	public:

//{ Import

		struct ImportInfos : public ARenderAsset::ImportInfos
		{
			const aiMaterial* mat = nullptr;
		};


		bool Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos);

//}
	};
}

#endif // GUARD

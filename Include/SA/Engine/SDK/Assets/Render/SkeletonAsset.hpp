// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SKELETON_ASSET_GUARD
#define SAPPHIRE_ENGINE_SKELETON_ASSET_GUARD

#include <SA/Engine/SDK/Assets/Render/ARenderAsset.hpp>

// Assimp
struct aiMesh;


namespace SA::SDK
{
	struct SkeletonImportInfos;

	class SkeletonAsset : public ARenderAsset
	{
	public:

//{ Import

		struct ImportInfos : public ARenderAsset::ImportInfos
		{
			const aiMesh* mesh = nullptr;
		};


		bool Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos);

//}
	};
}

#endif // GUARD

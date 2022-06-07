// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SKELETAL_MESH_ASSET_GUARD
#define SAPPHIRE_ENGINE_SKELETAL_MESH_ASSET_GUARD

#include <SA/Engine/SDK/Assets/Render/MeshAsset.hpp>
#include <SA/Engine/SDK/Assets/Render/SkeletonAsset.hpp>

namespace SA::SDK
{
	class SkeletalMeshAsset : public MeshAsset
	{
		using MeshAsset::Import;

	public:
		std::string skeletonPath;


//{ Import

		struct ImportInfos : public MeshAsset::ImportInfos
		{
			SkeletonAsset::ImportInfos skelImport;

			void SetMesh(const aiMesh* _mesh);
		};


		bool Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos);

	private:
		bool ImportSkeleton(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos);

//}
	};
}

#endif // GUARD

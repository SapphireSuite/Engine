// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MESH_ASSET_GUARD
#define SAPPHIRE_ENGINE_MESH_ASSET_GUARD

#include <SA/Engine/SDK/Assets/Render/ARenderAsset.hpp>

#include <SA/Engine/Render/Base/Mesh/RawMesh.hpp>

#include <SA/Engine/SDK/Assets/Render/MaterialAsset.hpp>

// Assimp.
struct aiMesh;


namespace SA::SDK
{
	class MeshAsset : public ARenderAsset
	{
	public:
		RawMesh raw;

		std::string materialPath;


//{ Import

		struct ImportInfos : public ARenderAsset::ImportInfos
		{
			/// Output base path from model.
			std::string outModelBasePath;

			const aiMesh* mesh = nullptr;

			MaterialAsset::ImportInfos matImport;
		};


		bool Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos);

	private:

		bool ImportVertices(const ImportInfos& _infos);
		bool ImportIndices(const ImportInfos& _infos);
		bool ImportAABB(const ImportInfos& _infos);
		bool ImportMaterial(AssetMgr& _mgr, const ImportInfos& _infos);

//}
	};
}

#endif // GUARD

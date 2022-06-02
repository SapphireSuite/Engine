// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MESH_ASSET_GUARD
#define SAPPHIRE_ENGINE_MESH_ASSET_GUARD

#include <SA/Engine/SDK/Assets/Render/ARenderAsset.hpp>

#include <SA/Engine/Render/Base/Mesh/RawMesh.hpp>

// Assimp.
struct aiMesh;

namespace SA::SDK
{
	class MeshAsset : public ARenderAsset
	{
		bool Load(AssetMgr& _mgr, const std::string& _path, std::string&& _bin) override final;
		bool Save(AssetMgr& _mgr, const std::string& _path, std::string& _bin) const override final;

	public:
		RawMesh raw;

		bool Import(const aiMesh* aiMesh);
	};
}

#endif // GUARD

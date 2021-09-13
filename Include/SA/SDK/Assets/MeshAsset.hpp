// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_MESH_ASSET_GUARD
#define SAPPHIRE_SDK_MESH_ASSET_GUARD

#include <SA/SDK/Assets/AAsset.hpp>

#include <SA/Render/Base/Mesh/RawMesh.hpp>

namespace Sa
{
	class MeshAsset : public AAsset
	{
	public:
		RawMesh rawData;

		bool Load(const std::string& _path) override final;
		void UnLoad() override final;

		bool Save(const std::string& _path) const override final;
	};
}

#endif // GUARD

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MESH_ASSET_GUARD
#define SAPPHIRE_ENGINE_MESH_ASSET_GUARD

#include <SA/Engine/SDK/Assets/Render/ARenderAsset.hpp>

#include <SA/Engine/Render/Base/Mesh/RawMesh.hpp>

namespace SA::SDK
{
	class MeshAsset : public ARenderAsset
	{
		bool Load_Internal(std::string&& _bin) override final;
		bool Save_Internal(std::fstream& _fstream) const override final;

	public:
		RawMesh raw;

		bool IsValid() const override final;

		void UnLoad() override final;
	};
}

#endif // GUARD

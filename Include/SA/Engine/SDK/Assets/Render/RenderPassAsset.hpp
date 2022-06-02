// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RENDER_PASS_ASSET_GUARD
#define SAPPHIRE_ENGINE_RENDER_PASS_ASSET_GUARD

#include <SA/Engine/SDK/Assets/Render/ARenderAsset.hpp>

#include <SA/Engine/Render/Base/Pass/Descriptors/RenderPassDescriptor.hpp>

namespace SA::SDK
{
	class RenderPassAsset : public ARenderAsset
	{
		bool Load(AssetMgr& _mgr, const std::string& _path, std::string&& _bin) override final;
		bool Save(AssetMgr& _mgr, const std::string& _path, std::string& _bin) const override final;

	public:
		RenderPassDescriptor descriptor;
	};
}

#endif // GUARD

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
		bool Load_Internal(std::string&& _bin) override final;
		bool Save_Internal(std::fstream& _fstream) const override final;

	public:
		RenderPassDescriptor descriptor;

		bool IsValid() const override final;

		void UnLoad() override final;
	};
}

#endif // GUARD

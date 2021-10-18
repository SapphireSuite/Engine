// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_RENDER_PASS_ASSET_GUARD
#define SAPPHIRE_SDK_RENDER_PASS_ASSET_GUARD

#include <SA/SDK/Assets/Render/ARenderAsset.hpp>

#include <SA/Render/Base/Pass/RenderPassDescriptor.hpp>

namespace Sa
{
	class RenderPassAsset : public ARenderAsset
	{
		bool Load_Internal(Serialize::Reader&& _read, const std::string& _path) override final;
		bool Save_Internal(std::fstream& _fStream) const override final;
		bool Import_Internal(const std::string& _path) override final;

	public:
		RenderPassDescriptor raw;

		bool IsValid() const override final;

		void UnLoad() override final;
	};
}

#endif // GUARD

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_ASSET_GUARD
#define SAPPHIRE_ENGINE_SHADER_ASSET_GUARD

#include <SA/Engine/SDK/Assets/Render/ARenderAsset.hpp>

#include <SA/Engine/Render/Base/Shader/RawShader.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

namespace SA::SDK
{
	class ShaderAsset : public ARenderAsset
	{
		std::string mResourcePath;

		bool Load(AssetMgr& _mgr, const std::string& _path, std::string&& _bin) override final;
		bool Save(AssetMgr& _mgr, const std::string& _path, std::string& _bin) const override final;

	public:
		RawShader raw;
		ShaderDescriptor descriptor;

		bool Import(AssetMgr& _mgr, const std::string& _path);

		static bool ShouldCompileShader(const std::string& _assetPath, const std::string& _resPath) noexcept;
	};
}

#endif // GUARD

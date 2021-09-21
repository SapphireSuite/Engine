// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_SHADER_ASSET_GUARD
#define SAPPHIRE_SDK_SHADER_ASSET_GUARD

#include <SA/SDK/Assets/AAsset.hpp>

#include <SA/Render/Base/Shader/RawShader.hpp>

namespace Sa
{
	class ShaderAsset : public AAsset
	{
		std::string mResourcePath;

		static bool ShouldCompileShader(const std::string& _resourcePath, const std::string& _assetPath) noexcept;

	public:
		RawShader raw;


		bool IsValid() const override final;

		bool Load(const std::string& _path) override final;
		void UnLoad() override final;

		bool Save(const std::string& _path) const override final;

		bool Import(const std::string& _path) override final;
	};
}

#endif // GUARD

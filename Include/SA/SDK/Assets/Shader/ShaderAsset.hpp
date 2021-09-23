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

	protected:
		bool Load_Internal(std::string&& _bin) override final;
		bool Save_Internal(std::fstream& _fStream) const override final;
		bool Import_Internal(const std::string& _path) override final;

	public:
		RawShader raw;


		bool IsValid() const override final;

		void UnLoad() override final;
	};
}

#endif // GUARD

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_ASSET_GUARD
#define SAPPHIRE_ENGINE_SHADER_ASSET_GUARD

#include <SA/Engine/SDK/Assets/AAsset.hpp>

#include <SA/Engine/Render/Base/Shader/RawShader.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

namespace SA::SDK
{
	class ShaderAsset : AAsset
	{
		std::string mResourcePath;
		mutable std::string mAssetPath;

		bool Save_Internal(std::fstream& _fstream) const override final;
		bool Load_Internal(std::string&& _bin) override final;

		bool ShouldCompileShader() const noexcept;

	public:
		RawShader raw;
		ShaderDescriptor descriptor;
	
		bool IsValid() const override final;

		bool Load(const std::string& _path) override final;
		void UnLoad() override final;

		bool Save(const std::string& _path) const override final;

		bool Import(const std::string& _path) override final;
	};
}

#endif // GUARD

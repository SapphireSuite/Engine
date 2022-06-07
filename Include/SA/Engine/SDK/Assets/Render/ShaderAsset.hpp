// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_ASSET_GUARD
#define SAPPHIRE_ENGINE_SHADER_ASSET_GUARD

#include <SA/Engine/SDK/Assets/Render/ARenderAsset.hpp>
#include <SA/Engine/SDK/ShaderBuilder/ShaderLanguage.hpp>

#include <SA/Engine/Render/Base/Shader/RawShader.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

namespace SA::SDK
{
	class ShaderAsset : public ARenderAsset
	{
	public:
		RawShader raw;
		ShaderDescriptor descriptor;


//{ Import

		struct ImportInfos : public ARenderAsset::ImportInfos
		{
			ShaderLanguage language = ShaderLanguage::GLSL;
		};


		bool Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos);
//}
	};
}

#endif // GUARD

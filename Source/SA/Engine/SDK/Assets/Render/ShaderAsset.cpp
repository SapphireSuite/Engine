// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/ShaderAsset.hpp>

#include <SDK/ShaderBuilder/GLSL/GLSLShaderBuilder.hpp>

namespace SA::SDK
{
//{ Import

	std::unique_ptr<AShaderBuilder> SelectBuilder(ShaderLanguage _lang)
	{
		std::unique_ptr<AShaderBuilder> builder;

		switch (_lang)
		{
			case ShaderLanguage::GLSL:
			case ShaderLanguage::HLSL:
			{
				builder = std::make_unique<GLSL::ShaderBuilder>();
				break;
			}
			default:
				break;
		}

		return builder;
	}


	bool ShaderAsset::Import(AssetMgr& _mgr, const std::string& _path, const ImportInfos& _infos)
	{
		SA_LOG(L"Importing shader [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;


		std::unique_ptr<AShaderBuilder> builder = SelectBuilder(_infos.language);

		if (!builder)
		{
			SA_LOG(L"Shader language [" << _infos.language << L"] import not supported yet!", Error, SA/Engine/SDK/Asset/Shader);
			return false;
		}
		

		// mResourcePath = _resPath;

		return builder->Build(_path, raw, descriptor);
	}

//}
}

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/ShaderAsset.hpp>

#include <sys/stat.h>

#include <SA/Collections/Debug>

#include <SDK/ShaderBuilder/GLSL/GLSLShaderBuilder.hpp>


namespace SA::SDK
{
	bool ShaderAsset::Load(AssetMgr& _mgr, const std::string& _path, std::string&& _bin)
	{
		SA_LOG(L"Loading shader [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;

		Ser::BinaryStream ser(std::move(_bin));

		ser >> mResourcePath;

		if (ShouldCompileShader(_path, mResourcePath))
		{
			// Re-import shader for compilation.

			if (!Import(_mgr, mResourcePath))
			{
				SA_LOG(L"Shader {" << _path << L"} Re-import compilation failed!", Error, SA/Engine/SDK/Asset);
				return false;
			}
		}
		else
		{
			ser >> raw;
			ser >> descriptor;
		}

		return true;
	}
	
	
	bool ShaderAsset::Save(AssetMgr& _mgr, const std::string& _path, std::string& _bin) const
	{
		SA_LOG(L"Saving shader [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;
		(void)_path;

		Ser::BinaryStream ser;

		ser << mResourcePath;
		ser << raw;
		ser << descriptor;

		_bin = std::move(ser.bin);

		return true;
	}


	bool ShaderAsset::Import(AssetMgr& _mgr, const std::string& _path)
	{
		SA_LOG(L"Importing shader [" << _path << L"]", Infos, SA/Engine/SDK/Asset);

		(void)_mgr;

		GLSL::ShaderBuilder builder;
		// AShaderBuilderInterface* builder;

		mResourcePath = _path;

		return builder.Build(_path, raw, descriptor);
	}


	bool ShaderAsset::ShouldCompileShader(const std::string& _assetPath, const std::string& _resPath) noexcept
	{
		struct stat assetStat;
		struct stat resourceStat;

		if(!(stat(_resPath.c_str(), &resourceStat) == 0))
		{
			// Resource file stat failed: can't reimport, assume asset is up to date.

			return false;
		}
		else
		{
			stat(_assetPath.c_str(), &assetStat); // file currently opened: can't fail.

			// Check asset is up-to-date.
			return assetStat.st_mtime < resourceStat.st_mtime;
		}
	}
}

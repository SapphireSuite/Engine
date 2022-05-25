// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/ShaderAsset.hpp>

#include <sys/stat.h>

#include <SA/Collections/Debug>

#include <SA/Collections/SerializeBinary>

#include <SDK/ShaderBuilder/GLSL/GLSLShaderBuilder.hpp>


namespace SA::SDK
{
	bool ShaderAsset::IsValid() const
	{
		return !raw.data.empty();
	}


	bool ShaderAsset::Load(const std::string& _path)
	{
		mAssetPath = _path;

		return AAsset::Load(_path);
	}

	bool ShaderAsset::Load_Internal(std::string&& _bin)
	{
		Ser::BinaryStream ser(std::move(_bin));

		ser >> mResourcePath;

		if (ShouldCompileShader())
		{
			// Re-import shader for compilation.

			if (!Import(mResourcePath))
			{
				SA_LOG(L"Shader {" << mAssetPath << L"} Re-import compilation failed!", Error, SA/Engine/SDK/Asset);
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

	void ShaderAsset::UnLoad()
	{
		mResourcePath.clear();

		raw.Clear();
		descriptor.Clear();
	}


	bool ShaderAsset::Save(const std::string& _path) const
	{
		mAssetPath = _path;

		return AAsset::Save(_path);
	}

	bool ShaderAsset::Save_Internal(std::fstream& _fstream) const
	{
		Ser::BinaryStream ser;

		ser << mResourcePath;
		ser << raw;
		ser << descriptor;

		_fstream << ser.bin;

		return true;
	}


	bool ShaderAsset::Import(const std::string& _path)
	{
		GLSL::ShaderBuilder builder;
		// AShaderBuilderInterface* builder;

		mResourcePath = _path;

		return builder.Build(_path, raw, descriptor);
	}


	bool ShaderAsset::ShouldCompileShader() const noexcept
	{
		struct stat assetStat;
		struct stat resourceStat;

		if(!(stat(mResourcePath.c_str(), &resourceStat) == 0))
		{
			// Resource file stat failed: can't reimport, assume asset is up to date.

			return false;
		}
		else
		{
			stat(mAssetPath.c_str(), &assetStat); // file currently opened: can't fail.

			// Check asset is up-to-date.
			return assetStat.st_mtime < resourceStat.st_mtime;
		}
	}
}

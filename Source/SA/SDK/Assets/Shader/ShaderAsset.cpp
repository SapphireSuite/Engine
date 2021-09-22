// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Shader/ShaderAsset.hpp>

#include <sstream>
#include <fstream>

#include <Core/Algorithms/SizeOf.hpp>

#include <SDK/Assets/Shader/ShaderCompiler.hpp>
#include <SDK/Assets/Shader/ShaderReflector.hpp>


namespace Sa
{
	ShaderCompiler compiler;
	ShaderReflector reflector;


	bool ShaderAsset::ShouldCompileShader(const std::string& _resourcePath, const std::string& _assetPath) noexcept
	{
		struct stat assetStat;
		struct stat resourceStat;

		return stat(_assetPath.c_str(), &assetStat) != 0 ||
			stat(_resourcePath.c_str(), &resourceStat) != 0 ||
			assetStat.st_mtime < resourceStat.st_mtime;
	}


	bool ShaderAsset::IsValid() const
	{
		return !raw.data.empty();
	}

	
	bool ShaderAsset::Load(const std::string& _path)
	{
		std::string bin;

		if (!ReadFile(_path, bin))
			return false;


		Serialize::Reader read = std::move(bin);

		Serialize::FromBinary(mResourcePath, read);
		Serialize::FromBinary(raw, read);

		return true;
	}
	
	void ShaderAsset::UnLoad()
	{
		mResourcePath.clear();
		raw.Reset();
	}

	
	bool ShaderAsset::Save(const std::string& _path) const
	{
		if (!AAsset::Save(_path))
			return false;


		std::fstream fStream(_path, std::fstream::binary | std::fstream::out | std::fstream::trunc);

		if (!fStream.is_open())
		{
			SA_LOG(L"Failed to open file {" << _path << L"}!", Error, SA/SDK/Asset);
			return false;
		}


		fStream << Serialize::ToBinary(mResourcePath);
		fStream << Serialize::ToBinary(raw);

		return true;
	}

	
	bool ShaderAsset::Import(const std::string& _path)
	{
		mResourcePath = _path;
		raw.descriptor.stage = ShaderStageFromFile(_path);

		if (!compiler.Compile(_path, raw))
			return false;

		if (!reflector.Reflect(raw))
			return false;

		return true;
	}
}

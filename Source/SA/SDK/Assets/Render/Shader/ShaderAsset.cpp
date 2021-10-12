// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/Shader/ShaderAsset.hpp>

#include <fstream>

#include <Core/Algorithms/SizeOf.hpp>
#include <Core/Serialize/Serializer.hpp>

#include <SDK/Assets/Render/Shader/ShaderCompiler.hpp>
#include <SDK/Assets/Render/Shader/ShaderReflector.hpp>


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

	
	bool ShaderAsset::Load_Internal(std::string&& _bin)
	{
		Serialize::Reader read = std::move(_bin);

		Serialize::FromBinary(mResourcePath, read);
		Serialize::FromBinary(raw, read);

		return true;
	}
	
	void ShaderAsset::UnLoad()
	{
		mResourcePath.clear();
		raw.Reset();
	}

	
	bool ShaderAsset::Save_Internal(std::fstream& _fStream) const
	{
		_fStream << Serialize::ToBinary(mResourcePath);
		_fStream << Serialize::ToBinary(raw);

		return true;
	}

	
	bool ShaderAsset::Import_Internal(const std::string& _path)
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
// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/Shader/ShaderAsset.hpp>

#include <fstream>

#include <Core/Algorithms/SizeOf.hpp>
#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
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
		// TODO: Use ShouldCompileShader.

		Serialize::Reader read = std::move(_bin);

		Serialize::FromBinary(mResourcePath, read);
		Serialize::FromBinary(raw, read);
		Serialize::FromBinary(descriptor, read);

		return true;
	}
	
	void ShaderAsset::UnLoad()
	{
		mResourcePath.clear();

		raw.Clear();
		descriptor.Clear();
	}

	
	bool ShaderAsset::Save_Internal(std::fstream& _fStream) const
	{
		_fStream << Serialize::ToBinary(mResourcePath);
		_fStream << Serialize::ToBinary(raw);
		_fStream << Serialize::ToBinary(descriptor);

		return true;
	}

	
	bool ShaderAsset::Import_Internal(const std::string& _path)
	{
		mResourcePath = _path;

		// TODO: Use Shader interface.

		//if (!compiler.Compile(_path, raw))
		//	return false;

		//if (!reflector.Reflect(raw))
		//	return false;

		return true;
	}
}

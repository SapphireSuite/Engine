// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Render/ShaderAsset.hpp>

#include <Core/Algorithms/SizeOf.hpp>
#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
	ShaderAsset::ShaderAsset(const AShaderBuilderInterface* _shaderBuilder) noexcept :
		mShaderBuilder{ _shaderBuilder }
	{
	}


	bool ShaderAsset::IsValid() const
	{
		return !raw.data.empty();
	}

	
	bool ShaderAsset::Load_Internal(Serialize::Reader&& _read, const std::string& _path)
	{
		Serialize::FromBinary(mResourcePath, _read);

		if (ShouldCompileShader(mResourcePath, _path))
		{
			// Re-import shader for compilation.

			if (!Import(mResourcePath))
			{
				SA_LOG("Shader {" << _path << L"} Re-import compilation failed!", Error, SA/SDK/Asset);
				return false;
			}
		}
		else
		{
			Serialize::FromBinary(raw, _read);
			Serialize::FromBinary(descriptor, _read);
		}

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

		SA_ASSERT(Nullptr, SA/SDK, mShaderBuilder, L"Try import shader with nullptr shader builder interface!");

		return mShaderBuilder->Build(_path, raw, descriptor);
	}


	bool ShaderAsset::ShouldCompileShader(const std::string& _resourcePath, const std::string& _assetPath) noexcept
	{
		struct stat assetStat;
		struct stat resourceStat;

		return stat(_assetPath.c_str(), &assetStat) != 0 ||
			stat(_resourcePath.c_str(), &resourceStat) != 0 ||
			assetStat.st_mtime < resourceStat.st_mtime;
	}
}

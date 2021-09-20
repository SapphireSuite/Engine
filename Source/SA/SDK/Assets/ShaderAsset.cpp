// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/ShaderAsset.hpp>

#include <fstream>

#include <Core/Algorithms/SizeOf.hpp>

#include <SDK/Assets/Shader/ShaderCompiler.hpp>


namespace Sa
{
	ShaderCompiler compiler;


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
		return !rawData.data.empty();
	}

	
	bool ShaderAsset::Load(const std::string& _path)
	{
		std::fstream fStream(_path, std::ios::binary | std::ios_base::in);

		if (!fStream.is_open())
		{
			SA_LOG("Failed to open file {" << _path << L"}!", Error, SA / SDK / Asset);
			return false;
		}


		// Resource path.
		{
			uint32 resourcePathSize = 0u;
			fStream.read(reinterpret_cast<char*>(&resourcePathSize), sizeof(uint32));

			if (resourcePathSize == 0u)
			{
				SA_LOG("Shader resource path invalid!", Error, SA/SDK/Asset);
				return false;
			}


			mResourcePath.resize(resourcePathSize);
			fStream.read(mResourcePath.data(), resourcePathSize);
		}


		// Data
		{
			if (!ShouldCompileShader(mResourcePath, _path)) // Read saved shader.
			{
				// Data.
				uint32 dataSize = 0u;
				fStream.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32));

				if (dataSize == 0u)
				{
					SA_LOG("Shader data invalid!", Error, SA/SDK/Asset);
					return false;
				}

				rawData.data.resize(dataSize / sizeof(uint32));
				fStream.read(reinterpret_cast<char*>(rawData.data.data()), dataSize);
			}
			else if (!Import(mResourcePath))
			{
				SA_LOG("Shader Re-import compilation failed!", Error, SA/SDK/Asset);
				return false;
			}
		}

		return true;
	}
	
	void ShaderAsset::UnLoad()
	{
		mResourcePath.clear();
		rawData.data.clear();
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


		// Resource path.
		{
			const uint32 resourcePathSize = SizeOf<uint32>(mResourcePath);
			fStream.write(reinterpret_cast<const char*>(&resourcePathSize), sizeof(uint32));

			fStream.write(mResourcePath.data(), resourcePathSize);
		}


		// Data.
		{
			const uint32 dataSize = OctSizeOf<uint32>(rawData.data);
			fStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32));

			fStream.write(reinterpret_cast<const char*>(rawData.data.data()), dataSize);
		}

		return true;
	}

	
	bool ShaderAsset::Import(const std::string& _path)
	{
		mResourcePath = _path;

		return compiler.Compile(_path, rawData.data);
	}
}

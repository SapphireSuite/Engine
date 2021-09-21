// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Shader/ShaderAsset.hpp>

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
			if (ShouldCompileShader(mResourcePath, _path))
			{
				// Re-import shader for compilation.

				if (!Import(mResourcePath))
				{
					SA_LOG("Shader Re-import compilation failed!", Error, SA/SDK/Asset);
					return false;
				}

				// Stop parsing on re-import success.
				return true;
			}
			else // Read saved shader.
			{
				// Data.
				uint32 dataSize = ~uint32();
				fStream.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32));

				if (dataSize == ~uint32())
				{
					SA_LOG("Shader data invalid!", Error, SA/SDK/Asset);
					return false;
				}

				rawData.data.resize(dataSize / sizeof(uint32));
				fStream.read(reinterpret_cast<char*>(rawData.data.data()), dataSize);
			}
		}


		// Layout
		{
			// Stage.
			{
				fStream.read(reinterpret_cast<char*>(&rawData.descriptor.stage), sizeof(ShaderStage));

				if (rawData.descriptor.stage == ShaderStage::Vertex)
					fStream.read(reinterpret_cast<char*>(&rawData.descriptor.vertexLayout), sizeof(VertexComp));
			}


			// Bindings.
			{
				uint32 dataSize = ~uint32();
				fStream.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32));

				if (dataSize == ~uint32())
				{
					SA_LOG("Shader binding data invalid!", Error, SA / SDK / Asset);
					return false;
				}

				rawData.descriptor.bindings.resize(dataSize / sizeof(ShaderBindingDescriptor));
				fStream.read(reinterpret_cast<char*>(rawData.descriptor.bindings.data()), dataSize);
			}


			// SpecConstants.
			{
				uint32 dataSize = ~uint32();
				fStream.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32));

				if (dataSize == ~uint32())
				{
					SA_LOG("Shader spec constants data invalid!", Error, SA/SDK/Asset);
					return false;
				}

				rawData.descriptor.specConstants.resize(dataSize / sizeof(SpecConstantDescriptor));
				fStream.read(reinterpret_cast<char*>(rawData.descriptor.specConstants.data()), dataSize);
			}
		}

		return true;
	}
	
	void ShaderAsset::UnLoad()
	{
		mResourcePath.clear();
		rawData.Reset();
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


		// Layout
		{
			// Stage.
			{
				fStream.write(reinterpret_cast<const char*>(&rawData.descriptor.stage), sizeof(ShaderStage));

				if (rawData.descriptor.stage == ShaderStage::Vertex)
					fStream.write(reinterpret_cast<const char*>(&rawData.descriptor.vertexLayout), sizeof(VertexComp));
			}


			// Bindings.
			{
				const uint32 dataSize = OctSizeOf<uint32>(rawData.descriptor.bindings);
				fStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32));
				fStream.write(reinterpret_cast<const char*>(rawData.descriptor.bindings.data()), dataSize);
			}

			// SpecConstants.
			{
				const uint32 dataSize = OctSizeOf<uint32>(rawData.descriptor.specConstants);
				fStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32));
				fStream.write(reinterpret_cast<const char*>(rawData.descriptor.specConstants.data()), dataSize);
			}
		}

		return true;
	}

	
	bool ShaderAsset::Import(const std::string& _path)
	{
		mResourcePath = _path;
		rawData.descriptor.stage = ShaderStageFromFile(_path);

		if (!compiler.Compile(_path, rawData))
			return false;

		if (!reflector.Reflect(rawData))
			return false;

		return true;
	}
}

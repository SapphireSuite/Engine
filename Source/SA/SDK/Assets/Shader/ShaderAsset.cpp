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
		return !raw.data.empty();
	}

	
	bool ShaderAsset::Load(const std::string& _path)
	{
		std::fstream fStream(_path, std::ios::binary | std::ios_base::in);

		if (!fStream.is_open())
		{
			SA_LOG("Failed to open file {" << _path << L"}!", Error, SA/SDK/Asset);
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

				raw.data.resize(dataSize / sizeof(uint32));
				fStream.read(reinterpret_cast<char*>(raw.data.data()), dataSize);
			}
		}


		// Descriptor
		{
			// Stage.
			{
				fStream.read(reinterpret_cast<char*>(&raw.descriptor.stage), sizeof(ShaderStage));

				if (raw.descriptor.stage == ShaderStage::Vertex)
					fStream.read(reinterpret_cast<char*>(&raw.descriptor.vertexLayout), sizeof(VertexComp));
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

				raw.descriptor.bindings.resize(dataSize / sizeof(ShaderBindingDescriptor));

				for (auto& bind : raw.descriptor.bindings)
				{
					uint32 nameSize = ~uint32();
					fStream.read(reinterpret_cast<char*>(&nameSize), sizeof(uint32));

					if (nameSize == ~uint32())
					{
						SA_LOG("Shader binding name invalid!", Error, SA/SDK/Asset);
						return false;
					}


					bind.name.resize(nameSize);
					fStream.read(bind.name.data(), nameSize);


					fStream.read(reinterpret_cast<char*>(&bind.type), sizeof(ShaderBindingDescriptor) - sizeof(std::string));
				}
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

				raw.descriptor.specConstants.resize(dataSize / sizeof(SpecConstantDescriptor));


				for (auto& spec : raw.descriptor.specConstants)
				{
					uint32 nameSize = ~uint32();
					fStream.read(reinterpret_cast<char*>(&nameSize), sizeof(uint32));

					if (nameSize == ~uint32())
					{
						SA_LOG("Shader spec constants name invalid!", Error, SA/SDK/Asset);
						return false;
					}


					spec.name.resize(nameSize);
					fStream.read(spec.name.data(), nameSize);

					fStream.read(reinterpret_cast<char*>(&spec.id), sizeof(SpecConstantDescriptor) - sizeof(std::string));
				}
			}
		}

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


		// Resource path.
		{
			const uint32 resourcePathSize = SizeOf<uint32>(mResourcePath);
			fStream.write(reinterpret_cast<const char*>(&resourcePathSize), sizeof(uint32));

			fStream.write(mResourcePath.data(), resourcePathSize);
		}


		// Data.
		{
			const uint32 dataSize = OctSizeOf<uint32>(raw.data);
			fStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32));

			fStream.write(reinterpret_cast<const char*>(raw.data.data()), dataSize);
		}


		// Descriptor.
		{
			// Stage.
			{
				fStream.write(reinterpret_cast<const char*>(&raw.descriptor.stage), sizeof(ShaderStage));

				if (raw.descriptor.stage == ShaderStage::Vertex)
					fStream.write(reinterpret_cast<const char*>(&raw.descriptor.vertexLayout), sizeof(VertexComp));
			}


			// Bindings.
			{
				const uint32 dataSize = OctSizeOf<uint32>(raw.descriptor.bindings);
				fStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32));

				for (auto& bind : raw.descriptor.bindings)
				{
					const uint32 nameSize = OctSizeOf<uint32>(bind.name);
					fStream.write(reinterpret_cast<const char*>(&nameSize), sizeof(uint32));
					fStream.write(bind.name.c_str(), nameSize);

					fStream.write(reinterpret_cast<const char*>(&bind.type), sizeof(ShaderBindingDescriptor) - sizeof(std::string));
				}
			}

			// SpecConstants.
			{
				const uint32 dataSize = OctSizeOf<uint32>(raw.descriptor.specConstants);
				fStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32));

				for (auto& spec : raw.descriptor.specConstants)
				{
					const uint32 nameSize = OctSizeOf<uint32>(spec.name);
					fStream.write(reinterpret_cast<const char*>(&nameSize), sizeof(uint32));
					fStream.write(spec.name.c_str(), nameSize);
					
					fStream.write(reinterpret_cast<const char*>(&spec.id), sizeof(SpecConstantDescriptor) - sizeof(std::string));
				}
			}
		}

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

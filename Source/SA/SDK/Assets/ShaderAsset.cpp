// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/ShaderAsset.hpp>

#include <fstream>
#include <sstream>

// GLSL compiler.
#include <shaderc/shaderc.hpp>

#include <Core/Algorithms/SizeOf.hpp>

namespace Sa
{
	shaderc_shader_kind GetShaderKind(const std::string& _resourcePath)
	{
		const uint32 extIndex = static_cast<uint32>(_resourcePath.find_last_of('.'));
		SA_ASSERT(Default, SA/SDK/Asset, extIndex != ~uint32(), L"Invalid resource extension {" << _resourcePath << L"}");
		
		const std::string extension = _resourcePath.substr(extIndex + 1);

		if (extension == "vert")
			return shaderc_glsl_vertex_shader;
		else if(extension == "frag")
			return shaderc_glsl_fragment_shader;
		else if (extension == "comp")
			return shaderc_glsl_compute_shader;
		else if (extension == "geom")
			return shaderc_glsl_geometry_shader;
		else if (extension == "tesc")
			return shaderc_glsl_tess_control_shader;
		else if (extension == "tese")
			return shaderc_glsl_tess_evaluation_shader;
		else
		{
			SA_LOG("Invalid shader extension {"<< extension << L"}", Error, SA/SDK/Asset);
			return shaderc_shader_kind(0);
		}
	}
	

	bool ShaderAsset::ShouldCompileShader(const std::string& _resourcePath, const std::string& _assetPath) noexcept
	{
		struct stat assetStat;
		struct stat resourceStat;

		return stat(_assetPath.c_str(), &assetStat) != 0 ||
			stat(_resourcePath.c_str(), &resourceStat) != 0 ||
			assetStat.st_mtime < resourceStat.st_mtime;
	}
	
	bool ShaderAsset::CompileShader(const std::string& _resourcePath)
	{
		static shaderc::Compiler compiler;

		SA_LOG(L"Compiling shader {" << _resourcePath << L"}", Infos, SA / SDK / Asset);


		std::stringstream code;

		// Query shader code
		{
			std::fstream fStream(_resourcePath, std::fstream::binary | std::ios_base::in);

			if (!fStream.is_open())
			{
				SA_LOG(L"Failed to open file {" << _resourcePath << L"}!", Error, SA / SDK / Asset);
				return false;
			}

			code << fStream.rdbuf();
		}


		// Compilation
		{
			shaderc::CompileOptions options;

#if !SA_DEBUG
			options.SetOptimizationLevel(shaderc_optimization_level_performance);
#endif


			const shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(_resourcePath, GetShaderKind(_resourcePath), code.str().c_str(), options);

			if (module.GetCompilationStatus() != shaderc_compilation_status_success)
			{
				SA_LOG(L"Shader {" << _resourcePath << L"} compilation failed", Error, SA/SDK/Asset, module.GetErrorMessage());

				return false;
			}


			// Copy data.
			rawData.data = { module.cbegin(), module.cend() };
			//std::memmove(rawData.data.data(), module.cbegin(), module.cend() - module.cbegin());
		}

		return true;
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
				SA_LOG("Shader resource path invalid!", Error, SA / SDK / Asset);
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

		return CompileShader(_path);
	}
}

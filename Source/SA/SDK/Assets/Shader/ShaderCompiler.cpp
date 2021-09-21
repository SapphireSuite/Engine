// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Shader/ShaderCompiler.hpp>

#include <sstream>
#include <fstream>

#include <Collections/Debug>

#include <Render/Base/Shader/RawShader.hpp>

#include <SDK/EnvironmentVariable.hpp>
#include <SDK/Assets/Shader/ShaderFileIncluder.hpp>

namespace Sa
{
	shaderc_shader_kind GetShaderKind(ShaderStage _stage)
	{
		switch (_stage)
		{
			case Sa::ShaderStage::Vertex:
				return shaderc_glsl_vertex_shader;
			case Sa::ShaderStage::Fragment:
				return shaderc_glsl_fragment_shader;
			case Sa::ShaderStage::Geometry:
				return shaderc_glsl_geometry_shader;
			case Sa::ShaderStage::Compute:
				return shaderc_glsl_compute_shader;
			default:
			{
				SA_LOG(L"Shader stage [" << _stage << L"] conversion to shader kind failed!", Error, SA / SDK / Asset);
				return shaderc_shader_kind(0);
			}
		}
	}

	void SetStageOptions(shaderc::CompileOptions& options, ShaderStage _stage)
	{
		switch (_stage)
		{
			case Sa::ShaderStage::Vertex:
				options.AddMacroDefinition("VERTEX");
				break;
			case Sa::ShaderStage::Fragment:
				options.AddMacroDefinition("FRAGMENT");
				break;
			case Sa::ShaderStage::Geometry:
				options.AddMacroDefinition("GEOMETRY");
				break;
			case Sa::ShaderStage::Compute:
				options.AddMacroDefinition("COMPUTE");
				break;
			default:
			{
				SA_LOG(L"Shader compiler option for stage [" << _stage << L"] not supported yet!", Error, SA / SDK / Asset);
			}
		}
	}


	std::string ShaderCompiler::AssembleShader(const std::string& _path)
	{
		std::string code;


		// Read File.
		{
			std::fstream fStream(_path, std::ios_base::in);

			if (!fStream.is_open())
			{
				SA_LOG(L"Failed to open file {" << _path << L"}!", Error, SA/SDK/Asset);
				return "";
			}


			std::stringstream scode;
			scode << fStream.rdbuf();

			code = scode.str();
		}


		// Rename use main() by main_user()
		{
			const uint64 index = code.find("main");

			if (index == std::string::npos)
			{
				SA_LOG(L"No main function found in file {" << _path << L"}", Error, SA/SDK/Asset);
				return "";
			}

			code.replace(index, 4, "main_user");
		}


		// Append engine main().
		{
			static std::string mainEnginePath = EnvVar::path + "\\Resources\\Shaders\\Lib\\main_engine.glsl";

			std::fstream fStream(mainEnginePath, std::ios_base::in);

			if (!fStream.is_open())
			{
				SA_LOG(L"Failed to open file main engine!", Error, SA/SDK/Asset);
				return "";
			}


			std::stringstream scode;
			scode << fStream.rdbuf();

			code += scode.str();
		}


		return code;
	}

	bool ShaderCompiler::Compile(const std::string& _path, RawShader& _raw)
	{
		SA_LOG(L"Compiling shader {" << _path << L"}", Infos, SA/SDK/Asset);

		const std::string code = AssembleShader(_path);

		shaderc::CompileOptions options;
		SetStageOptions(options, _raw.stage);
		options.SetIncluder(std::make_unique<ShaderFileIncluder>());

#if !SA_DEBUG
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
#endif


		shaderc::SpvCompilationResult module =
			mHandle.CompileGlslToSpv(code.data(), code.size(), GetShaderKind(_raw.stage), _path.c_str(), options);

		if (module.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			SA_LOG(L"Shader {" << _path << L"} compilation failed with " <<
				module.GetNumErrors() << L" Errors and " <<
				module.GetNumWarnings() << " Warnings.",
				Error, SA/SDK/Asset, module.GetErrorMessage());

			return false;
		}
		else if (module.GetNumWarnings())
		{
			SA_LOG(L"Shader {" << _path << L"} compilation success with " <<
				module.GetNumWarnings() << " Warnings.",
				Warning, SA/SDK/Asset, module.GetErrorMessage());
		}


		// Copy data.
		_raw.data = { module.cbegin(), module.cend() };

		return true;
	}
}

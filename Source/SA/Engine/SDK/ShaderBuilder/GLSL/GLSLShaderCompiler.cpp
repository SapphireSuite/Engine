// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/ShaderBuilder/GLSL/GLSLShaderCompiler.hpp>

#include <SA/Collections/Debug>


#include <Render/Base/Shader/RawShader.hpp>
#include <Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

#include <SDK/Misc/ReadFile.hpp>
#include <SDK/ShaderBuilder/GLSL/GLSLShaderFileIncluder.hpp>

namespace SA::GLSL
{
	shaderc_shader_kind GetShaderKind(ShaderStage _stage)
	{
		switch (_stage)
		{
			case ShaderStage::Vertex:
				return shaderc_glsl_vertex_shader;
			case ShaderStage::Fragment:
				return shaderc_glsl_fragment_shader;
			case ShaderStage::Geometry:
				return shaderc_glsl_geometry_shader;
			case ShaderStage::Compute:
				return shaderc_glsl_compute_shader;
			default:
			{
				SA_LOG(L"Shader stage [" << _stage << L"] conversion to shader kind failed!", Error, SA/Engine/SDK/Asset);
				return shaderc_shader_kind(0);
			}
		}
	}

	void SetStageOptions(shaderc::CompileOptions& options, ShaderStage _stage)
	{
		switch (_stage)
		{
			case ShaderStage::Vertex:
				options.AddMacroDefinition("VERTEX");
				break;
			case ShaderStage::Fragment:
				options.AddMacroDefinition("FRAGMENT");
				break;
			case ShaderStage::Geometry:
				options.AddMacroDefinition("GEOMETRY");
				break;
			case ShaderStage::Compute:
				options.AddMacroDefinition("COMPUTE");
				break;
			default:
			{
				SA_LOG(L"Shader compiler option for stage [" << _stage << L"] not supported yet!", Error, SA/Engine/SDK/Asset);
			}
		}
	}


	std::string ShaderCompiler::AssembleShader(const std::string& _path) const
	{
		std::string code;

		if (!ReadFile(_path, code))
			return "";


		// Rename use main() by main_user()
		{
			const uint64_t index = code.find("main");

			if (index == std::string::npos)
			{
				SA_LOG(L"No main function found in file {" << _path << L"}", Error, SA/Engine/SDK/Asset);
				return "";
			}

			code.replace(index, 4, "main_user");
		}


		// Append engine main().
		{
			static std::string mainEnginePath = "Resources/Shaders/Lib/main_engine.glsl";

			std::string mainCode;
			
			if (!ReadFile(mainEnginePath, mainCode))
				return "";

			code += mainCode;
		}


		return code;
	}

	bool ShaderCompiler::Compile(const std::string& _path, RawShader& _raw, ShaderDescriptor& _desc) const
	{
		SA_LOG(L"Compiling shader {" << _path << L"}", Infos, SA/Engine/SDK/Asset);

		const std::string code = AssembleShader(_path);

		_desc.stage = ShaderStageFromFile(_path);

		shaderc::CompileOptions options;
		SetStageOptions(options, _desc.stage);
		options.SetIncluder(std::make_unique<ShaderFileIncluder>());

#if !SA_DEBUG
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
#endif


		shaderc::SpvCompilationResult module =
			mHandle.CompileGlslToSpv(code.data(), code.size(), GetShaderKind(_desc.stage), _path.c_str(), options);

		if (module.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			SA_LOG(L"Shader {" << _path << L"} compilation failed with " <<
				module.GetNumErrors() << L" Errors and " <<
				module.GetNumWarnings() << " Warnings.",
				Error, SA/Engine/SDK/Asset, module.GetErrorMessage());

			return false;
		}
		else if (module.GetNumWarnings())
		{
			SA_LOG(L"Shader {" << _path << L"} compilation success with " <<
				module.GetNumWarnings() << " Warnings.",
				Warning, SA/Engine/SDK/Asset, module.GetErrorMessage());
		}


		// Copy data.
		_raw.data = { module.cbegin(), module.cend() };

		return true;
	}
}

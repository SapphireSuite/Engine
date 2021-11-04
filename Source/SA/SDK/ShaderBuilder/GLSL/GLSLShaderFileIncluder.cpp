// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/ShaderBuilder/GLSL/GLSLShaderFileIncluder.hpp>

#include <libshaderc_util/io_shaderc.h>

#include <Collections/Debug>

#include <SDK/EnvironmentVariable.hpp>

namespace Sa::GLSL
{
	shaderc_include_result* MakeError(const std::string& message)
	{
		return new shaderc_include_result{ nullptr, 0u, message.c_str(), message.size() };
	}


	std::string ShaderFileIncluder::GetFullPath(const std::string& _requestedSrc, const std::string& _requestingSrc, shaderc_include_type _type)
	{
		switch (_type)
		{
			case shaderc_include_type_relative:		// include "file.glsl"
			{
				const uint64 dirIndex = _requestingSrc.find_last_of("/");

				if (dirIndex != std::string::npos)
					return _requestingSrc.substr(0u, dirIndex + 1) + _requestedSrc;

				return "";
			}
			case shaderc_include_type_standard:		// include <file.glsl>
			{
				static const std::string shaderLibPath = EnvVar::path + "/Resources/Shaders/Lib";

				return shaderLibPath + "/" + _requestedSrc;
			}
			default:
			{
				SA_LOG(L"Shaderc include type [" << _type << L"] not supported yet!", Error, SA/SDK/Asset);
				return "";
			}
		}
	}

	shaderc_include_result* ShaderFileIncluder::GetInclude_Internal(const std::string& _requestedSrc,
		shaderc_include_type _type,
		const std::string& _requestingSrc,
		size_t _includeDepth)
	{
		(void)_includeDepth;

		const std::string fullPath = GetFullPath(_requestedSrc, _requestingSrc, _type);

		if (fullPath.empty())
			return MakeError("Can't find included file {" << _requestedSrc << "} from {" << _requestingSrc << "}");


		// File already included: don't add code.
		if (mRegisteredIncludes.find(fullPath) != mRegisteredIncludes.end())
		{
			static const char* emptyInclude = " ";
			static const char emptyIncludeName[] = "EmptyInclude";

			return new shaderc_include_result{
				emptyIncludeName, sizeof(emptyIncludeName),
				emptyInclude, 1u,
				nullptr
			};
		}


		std::vector<char> content;

		if(!shaderc_util::ReadFile(fullPath, &content))
			return MakeError("Can't read included file {" << _requestedSrc << "} from {" << _requestingSrc << "}");


		mRegisteredIncludes.emplace(fullPath);

		FileInfos* const fInfos = new FileInfos{ std::move(fullPath), std::move(content) };

		return new shaderc_include_result{
			fInfos->fullPath.c_str(), fInfos->fullPath.size(),
			fInfos->content.data(), fInfos->content.size(),
			fInfos
		};
	}


	shaderc_include_result* ShaderFileIncluder::GetInclude(const char* _requestedSrc,
		shaderc_include_type _type,
		const char* _requestingSrc,
		size_t _includeDepth)
	{
		return GetInclude_Internal(_requestedSrc, _type, _requestingSrc, _includeDepth);
	}

	void ShaderFileIncluder::ReleaseInclude(shaderc_include_result* _data)
	{
		if (_data->user_data)
			delete static_cast<FileInfos*>(_data->user_data);

		delete _data;
	}
}

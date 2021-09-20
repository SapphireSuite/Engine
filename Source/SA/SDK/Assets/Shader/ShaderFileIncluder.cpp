// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/Assets/Shader/ShaderFileIncluder.hpp>

#include <libshaderc_util/io_shaderc.h>

#include <Collections/Debug>

namespace Sa
{
	const std::string shaderLibPath = std::string(getenv("SA_ENGINE_PATH")) + "\\Resources\\Shaders\\Lib";


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
				const uint64 dirIndex = _requestingSrc.find_last_of("/\\");

				if (dirIndex != std::string::npos)
					return _requestingSrc.substr(0u, dirIndex + 1) + _requestedSrc;

				return "";
			}
			case shaderc_include_type_standard:		// include <file.glsl>
			{
				return shaderLibPath + "\\" + _requestedSrc;
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
		std::string fullPath = GetFullPath(_requestedSrc, _requestingSrc, _type);

		if (fullPath.empty())
			return MakeError("Can't find included file {" << _requestedSrc << "} from {" << _requestingSrc << "}");


		std::vector<char> content;

		if(!shaderc_util::ReadFile(fullPath, &content))
			return MakeError("Can't read included file {" << _requestedSrc << "} from {" << _requestingSrc << "}");


		FileInfos* fInfos = new FileInfos{ std::move(fullPath), std::move(content) };

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
		delete static_cast<FileInfos*>(_data->user_data);

		delete _data;
	}
}

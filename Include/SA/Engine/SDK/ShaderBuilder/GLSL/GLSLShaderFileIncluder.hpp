// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_GLSL_SHADER_FILE_INCLUDER_GUARD
#define SAPPHIRE_ENGINE_GLSL_SHADER_FILE_INCLUDER_GUARD

#include <unordered_set>

#include <shaderc/shaderc.hpp>

namespace SA::SDK::GLSL
{
	class ShaderFileIncluder : public shaderc::CompileOptions::IncluderInterface
	{
		struct FileInfos
		{
			std::string fullPath;
			std::vector<char> content;
		};


		std::string GetFullPath(const std::string& _requestedSrc, const std::string& _requestingSrc, shaderc_include_type _type);

		shaderc_include_result* GetInclude_Internal(const std::string& _requestedSrc,
			shaderc_include_type _type,
			const std::string& _requestingSrc,
			size_t _includeDepth);

		std::unordered_set<std::string> mRegisteredIncludes;

	public:
		shaderc_include_result* GetInclude(const char* _requestedSrc,
			shaderc_include_type _type,
			const char* _requestingSrc,
			size_t _includeDepth) override final;

		void ReleaseInclude(shaderc_include_result* _data) override final;
	};
}

#endif // GUARD

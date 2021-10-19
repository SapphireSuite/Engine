// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_GLSL_SHADER_FILE_INCLUDER_GUARD
#define SAPPHIRE_RENDER_GLSL_SHADER_FILE_INCLUDER_GUARD

#include <shaderc/shaderc.hpp>

namespace Sa::GLSL
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

	public:
		shaderc_include_result* GetInclude(const char* _requestedSrc,
			shaderc_include_type _type,
			const char* _requestingSrc,
			size_t _includeDepth) override final;

		void ReleaseInclude(shaderc_include_result* _data) override final;
	};
}

#endif // GUARD

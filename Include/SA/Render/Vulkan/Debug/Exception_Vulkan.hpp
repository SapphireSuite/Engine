// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_EXCEPTION_VULKAN_GUARD
#define SAPPHIRE_RENDER_EXCEPTION_VULKAN_GUARD

#include <SA/Core/Debug/Exceptions/Exception.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	class Exception_Vulkan : public Exception
	{
	public:
		Exception_Vulkan(
			BaseInfos&& _infos,
			VkResult _vkRes,
			std::string&& _predStr,
			std::wstring&& _msg = L"",
			std::wstring&& _details = L""
		) noexcept;
	};


	#define __SA_CREATE_EXCEPTION_Vulkan(_baseInfos, _vkRes, ...) Sa::Exception_Vulkan(\
		_baseInfos,\
		_vkRes,\
		#_vkRes,\
		##__VA_ARGS__\
	)
}

#endif // GUARD

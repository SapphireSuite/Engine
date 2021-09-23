// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Debug/Exception_Vulkan.hpp>

#if SA_VULKAN

namespace Sa
{
	Exception_Vulkan::Exception_Vulkan(
		BaseInfos&& _infos,
		VkResult _vkRes,
		std::string&& _predStr,
		std::wstring&& _msg,
		std::wstring&& _details
	) noexcept :
		Exception(std::move(_infos),
			_vkRes == VkResult::VK_SUCCESS, std::move(_predStr) + " == VkResult::VK_SUCCESS",
			std::move(_msg),
			std::move(_details))
	{
	}
}

#endif

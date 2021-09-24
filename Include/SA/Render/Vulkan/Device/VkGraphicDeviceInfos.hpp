// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_GRAPHIC_DEVICE_INFOS_GUARD
#define SAPPHIRE_RENDER_VK_GRAPHIC_DEVICE_INFOS_GUARD

#include <SA/Render/Base/Device/AGraphicDeviceInfos.hpp>

#include <SA/Render/Vulkan/Device/VkQueueRequirements.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Surface;

	struct GraphicDeviceInfos : public AGraphicDeviceInfos
	{
		struct FamilyInfos
		{
			struct QueueInfos
			{
				uint32 familyIndex = 0;
				uint32 queueIndex = 0;
			};

			std::vector<QueueInfos> queueInfos;
		};

		FamilyInfos graphics;
		FamilyInfos compute;
		FamilyInfos transfer;
		FamilyInfos present;


		struct IndexInfos
		{
			uint32 index = ~uint32();
			uint32 num = 0u;
		};

		std::vector<IndexInfos> indexInfos;


		const VkPhysicalDevice device = VK_NULL_HANDLE;
		
		QueueRequirements reqs;


		GraphicDeviceInfos(VkPhysicalDevice _device, const QueueRequirements& _reqs) noexcept;

		void QueryQueueFamilies(const Surface* _surface) noexcept;
		void AddFamily(const Surface* _surface, const VkQueueFamilyProperties& _family, uint32 _famIndex) noexcept;

		bool QueueFamiliesCompleted() const noexcept;

		std::vector<VkDeviceQueueCreateInfo> GetDeviceCreateInfos() const noexcept;
	};
}

#endif

#endif // GUARD
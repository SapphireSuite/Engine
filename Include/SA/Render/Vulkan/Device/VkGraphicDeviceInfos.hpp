// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_GRAPHIC_DEVICE_INFOS_GUARD
#define SAPPHIRE_RENDER_VK_GRAPHIC_DEVICE_INFOS_GUARD

#include <SA/Render/Base/AGraphicDeviceInfos.hpp>

#include <SA/Render/Vulkan/Device/VkQueueType.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class RenderSurface;

	struct GraphicDeviceInfos : public AGraphicDeviceInfos
	{
		struct FamilyInfos
		{
			uint32 index = ~uint32();
			uint32 maxQueueNum = 1u;
			uint32 queueNum = 1u;

			bool IsCompleted() const noexcept;
		};

		const VkPhysicalDevice device = VK_NULL_HANDLE;
		const QueueType familyTypes;

		FamilyInfos graphics;
		FamilyInfos compute;
		FamilyInfos transfer;
		FamilyInfos present;

		static constexpr uint32 familyNum = 4;


		GraphicDeviceInfos(GraphicDeviceInfos&&) = default;
		GraphicDeviceInfos(const GraphicDeviceInfos&) = default;
		GraphicDeviceInfos(VkPhysicalDevice _device, QueueType _familyTypes) noexcept;

		const FamilyInfos* Families() const noexcept;

		void QueryQueueFamilies(const RenderSurface* _surface) noexcept;
		void AddFamily(const RenderSurface* _surface, const VkQueueFamilyProperties& _family, uint32 _index) noexcept;

		bool QueueFamiliesCompleted() const noexcept;

		std::vector<VkDeviceQueueCreateInfo> GetDeviceCreateInfos() const noexcept;
	};
}

#endif

#endif // GUARD

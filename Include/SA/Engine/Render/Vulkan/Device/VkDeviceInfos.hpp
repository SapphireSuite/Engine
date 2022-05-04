// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_DEVICE_INFOS_GUARD
#define SAPPHIRE_ENGINE_VK_DEVICE_INFOS_GUARD

#include <vector>

#include <SA/Support/API/Vulkan.hpp>

#include <SA/Engine/Render/Base/Device/ARenderDeviceInfos.hpp>
#include <SA/Engine/Render/Vulkan/Device/Queue/VkQueueRequirements.hpp>

namespace Sa::Vk
{
	class WindowSurface;

	class DeviceInfos : public ARenderDeviceInfos
	{
		QueueRequirements mReqs;

	public:
		VkPhysicalDevice device = VK_NULL_HANDLE;
		VkPhysicalDeviceProperties properties;


		DeviceInfos(VkPhysicalDevice _device, const QueueRequirements& _reqs);


		uint32_t GetID() const noexcept override final;
		std::string GetName() const noexcept override final;

//{ Queue Families

		struct FamilyInfos
		{
			struct QueueInfos
			{
				uint32_t familyIndex = 0;
				uint32_t queueIndex = 0;
			};

			std::vector<QueueInfos> queueInfos;
		};

		FamilyInfos graphics;
		FamilyInfos compute;
		FamilyInfos transfer;
		FamilyInfos present;


		struct IndexInfos
		{
			uint32_t index = ~uint32_t();
			uint32_t num = 0u;
			
			std::vector<float> queuePriorities;
		};

		std::vector<IndexInfos> indexInfos;


		void QueryQueueFamilies(const WindowSurface* _winSurface = nullptr) noexcept;
		void AddFamily(const WindowSurface* _winSurface, const VkQueueFamilyProperties& _family, uint32_t _famIndex) noexcept;

		bool QueueFamiliesCompleted() const noexcept;

//}


//{ Extensions

		std::vector<const char*> GetRequiredExtensions() const;
		bool CheckExtensionSupport() const noexcept;

//}


		std::vector<VkDeviceQueueCreateInfo> GetDeviceCreateInfos() const noexcept;
	};
}

#endif // GUARD

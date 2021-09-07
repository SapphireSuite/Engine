// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Surface/VkRenderSurface.hpp>

#include <Render/Debug.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	RenderSurface::RenderSurface(VkSurfaceKHR _handle) noexcept :
		mHandle{ _handle }
	{
	}


	Format RenderSurface::GetFormat() const
	{
		return mSwapChain.GetFormat();
	}


	void RenderSurface::Create(const Device& _device)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, mHandle,
			L"Handle is nullptr. VkSurfaceKHR must be created first: use VkRenderInstance.CreateRenderSurface()");

		mSwapChain.Create(_device, *this);


		SA_LOG(L"Render Surface created.", Infos, SA/Render/Vulkan);
	}
	
	void RenderSurface::Destroy(const Device& _device)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, mHandle,
			L"Handle is nullptr. VkSurfaceKHR must be created first: use VkRenderInstance.CreateRenderSurface()");

		mSwapChain.Destroy(_device);

		SA_LOG(L"Render Surface destroyed.", Infos, SA/Render/Vulkan);
	}


	RenderSurfaceSupportDetails RenderSurface::QuerySupportDetails(VkPhysicalDevice _device) const
	{
		RenderSurfaceSupportDetails details{};

		// KHR Capabilities.
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_device, mHandle, &details.capabilities);


		// KHR Formats.
		uint32 formatCount = 0u;
		vkGetPhysicalDeviceSurfaceFormatsKHR(_device, mHandle, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(_device, mHandle, &formatCount, details.formats.data());
		}


		// KHR Present Modes.
		uint32 presentModeCount = 0u;
		vkGetPhysicalDeviceSurfacePresentModesKHR(_device, mHandle, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(_device, mHandle, &presentModeCount, details.presentModes.data());
		}

		return details;
	}


	RenderSurface::operator VkSurfaceKHR() const noexcept
	{
		return mHandle;
	}
}

#endif

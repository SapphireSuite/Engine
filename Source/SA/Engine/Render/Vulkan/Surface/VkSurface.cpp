// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Surface/VkSurface.hpp>

#include <SA/Collections/Debug>

#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

namespace SA::VK
{
	Vec2ui Surface::GetExtent() const
	{
		return mSwapChain.GetExtent();
	}
	
	Format Surface::GetFormat() const
	{
		return mSwapChain.GetFormat();
	}


	void Surface::Create(const Device& _device, const WindowSurface& _winSurface)
	{
		ARenderSurface::Create();
		
		mHandle = _winSurface;

		mSwapChain.Create(_device, *this);

		SA_LOG(L"Render Surface [" << mHandle << L"] created.", Infos, SA/Engine/Render/Vulkan);
	}

	void Surface::Destroy(const Device& _device)
	{
		ARenderSurface::Destroy();

		mSwapChain.Destroy(_device);

		SA_LOG(L"Render Surface [" << mHandle << L"] destroyed.", Infos, SA/Engine/Render/Vulkan);

		mHandle = VK_NULL_HANDLE;
	}


	void Surface::CreateFrameBuffers(const Device& _device,
		const RenderPass& _renderPass,
		const RenderPassDescriptor& _renderPassDesc)
	{
		CheckCreated();

		mSwapChain.CreateFrameBuffers(_device, _renderPass, _renderPassDesc);

		SA_LOG(L"Render Surface FrameBuffers created.", Infos, SA/Engine/Render/Vulkan);
	}
	
	void Surface::DestroyFrameBuffers(const Device& _device)
	{
		CheckCreated();

		mSwapChain.DestroyFrameBuffers(_device);

		SA_LOG(L"Render Surface FrameBuffers destroyed.", Infos, SA/Engine/Render/Vulkan);
	}


	Frame& Surface::Begin(const Device& _device)
	{
		CheckCreated();

		return mSwapChain.Begin(_device);
	}

	void Surface::End(const Device& _device)
	{
		CheckCreated();

		return mSwapChain.End(_device);
	}


	SurfaceSupportDetails Surface::QuerySupportDetails(VkPhysicalDevice _device) const
	{
		SurfaceSupportDetails details{};

		// KHR Capabilities.
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_device, mHandle, &details.capabilities);


		// KHR Formats.
		uint32_t formatCount = 0u;
		vkGetPhysicalDeviceSurfaceFormatsKHR(_device, mHandle, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(_device, mHandle, &formatCount, details.formats.data());
		}


		// KHR Present Modes.
		uint32_t presentModeCount = 0u;
		vkGetPhysicalDeviceSurfacePresentModesKHR(_device, mHandle, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(_device, mHandle, &presentModeCount, details.presentModes.data());
		}

		return details;	
	}


	Surface::operator VkSurfaceKHR() const noexcept
	{
		return mHandle;
	}
}

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Surface/VkSurface.hpp>

#include <Render/Vulkan/VkInstance.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pass/VkRenderPass.hpp>
#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

#include <Render/Debug.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	Format Surface::GetFormat() const
	{
		return mSwapChain.GetFormat();
	}

	void Surface::Create(const Device& _device, const WindowSurface& _winSurface)
	{
		mHandle = _winSurface;

		mSwapChain.Create(_device, *this);

		SA_LOG(L"Render Surface created.", Infos, SA/Render/Vulkan);
	}
	
	void Surface::Destroy(const Device& _device)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, mHandle,
			L"Handle is nullptr. VkSurfaceKHR must be created first: use window.CreateVkSurface()");

		mSwapChain.Destroy(_device);
		mHandle = VK_NULL_HANDLE;
		
		SA_LOG(L"Render Surface destroyed.", Infos, SA/Render/Vulkan);
	}


	void Surface::CreateFrameBuffers(const Device& _device, const RenderPass& _renderPass, const RenderPassDescriptor& _renderPassDesc)
	{
		mSwapChain.CreateFrameBuffers(_device, _renderPass, _renderPassDesc);

		SA_LOG(L"Render Surface FrameBuffers created.", Infos, SA/Render/Vulkan);
	}

	void Surface::DestroyFrameBuffers(const Device& _device)
	{
		mSwapChain.DestroyFrameBuffers(_device);

		SA_LOG(L"Render Surface FrameBuffers destroyed.", Infos, SA/Render/Vulkan);
	}


	FrameBuffer& Surface::Begin(const Device& _device)
	{
		return mSwapChain.Begin(_device);
	}

	void Surface::End(const Device& _device, const std::vector<CommandBuffer>& _cmdBuffers)
	{
		mSwapChain.End(_device, _cmdBuffers);
	}


	SurfaceSupportDetails Surface::QuerySupportDetails(VkPhysicalDevice _device) const
	{
		SurfaceSupportDetails details{};

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


	Surface::operator VkSurfaceKHR() const noexcept
	{
		return mHandle;
	}
}

#endif

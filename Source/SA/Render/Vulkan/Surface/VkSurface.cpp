// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Surface/VkSurface.hpp>

#include <Render/Vulkan/VkInstance.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pass/VkRenderPass.hpp>

#include <Render/Debug.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	Surface::Surface(VkSurfaceKHR _handle) noexcept :
		mHandle{ _handle }
	{
	}


	Format Surface::GetFormat() const
	{
		return mSwapChain.GetFormat();
	}

	void Surface::Create(const ARenderDevice* _device)
	{
		const Device& vkDevice = _device->As<Device>();

		SA_ASSERT(Nullptr, SA/Render/Vulkan, mHandle,
			L"Handle is nullptr. VkSurfaceKHR must be created first: use window.CreateVkSurface()");

		mSwapChain.Create(vkDevice, *this);

		SA_LOG(L"Render Surface created.", Infos, SA/Render/Vulkan);
	}
	
	void Surface::Destroy(const ARenderDevice* _device)
	{
		const Device& vkDevice = _device->As<Device>();

		SA_ASSERT(Nullptr, SA/Render/Vulkan, mHandle,
			L"Handle is nullptr. VkSurfaceKHR must be created first: use window.CreateVkSurface()");

		mSwapChain.Destroy(vkDevice);
	}


	void Surface::CreateFrameBuffers(const ARenderDevice* _device, const ARenderPass* _renderPass, const RenderPassDescriptor& _renderPassDesc)
	{
		const Device& vkDevice = _device->As<Device>();
		const RenderPass& vkRenderPass = _renderPass->As<RenderPass>();

		mSwapChain.CreateFrameBuffers(vkDevice, vkRenderPass, _renderPassDesc);

		SA_LOG(L"Render Surface FrameBuffers created.", Infos, SA/Render/Vulkan);
	}

	void Surface::DestroyFrameBuffers(const ARenderDevice* _device)
	{
		const Device& vkDevice = _device->As<Device>();

		mSwapChain.DestroyFrameBuffers(vkDevice);

		SA_LOG(L"Render Surface FrameBuffers destroyed.", Infos, SA/Render/Vulkan);
	}


	FrameBuffer& Surface::Begin(const ARenderDevice& _device)
	{
		const Device& vkDevice = _device.As<Device>();

		return mSwapChain.Begin(vkDevice);
	}

	void Surface::End(const ARenderDevice& _device, const std::vector<CommandBuffer>& _cmdBuffers)
	{
		const Device& vkDevice = _device.As<Device>();

		mSwapChain.End(vkDevice, _cmdBuffers);
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

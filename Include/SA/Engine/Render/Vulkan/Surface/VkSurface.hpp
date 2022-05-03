// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_SURFACE_GUARD
#define SAPPHIRE_ENGINE_VK_SURFACE_GUARD

#include <SA/Engine/Render/Base/Surface/ARenderSurface.hpp>

#include <SA/Engine/Render/Vulkan/Surface/VkSwapChain.hpp>
#include <SA/Engine/Render/Vulkan/Surface/VkSurfaceSupportDetails.hpp>

namespace Sa::Vk
{
	class Device;
	class WindowSurface;

	class Surface : public ARenderSurface
	{
		VkSurfaceKHR mHandle = VK_NULL_HANDLE;

		SwapChain mSwapChain;

		using HardwareInterface::Create; // overloaded.
		using HardwareInterface::Destroy;// overloaded.

	public:
		Format GetFormat() const override final;

		void Create(const Device& _device, const WindowSurface& _winSurface);
		void Destroy(const Device& _device);

		SurfaceSupportDetails QuerySupportDetails(VkPhysicalDevice _device) const;


		operator VkSurfaceKHR() const noexcept;
	};
}

#endif // GUARD

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_CONTEXT_GUARD
#define SAPPHIRE_ENGINE_VK_CONTEXT_GUARD

#include <SA/Engine/Render/Base/Context/ARenderContext.hpp>

#include <SA/Engine/Render/Vulkan/Surface/VkSurface.hpp>
#include <SA/Engine/Render/Vulkan/Pass/VkRenderPass.hpp>

#include <SA/Engine/HI/InterfaceList.hpp>

namespace Sa::Vk
{
	class Device;

	class Context : public ARenderContext
	{
		Device* mDevice = nullptr;

		InterfaceList<Surface> mSurfaces;
		InterfaceList<RenderPass> mRenderPasses;

		using HardwareInterface::Create; // overloaded.

	public:
		void Create(Device& _device);
		void Destroy() override final;
		void Clear() override final;


		ARenderSurface* CreateSurface(AWindowSurface* _winSurface) override final;
		void DestroySurface(ARenderSurface* _surface) override final;

		ARenderPass* CreateRenderPass(const RenderPassDescriptor& _desc) override final;
		void DestroyRenderPass(ARenderPass* _pass) override final;
	};


	template <typename T>
	struct ContextObjDestroyer
	{
		Device& device;

		void operator()(T& _in)
		{
			_in.Destroy(device);
		}
	};
}


#endif // GUARD

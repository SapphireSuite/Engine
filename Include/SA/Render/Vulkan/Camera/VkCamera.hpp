// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_CAMERA_GUARD
#define SAPPHIRE_RENDER_VK_CAMERA_GUARD

#include <SA/Render/Base/Camera/ARenderCamera.hpp>

#include <SA/Render/Vulkan/Buffers/VkBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class Camera : public ARenderCamera
	{
		Buffer mCameraUBO;

		void UpdateUBO(const ARenderDevice* _device);

	public:
		void Create(const ARenderDevice* _device) override final;
		void Destroy(const ARenderDevice* _device) override final;

		void Update(const ARenderDevice* _device) override final;
	};
}

#endif

#endif // GUARD

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_CAMERA_GUARD
#define SAPPHIRE_RENDER_VK_CAMERA_GUARD

#include <SA/Render/Base/Camera/ACamera.hpp>

#include <SA/Render/Vulkan/Buffers/VkBuffer.hpp>

namespace Sa::Vk
{
	class Device;

	class Camera : public ACamera
	{
		//Buffer mCameraUBO;

		void UpdateUBO(const Device& _device);

	public:
		void Create(const Device& _device);
		void Destroy(const Device& _device);

		void Update(const Device& _device);
	};
}

#endif // GUARD

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Camera/VkCamera.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void Camera::Create(const ARenderDevice* _device)
	{
		//const Device& vkDevice = _device->As<Device>();

		mCameraUBO.Create(_device, RenderBufferType::Uniform, sizeof(RenderCameraUBO), &mUBOData);

		SA_LOG(L"Camera created", Infos, SA/Render/Vulkan);
	}

	void Camera::Destroy(const ARenderDevice* _device)
	{
		//const Device& vkDevice = _device->As<Device>();

		mCameraUBO.Destroy(_device);

		SA_LOG(L"Camera destroyed", Infos, SA/Render/Vulkan);
	}


	void Camera::Update(const ARenderDevice* _device)
	{
		//const Device& vkDevice = _device->As<Device>();

		UpdateUBO(_device);
	}


	void Camera::UpdateUBO(const ARenderDevice* _device)
	{
		if (bProjDirty)
		{
			if (bTransformDirty)
			{
				// Update whole buffer.
				mCameraUBO.UpdateData(_device, &mUBOData, sizeof(RenderCameraUBO));
			}
			else
			{
				// Update proj only.
				mCameraUBO.UpdateData(_device, &mUBOData.proj, sizeof(CMat4f));
			}
		}
		else if (bTransformDirty)
		{
			// Update transform only.
			mCameraUBO.UpdateData(_device, &mUBOData.viewInv, sizeof(CMat4f) + sizeof(Vec3f), sizeof(CMat4f));
		}
	}
}

#endif

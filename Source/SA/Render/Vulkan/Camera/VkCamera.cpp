// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Camera/VkCamera.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
	void Camera::Create(const Device& _device)
	{
		mCameraUBO.Create(_device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(CameraUBO), &mUBOData);
		
		SA_LOG(L"Camera created.", Infos, SA/Render/Vulkan);
	}

	void Camera::Destroy(const Device& _device)
	{
		mCameraUBO.Destroy(_device);
		
		SA_LOG(L"Camera destroyed.", Infos, SA/Render/Vulkan);
	}


	void Camera::Update(const Device& _device)
	{
		UpdateUBO(_device);
	}


	void Camera::UpdateUBO(const Device& _device)
	{
		if (bProjDirty)
		{
			if (bTransformDirty)
			{
				// Update whole buffer.
				mCameraUBO.UpdateData(_device, &mUBOData, sizeof(CameraUBO));
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

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkFrameBuffer.hpp>

#include <Render/Base/Misc/Color.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pass/VkRenderPass.hpp>

namespace SA::VK
{
	void FrameBuffer::AddClearColor(Format _format, const Color& _clearColor)
	{
		if (_format.IsDepthFormat())
			mClearValues.emplace_back(VkClearValue{ { { 1.f, 0u } } });
		else
			mClearValues.emplace_back(_clearColor);
	}


	const std::vector<VkClearValue>& FrameBuffer::GetClearValues() const
	{
		return mClearValues;
	}


	void FrameBuffer::Create(const Device& _device, const RenderPass& _renderPass,
		const RenderPassDescriptor& _rpDescriptor,
		const Vec2ui& _extent, VkImage presentImage)
	{
		std::vector<VkImageView> attachementCreateInfos;

		ImageBufferCreateInfos imageInfos;
		imageInfos.extent = _extent;

		for (auto subIt = _rpDescriptor.subPassDescs.begin(); subIt != _rpDescriptor.subPassDescs.end(); ++subIt)
		{
			for (auto attIt = subIt->attachmentDescs.begin(); attIt != subIt->attachmentDescs.end(); ++attIt)
			{
				imageInfos.format = attIt->format;
				imageInfos.usage = 0u; // Reset usage.
				imageInfos.sampling = subIt->sampling; // Reset sampling value.


				if (subIt->sampling != SampleBits::Sample1Bit && !attIt->format.IsDepthFormat())
				{
					// Add multisampled buffer.
					ImageBuffer& multSamplBuffer = mAttachments.emplace_back(ImageBuffer{});
					multSamplBuffer.Create(_device, imageInfos);
					attachementCreateInfos.push_back(multSamplBuffer);

					if (attIt->loadMode == AttachmentLoadMode::Clear)
						AddClearColor(attIt->format, attIt->clearColor);

					imageInfos.sampling = SampleBits::Sample1Bit;
				}


				if (attIt->format.IsPresentFormat())
				{
					SA_ASSERT(Default, SA/Engine/Render/Vulkan, presentImage != VK_NULL_HANDLE,
						L"Framebuffer with present format requiere a valid swapchain image!");

					ImageBuffer& presentBuffer = mAttachments.emplace_back(ImageBuffer{});
					presentBuffer.CreateFromImage(_device, imageInfos, presentImage);
					attachementCreateInfos.push_back(presentBuffer);
				}
				else if (attIt->bInputNext)
				{
					imageInfos.usage = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;

					ImageBuffer& inputBuffer = mInputAttachments.emplace_back(ImageBuffer{});
					inputBuffer.Create(_device, imageInfos);
					attachementCreateInfos.push_back(inputBuffer);
				}
				else
				{
					ImageBuffer& buffer = mAttachments.emplace_back(ImageBuffer{});
					buffer.Create(_device, imageInfos);
					attachementCreateInfos.push_back(buffer);
				}


				if (attIt->loadMode == AttachmentLoadMode::Clear)
					AddClearColor(attIt->format, attIt->clearColor);
			}
		}


		// === Create FrameBuffer ===
		VkFramebufferCreateInfo framebufferCreateInfo{};
		framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCreateInfo.pNext = nullptr;
		framebufferCreateInfo.flags = 0;
		framebufferCreateInfo.renderPass = _renderPass;
		framebufferCreateInfo.attachmentCount = (uint32_t)attachementCreateInfos.size();
		framebufferCreateInfo.pAttachments = attachementCreateInfos.data();
		framebufferCreateInfo.width = _extent.x;
		framebufferCreateInfo.height = _extent.y;
		framebufferCreateInfo.layers = 1;

		SA_VK_ASSERT(vkCreateFramebuffer(_device, &framebufferCreateInfo, nullptr, &mHandle),
			L"Failed to create framebuffer!");
	}

	void FrameBuffer::Destroy(const Device& _device)
	{
		vkDestroyFramebuffer(_device, mHandle, nullptr);

		// Destroy attachments.
		for (auto it = mAttachments.begin(); it != mAttachments.end(); ++it)
			it->Destroy(_device);

		mAttachments.clear();

		// Destroy input attachments.
		for (auto it = mInputAttachments.begin(); it != mInputAttachments.end(); ++it)
			it->Destroy(_device);

		mInputAttachments.clear();
	}


	FrameBuffer::operator VkFramebuffer() const
	{
		return mHandle;
	}
}

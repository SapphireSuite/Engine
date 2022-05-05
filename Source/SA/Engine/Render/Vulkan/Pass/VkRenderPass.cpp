// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pass/VkRenderPass.hpp>

#include <HI/Cast.hpp>

#include <Render/Vulkan/VkFrame.hpp>
#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
	namespace Intl
	{
		VkSubpassDescription CreateSubpassDesc()
		{
			VkSubpassDescription subpass{};

			subpass.flags = 0u;
			subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

			subpass.inputAttachmentCount = 0u;
			subpass.pInputAttachments = nullptr;

			subpass.colorAttachmentCount = 0u;
			subpass.pColorAttachments = nullptr;
			subpass.pResolveAttachments = nullptr;

			subpass.pDepthStencilAttachment = nullptr;

			subpass.preserveAttachmentCount = 0u;
			subpass.pPreserveAttachments = nullptr;

			return subpass;
		}

		VkSubpassDependency CreateSubpassDep(uint32_t _currIndex, uint32_t _subpassNum)
		{
			VkSubpassDependency subpassDependency{};

			// Default dependency.
			subpassDependency.srcSubpass = _currIndex - 1;
			subpassDependency.dstSubpass = _currIndex;

			subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

			subpassDependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

			subpassDependency.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

			// Specialization: first dependency.
			if (_currIndex == 0)
			{
				subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;

				subpassDependency.srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

				subpassDependency.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
			}

			// Specialization: last dependency.
			if (_currIndex == _subpassNum - 1)
			{
				subpassDependency.dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

				subpassDependency.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
			}

			return subpassDependency;
		}

		VkAttachmentDescription CreateAttachement(VkFormat _format, VkSampleCountFlagBits _sampling, VkAttachmentLoadOp _loadOp)
		{
			VkAttachmentDescription attachment{};
			attachment.flags = 0u;
			attachment.format = _format;
			attachment.samples = _sampling;
			attachment.loadOp = _loadOp;
			attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			attachment.stencilLoadOp = _loadOp;
			attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
			attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			attachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			return attachment;
		}
	}

	void RenderPass::Create(const Device& _device, const RenderPassDescriptor& _desc)
	{
		ARenderPass::Create();

		// === Subpasses ===
		uint32_t subpassNum = (uint32_t)_desc.subPassDescs.size();

		std::vector<VkSubpassDescription> subpassDescriptions;
		subpassDescriptions.reserve(subpassNum);

		std::vector<VkSubpassDependency> subpassDependencies;
		subpassDependencies.reserve(subpassNum);


		std::vector<VkAttachmentDescription> subpassAttachments;
		subpassAttachments.reserve(subpassNum * 10u);

		std::vector<std::vector<VkAttachmentReference>> subpassColorAttachmentRefs;
		subpassColorAttachmentRefs.resize(subpassNum);

		std::vector<std::vector<VkAttachmentReference>> subpassAttachmentResolveRefs;
		subpassAttachmentResolveRefs.resize(subpassNum);

		std::vector<std::vector<VkAttachmentReference>> subpassInputAttachmentRefs;
		subpassInputAttachmentRefs.resize(subpassNum);

		std::vector<VkAttachmentReference> subpassDepthAttachmentRefs;
		subpassDepthAttachmentRefs.reserve(subpassNum);


		for (uint32_t i = 0; i < _desc.subPassDescs.size(); ++i)
		{
			const SubPassDescriptor& subpassDesc = _desc.subPassDescs[i];
			const VkSampleCountFlagBits sampling = API_GetSampleCount(subpassDesc.sampling);

			// === Attachments ===
			std::vector<VkAttachmentReference>& colorAttachmentRefs = subpassColorAttachmentRefs[i];
			colorAttachmentRefs.reserve(subpassDesc.attachmentDescs.size());

			std::vector<VkAttachmentReference>& resolveAttachmentRefs = subpassAttachmentResolveRefs[i];
			resolveAttachmentRefs.reserve(subpassDesc.attachmentDescs.size());

			std::vector<VkAttachmentReference>& inputAttachmentRefs = subpassInputAttachmentRefs[i];
			inputAttachmentRefs.reserve(subpassDesc.attachmentDescs.size());

			VkAttachmentReference& depthAttachRef = subpassDepthAttachmentRefs.emplace_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED,
				VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL });


			for (auto attIt = subpassDesc.attachmentDescs.begin(); attIt != subpassDesc.attachmentDescs.end(); ++attIt)
			{
				const VkFormat format = API_GetFormat(attIt->format);
				const VkAttachmentLoadOp loadOp = API_GetAttachmentLoadOp(attIt->loadMode);

				VkAttachmentDescription& attachDesc = subpassAttachments.emplace_back(Intl::CreateAttachement(format, sampling, loadOp));

				if (IsDepthFormat(attIt->format))
				{
					attachDesc.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					depthAttachRef.attachment = subpassAttachments.size() - 1u;
				}
				else
				{
					colorAttachmentRefs.push_back(VkAttachmentReference{ (uint32_t)subpassAttachments.size() - 1u, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
					resolveAttachmentRefs.push_back(VkAttachmentReference{ VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });

					if (sampling != VK_SAMPLE_COUNT_1_BIT)
					{
						// Color attachment multisampling resolution.

						VkAttachmentDescription& resolveAttachDesc = subpassAttachments.emplace_back(Intl::CreateAttachement(format, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_DONT_CARE));

						if (IsPresentFormat(attIt->format))
							resolveAttachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

						resolveAttachmentRefs.back().attachment = (uint32_t)subpassAttachments.size() - 1u;
					}
					else if (IsPresentFormat(attIt->format))
						attachDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
				}

				if (attIt->bInputNext)
					inputAttachmentRefs.push_back({ (uint32_t)subpassAttachments.size() - 1u, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
			}


			// Subpass description.
			VkSubpassDescription& vkSubpassDesc = subpassDescriptions.emplace_back(Intl::CreateSubpassDesc());

			vkSubpassDesc.colorAttachmentCount = (uint32_t)colorAttachmentRefs.size();
			vkSubpassDesc.pColorAttachments = colorAttachmentRefs.data();
			vkSubpassDesc.pResolveAttachments = resolveAttachmentRefs.data();

			vkSubpassDesc.pDepthStencilAttachment = &depthAttachRef;

			if (i > 0u && subpassInputAttachmentRefs[i - 1].size() > 0u)
			{
				// Add input attachment from previous subpass.
				vkSubpassDesc.inputAttachmentCount = (uint32_t)subpassInputAttachmentRefs[i - 1].size();
				vkSubpassDesc.pInputAttachments = subpassInputAttachmentRefs[i - 1].data();
			}


			// Subpass dependency.
			/* VkSubpassDependency& subpassDep =*/ subpassDependencies.emplace_back(Intl::CreateSubpassDep(i, subpassNum));
		}


		// === RenderPass ===
		VkRenderPassCreateInfo renderPassCreateInfo{};
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCreateInfo.pNext = nullptr;
		renderPassCreateInfo.flags = VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM;
		renderPassCreateInfo.attachmentCount = (uint32_t)subpassAttachments.size();
		renderPassCreateInfo.pAttachments = subpassAttachments.data();
		renderPassCreateInfo.subpassCount = (uint32_t)subpassDescriptions.size();
		renderPassCreateInfo.pSubpasses = subpassDescriptions.data();
		renderPassCreateInfo.dependencyCount = (uint32_t)subpassDependencies.size();
		renderPassCreateInfo.pDependencies = subpassDependencies.data();

		SA_VK_ASSERT(vkCreateRenderPass(_device, &renderPassCreateInfo, nullptr, &mHandle), L"Failed to create render pass!");
		
		SA_LOG(L"RenderPass [" << mHandle << L"] created.", Infos, SA/Engine/Render/Vulkan);
	}
	
	void RenderPass::Destroy(const Device& _device)
	{
		ARenderPass::Destroy();

		vkDestroyRenderPass(_device, mHandle, nullptr);

		SA_LOG(L"RenderPass [" << mHandle << L"] destroyed.", Infos, SA/Render/Vulkan);

		mHandle = VK_NULL_HANDLE;
	}

	
	void RenderPass::Begin(ARenderFrame& _frame, const Rect2Dui& _rect)
	{
		Frame& vkFrame = CastRef<Frame>(_frame);

		const std::vector<VkClearValue>& clearValues = vkFrame.fBuff.GetClearValues();

		VkRenderPassBeginInfo renderPassBeginInfo{};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassBeginInfo.pNext = nullptr;
		renderPassBeginInfo.renderPass = mHandle;
		renderPassBeginInfo.framebuffer = vkFrame.fBuff;
		renderPassBeginInfo.renderArea = reinterpret_cast<const VkRect2D&>(_rect);
		renderPassBeginInfo.clearValueCount = (uint32_t)clearValues.size();
		renderPassBeginInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(vkFrame.cmd, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	}
	
	void RenderPass::NextSubpass(ARenderFrame& _frame)
	{
		Frame& vkFrame = CastRef<Frame>(_frame);

		vkCmdNextSubpass(vkFrame.cmd, VK_SUBPASS_CONTENTS_INLINE);
	}
	
	void RenderPass::End(ARenderFrame& _frame)
	{
		Frame& vkFrame = CastRef<Frame>(_frame);

		vkCmdEndRenderPass(vkFrame.cmd);
	}
	

	RenderPass::operator VkRenderPass() const noexcept
	{
		return mHandle;
	}
}

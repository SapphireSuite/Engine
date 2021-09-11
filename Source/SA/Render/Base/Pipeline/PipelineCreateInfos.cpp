// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/PipelineCreateInfos.hpp>

namespace Sa
{
	PipelineCreateInfos::PipelineCreateInfos(const ARenderPass& _renderPass, const RenderPassDescriptor& _renderPassDesc) noexcept :
		renderPass{ _renderPass },
		renderPassDesc{ _renderPassDesc }
	{
	}


	void PipelineCreateInfos::AddBinding(PipelineBindingInfos _bindingInfos)
	{
		// Try find binding.
		for (auto it = bindings.begin(); it != bindings.end(); ++it)
		{
			if (it->binding == _bindingInfos.binding)
			{
				SA_ASSERT(Default, SA/Render, it->type == _bindingInfos.type, L"Binding redifinition with different types!");

				// Add shader stage.
				it->stageFlags |= _bindingInfos.stageFlags;

				return;
			}
		}

		// Not found.
		bindings.push_back(_bindingInfos);
	}

	void PipelineCreateInfos::RemoveBinding(uint32 _binding)
	{
		for (auto it = bindings.begin(); it != bindings.end(); ++it)
		{
			if (it->binding == _binding)
			{
				bindings.erase(it);
				return;
			}
		}

		SA_LOG("Try to remove invalid binding!", Warning, SA/Render);
	}
}

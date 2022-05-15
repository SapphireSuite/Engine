// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Descriptors/RenderPipelineLayoutDescriptor.hpp>

#include <SA/Collections/Debug>

#include <Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

namespace SA
{
	void RenderPipelineLayoutDescriptor::AddShader(const ShaderDescriptor& _desc)
	{
		AddBindingSets(_desc);
		AddPushConstants(_desc);
	}


	void RenderPipelineLayoutDescriptor::AddBindingSets(const ShaderDescriptor& _desc)
	{
		if (bindSetDescs.size() < _desc.bindingSet.size())
			bindSetDescs.resize(_desc.bindingSet.size());

		for (uint32_t i = 0u; i < _desc.bindingSet.size(); ++i)
		{
			for (auto& shBind : _desc.bindingSet[i].bindings)
			{
				PipelineBindingDescriptor* pipBindDesc = nullptr;

				// Search existing binding.
				for (auto& pipBindDescIt : bindSetDescs[i].bindings)
				{
					if (pipBindDescIt.binding == shBind.binding)
					{
						pipBindDesc = &pipBindDescIt;
						break;
					}
				}

				// Not found: emplace new binding.
				if (!pipBindDesc)
					pipBindDesc = &bindSetDescs[i].bindings.emplace_back(shBind);

				pipBindDesc->stageFlags |= _desc.stage;
			}
		}
	}
	
	void RenderPipelineLayoutDescriptor::AddPushConstants(const ShaderDescriptor& _desc)
	{
		for (auto& pushCst : _desc.pushConstants)
		{
			PipelinePushConstantDescriptor* pipPushCst = nullptr;

			// Search existing push constant.
			for (auto& pipPushCstIt : pushConstDescs)
			{
				if (pipPushCstIt.offset == pushCst.offset)
				{
					SA_ASSERT(Default, SA/Render, pipPushCstIt.size == pushCst.size,
						L"Add push constant at same offset ["_L << pipPushCstIt.offset <<
						L"] with different size: [" << pipPushCstIt << L"] and [" << pushCst.size << L"]!");

					pipPushCst = &pipPushCstIt;
					break;
				}
			}

			// Not found: emplace new push constant.
			if(!pipPushCst)
				pipPushCst = &pushConstDescs.emplace_back(pushCst);

			pipPushCst->stageFlags |= _desc.stage;
		}
	}
}


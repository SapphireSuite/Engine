// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Descriptors/RenderPipelineLayoutDescriptor.hpp>

#include <SA/Collections/Debug>

#include <Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

namespace SA
{
	void RenderPipelineLayoutDescriptor::AddShader(const ShaderDescriptor& _desc)
	{
		AddBindingSets(_desc.bindingSet);
		AddPushConstants(_desc.pushConstants);
	}


	void RenderPipelineLayoutDescriptor::AddBindingSets(const std::vector<ShaderBindingSetDescriptor>& _shBindSetDescs)
	{
		if (bindingSets.size() < _shBindSetDescs.size())
			bindingSets.resize(_shBindSetDescs.size());

		for (uint32_t i = 0u; i < _shBindSetDescs.size(); ++i)
		{
			for (auto& shBind : _shBindSetDescs[i].bindings)
			{
				PipelineBindingDescriptor* pipBindDesc = nullptr;

				// Search existing binding.
				for (auto& pipBindDescIt : bindingSets[i].bindings)
				{
					if (pipBindDescIt.binding == shBind.binding)
					{
						pipBindDesc = &pipBindDescIt;
						break;
					}
				}

				// Not found: emplace new binding.
				if (!pipBindDesc)
					pipBindDesc = &bindingSets[i].bindings.emplace_back(shBind);

				pipBindDesc->stageFlags |= _desc.stage;
			}
		}
	}
	
	void RenderPipelineLayoutDescriptor::AddPushConstants(const std::vector<ShaderPushConstantDescriptor>& _shPushCstDescs)
	{
		for (auto& pushCst : _shPushCstDescs)
		{
			PipelinePushConstantDescriptor* pipPushCst = nullptr;

			// Search existing push constant.
			for (auto& pipPushCstIt : pushConstants)
			{
				if (pipPushCstIt.offset == pushCst.offset)
				{
					SA_ASSERT(Default, SA/Render, pipPushCstIt.size == pushCst.size,
						(std::wstring(L"Add push constant at same offset [") << pipPushCstIt.offset <<
						L"] with different size: [" << pipPushCstIt << L"] and [" << pushCst.size << L"]!"));

					pipPushCst = &pipPushCstIt;
					break;
				}
			}

			// Not found: emplace new push constant.
			if(!pipPushCst)
				pipPushCst = &pushConstants.emplace_back(pushCst);

			pipPushCst->stageFlags |= _desc.stage;
		}
	}
}


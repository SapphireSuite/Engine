// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/Base/Pipeline/PipelineShaderInfos.hpp>

#include <Collections/Debug>

namespace Sa
{
	void PipelineShaderInfos::AddShader(const AShader* _shader, const ShaderDescriptor& _desc)
	{
		if (_desc.stage == ShaderStage::Vertex)
			vertexBindingLayout.desiredLayout = VertexLayout::Make(static_cast<VertexComp>((uint8)_desc.vertexLayout)); // TODO: Clean.

		PipelineShaderStage& stage = stages.emplace_back();
		stage.shader = _shader;
		stage.stage = _desc.stage;


		// Bindings
		{
			if (bindingSets.size() < _desc.bindingSet.size())
				bindingSets.resize(_desc.bindingSet.size());

			for (uint32 i = 0u; i < _desc.bindingSet.size(); ++i)
			{
				for (auto& shBind : _desc.bindingSet[i].bindings)
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


		// Spec constants.
		{
			for (auto& specCst : _desc.specConstants)
				specConstants.emplace(specCst);
		}


		// Push constants.
		{
			for (auto& pushCst : _desc.pushConstants)
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
}

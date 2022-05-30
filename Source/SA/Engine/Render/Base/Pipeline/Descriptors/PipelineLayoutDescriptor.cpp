// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Descriptors/PipelineLayoutDescriptor.hpp>

#include <SA/Collections/Debug>

#include <Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

namespace SA
{
	bool PipelineLayoutDescriptor::Empty() const noexcept
	{
		return bindSetDescs.empty() && pushConstDescs.empty();
	}

	void PipelineLayoutDescriptor::Clear()
	{
		bindSetDescs.clear();
		pushConstDescs.clear();
	}


	void PipelineLayoutDescriptor::AddShader(const ShaderDescriptor& _desc)
	{
		AddBindingSets(_desc);
		AddPushConstants(_desc);
	}


	void PipelineLayoutDescriptor::AddBindingSets(const ShaderDescriptor& _desc)
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
	
	void PipelineLayoutDescriptor::AddPushConstants(const ShaderDescriptor& _desc)
	{
		if(_desc.pushConstants.empty())
			return;

		PipelinePushConstantDescriptor& pipPushCst = pushConstDescs.emplace_back();

		pipPushCst.stage = _desc.stage;

		for (auto& pushCst : _desc.pushConstants)
		{
			pipPushCst.offset = std::min(pipPushCst.offset, pushCst.offset);
			pipPushCst.size += pushCst.size;
		}
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const PipelineLayoutDescriptor& _desc, std::string& _dst)
		{
			ToBinary(_desc.bindSetDescs, _dst);
			ToBinary(_desc.pushConstDescs, _dst);

			return true;
		}

		template <>
		bool FromBinary(PipelineLayoutDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			FromBinary(_desc.bindSetDescs, _src, _offset);
			FromBinary(_desc.pushConstDescs, _src, _offset);
			
			return true;
		}
	}
}


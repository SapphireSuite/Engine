// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

namespace SA
{
	ShaderBindingDescriptor& ShaderDescriptor::EmplaceBinding(uint32_t _set)
	{
		while (_set >= bindingSet.size())
			bindingSet.emplace_back();

		return bindingSet[_set].bindings.emplace_back();
	}

	void ShaderDescriptor::Clear()
	{
		stage = ShaderStage::Unknown;

		vertexLayout.Clear();

		bindingSet.clear();
		pushConstants.clear();
		specConstants.clear();
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderDescriptor& _desc, std::string& _dst)
		{
			ToBinary(_desc.stage, _dst);
			ToBinary(_desc.vertexLayout, _dst);

			ToBinary(_desc.bindingSet, _dst);
			ToBinary(_desc.pushConstants, _dst);
			ToBinary(_desc.specConstants, _dst);

			return true;
		}

		template <>
		bool FromBinary(ShaderDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			FromBinary(_desc.stage, _src, _offset);
			FromBinary(_desc.vertexLayout, _src, _offset);

			FromBinary(_desc.bindingSet, _src, _offset);
			FromBinary(_desc.pushConstants, _src, _offset);
			FromBinary(_desc.specConstants, _src, _offset);

			return true;
		}
	}
}

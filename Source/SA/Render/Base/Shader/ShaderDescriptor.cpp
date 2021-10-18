// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/ShaderDescriptor.hpp>

#include <Core/Serialize/Serializer.hpp>

#include <Render/Base/Shader/SpecConstants/DefaultSpecConstant.hpp>

namespace Sa
{
	ShaderBindingDescriptor& ShaderDescriptor::EmplaceBinding(uint32 _set)
	{
		while (_set >= bindingSet.size())
			bindingSet.emplace_back();

		return bindingSet[_set].bindings.emplace_back();
	}

	void ShaderDescriptor::Clear()
	{
		stage = ShaderStage::Unknown;

		vertexLayout = 0u;

		bindingSet.clear();
		specConstants.clear();
	}


	namespace Serialize
	{
		void ToBinary(const ShaderDescriptor& _obj, std::string& _str)
		{
			ToBinary(_obj.stage, _str);

			if (_obj.stage == ShaderStage::Vertex)
				ToBinary(_obj.vertexLayout, _str);

			ToBinary(_obj.bindingSet, _str);
			ToBinary(_obj.specConstants, _str);
		}

		void FromBinary(ShaderDescriptor& _obj, Reader& _read)
		{
			FromBinary(_obj.stage, _read);

			if (_obj.stage == ShaderStage::Vertex)
				FromBinary(_obj.vertexLayout, _read);

			FromBinary(_obj.bindingSet, _read);
			FromBinary(_obj.specConstants, _read);
		}
	}
}

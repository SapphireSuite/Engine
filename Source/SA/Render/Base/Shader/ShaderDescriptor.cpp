// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/ShaderDescriptor.hpp>

#include <Core/Serialize/Serializer.hpp>

#include <Render/Base/Shader/SpecConstants/DefaultSpecConstant.hpp>

namespace Sa
{
	SpecConstantDescriptor& ShaderDescriptor::EmplaceSpecConstants(uint32 _id)
	{
		SpecConstantDescriptor& specDesc =
			_id >= SpecConstantID::Min ?
			engineSpecConstants.emplace_back() :
			userSpecConstants.emplace_back();

		specDesc.id = _id;

		return specDesc;
	}


	void ShaderDescriptor::Clear()
	{
		stage = ShaderStage::Unknown;

		vertexLayout = 0u;

		userBindingSet.bindings.clear();
		engineBindingSets.clear();

		userSpecConstants.clear();
		engineSpecConstants.clear();
	}


	namespace Serialize
	{
		void ToBinary(const ShaderDescriptor& _obj, std::string& _str)
		{
			ToBinary(_obj.stage, _str);

			if (_obj.stage == ShaderStage::Vertex)
				ToBinary(_obj.vertexLayout, _str);

			ToBinary(_obj.userBindingSet, _str);
			ToBinary(_obj.engineBindingSets, _str);

			ToBinary(_obj.userSpecConstants, _str);
			ToBinary(_obj.engineSpecConstants, _str);
		}

		void FromBinary(ShaderDescriptor& _obj, Reader& _read)
		{
			FromBinary(_obj.stage, _read);

			if (_obj.stage == ShaderStage::Vertex)
				FromBinary(_obj.vertexLayout, _read);

			FromBinary(_obj.userBindingSet, _read);
			FromBinary(_obj.engineBindingSets, _read);

			FromBinary(_obj.userSpecConstants, _read);
			FromBinary(_obj.engineSpecConstants, _read);
		}
	}
}

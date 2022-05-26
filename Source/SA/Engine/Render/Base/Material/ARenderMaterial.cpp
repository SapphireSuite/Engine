// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/ARenderMaterial.hpp>

#include <SA/Collections/Debug>

#include <Render/Base/Pipeline/Descriptors/RenderPipelineLayoutDescriptor.hpp>

namespace SA
{
	void ARenderMaterial::Create(const RenderPipelineLayoutDescriptor& _pipLayoutDesc)
	{
		HardwareInterface::Create();

		// Create map.
		for(uint32_t i = 0; i < _pipLayoutDesc.bindSetDescs.size(); ++i)
		{
			auto& bindSet = _pipLayoutDesc.bindSetDescs[i];
	
			for(auto& bind : bindSet.bindings)
				mNameToBindingMap[bind.name] = BindMapInfos{ bind.binding, i };
		}
	}


	bool ARenderMaterial::GetStaticBindFromNamed(const MaterialNamedBindingInfos& _named, MaterialStaticBindingInfos& _static) const
	{
		auto bindInfos = mNameToBindingMap.find(_named.name);

		if(bindInfos == mNameToBindingMap.end())
		{
			SA_LOG(L"Binding [" << _named.name << L"] not found in material.", Error, SA/Engine/Render/Vulkan);
			return false;
		}
	
		_static.binding = bindInfos->second.binding;
		_static.set = bindInfos->second.set;
		_static.offset = _named.offset;

		return true;
	}
}

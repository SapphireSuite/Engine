// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T>
	void PipelineShaderInfos::SetSpecConstant(uint32 _id, const T& _value)
	{
		PipelineSpecConstant* specCst = nullptr;

		for (auto& specCstIt : specConstants)
		{
			if (specCstIt.id == _id)
			{
				specCst = &specCstIt;
				break;
			}
		}

		// Not found: emplace unnamed spec constant.
		if (!specCst)
			specCst = &(*specConstants.emplace(ShaderSpecConstantDescriptor{ "", _id }).first);

		specCst->value = std::make_unique<SpecConstant<T>>(_value);
	}

	template <typename T>
	void PipelineShaderInfos::SetSpecConstant(const std::string& _name, const T& _value)
	{
		for (auto& specCst : specConstants)
		{
			if (specCst.name == _name)
			{
				specCst.value = std::make_unique<SpecConstant<T>>(_value);
				return;
			}
		}

		// Can't emplace new spec constant: ID required.
	}
}

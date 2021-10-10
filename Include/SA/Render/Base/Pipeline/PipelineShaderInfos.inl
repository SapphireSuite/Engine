// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T>
	void PipelineShaderInfos::SetSpecConstant(uint32 _id, const T& _value)
	{
		for (auto& specCst : userSpecConstants)
		{
			if (specCst.id == _id)
			{
				specCst.value = std::make_unique<SpecConstant<T>>(_value);
				return;
			}
		}
	}

	template <typename T>
	void PipelineShaderInfos::SetSpecConstant(const std::string& _name, const T& _value)
	{
		for (auto& specCst : userSpecConstants)
		{
			if (specCst.name == _name)
			{
				specCst.value = std::make_unique<SpecConstant<T>>(_value);
				return;
			}
		}
	}
}

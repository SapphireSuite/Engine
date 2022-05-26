// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/Bindings/MaterialBindingData.hpp>

namespace SA
{
	MaterialBindingData::~MaterialBindingData()
	{
		Clear();
	}


	bool MaterialBindingData::Empty() const noexcept
	{
		return staticBindings.empty() && namedBindings.empty();
	}

	void MaterialBindingData::Clear()
	{
		// Static.
		for(auto& pair : staticBindings)
			delete pair.second;

		staticBindings.clear();


		// Named.
		for(auto& pair : namedBindings)
			delete pair.second;

		namedBindings.clear();
	}
}

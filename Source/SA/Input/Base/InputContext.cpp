// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/InputContext.hpp>

namespace Sa
{
	bool InputContext::Process(const InputRawKey& _inRawKey)
	{
		if (!bEnabled)
			return false;

		return key.Process(_inRawKey);
	}
	
	bool InputContext::Process(const InputAxis& _inAxis)
	{
		if (!bEnabled)
			return false;
		
		return axis.Process(_inAxis);
	}
}

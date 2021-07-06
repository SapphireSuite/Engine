// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Types/InputComposite.hpp>

namespace Sa
{
	InputComposite::~InputComposite()
	{
		for (auto it = mComps.begin(); it != mComps.end(); ++it)
			delete* it;

		mComps.clear();
	}
}

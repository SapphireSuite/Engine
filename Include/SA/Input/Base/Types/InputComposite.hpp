// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_COMPOSITE_GUARD
#define SAPPHIRE_INPUT_INPUT_COMPOSITE_GUARD

#include <vector>

#include <SA/Input/Base/Types/InputBase.hpp>

namespace Sa
{
	class InputComposite : public InputBase
	{
		std::vector<InputBase*> mComps;

	public:
		~InputComposite();
	};
}

#endif // GUARD

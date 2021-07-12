// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Axis/InputAxisBind.hpp>

namespace Sa
{
	InputAxisBind::InputAxisBind(Axis _axis) noexcept :
		axis{ _axis }
	{
	}

	InputAxisBind::InputAxisBind(const InputAxis& _inAxis) noexcept :
		axis{ _inAxis.axis }
	{
	}
}

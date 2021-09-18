// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_AMATERIAL_GUARD
#define SAPPHIRE_RENDER_AMATERIAL_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Base/Material/MaterialCreateInfos.hpp>

namespace Sa
{
	class ARenderFrame;

	class AMaterial : public Abstract
	{
	public:
		virtual void Bind(const ARenderFrame& _frame, const APipeline& _pipeline) const = 0;
	};
}

#endif // GUARD

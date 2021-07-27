// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_SYSTEM_GUARD
#define SAPPHIRE_RENDER_ARENDER_SYSTEM_GUARD

#include <SA/Core/Types/Abstract.hpp>

namespace Sa
{
	class AWindowSystem;

	class ARenderSystem : public Abstract
	{
	public:
		virtual void Create(const AWindowSystem& _winSys) = 0;
		virtual void Destroy() = 0;
	};
}

#endif // GUARD

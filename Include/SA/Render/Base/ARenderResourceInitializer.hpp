// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_RESOURCE_INITIALIZER_GUARD
#define SAPPHIRE_RENDER_ARENDER_RESOURCE_INITIALIZER_GUARD

#include <SA/Core/Types/Abstract.hpp>

namespace Sa
{
	class ARenderDevice;

	class ARenderResourceInitializer : public Abstract
	{
	public:
		virtual void Create(const ARenderDevice* _device) = 0;
		virtual void Destroy() = 0;

		virtual void Submit() = 0;
	};
}

#endif // GUARD

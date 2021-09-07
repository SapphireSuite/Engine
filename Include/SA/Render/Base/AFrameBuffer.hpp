// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_AFRAME_BUFFER_GUARD
#define SAPPHIRE_RENDER_AFRAME_BUFFER_GUARD

#include <SA/Core/Types/Abstract.hpp>

namespace Sa
{
	class AFrameBuffer : public Abstract
	{
	public:
		virtual void Begin() = 0;
		virtual void NextSubpass() = 0;
		virtual void End() = 0;
	};
}

#endif // GUARD

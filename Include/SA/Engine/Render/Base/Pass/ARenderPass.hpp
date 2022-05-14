// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_PASS_GUARD
#define SAPPHIRE_ENGINE_ARENDER_PASS_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Maths/Geometry/Rectangle2D.hpp>

#include <SA/Engine/Render/Base/Pass/RenderPassDescriptor.hpp>

namespace SA
{
	struct ARenderFrame;

	class ARenderPass : protected HardwareInterface
	{
		using HardwareInterface::Clear; // not used.

	public:
		virtual void Begin(ARenderFrame& _frame, const Rect2Dui& _rect) = 0;
		virtual void NextSubpass(ARenderFrame& _frame) = 0;
		virtual void End(ARenderFrame& _frame) = 0;
	};
}

#endif // GUARD

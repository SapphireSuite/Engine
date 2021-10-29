// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_PASS_GUARD
#define SAPPHIRE_RENDER_ARENDER_PASS_GUARD

#include <SA/Core/Types/Variadics/SparseVector.hpp>

#include <SA/Render/Base/Pass/RenderPassDescriptor.hpp>

namespace Sa
{
	class ARenderPass
	{
	public:
	};

	using RenderPassHandle = SparseVectorHandle<ARenderPass>;
}

#endif // GUARD

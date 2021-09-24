// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_PASS_GUARD
#define SAPPHIRE_RENDER_ARENDER_PASS_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Base/Pass/RenderPassDescriptor.hpp>

namespace Sa
{
	class ARenderDevice;

	class ARenderPass : public Abstract
	{
	public:
		virtual void Create(const ARenderDevice& _device, const RenderPassDescriptor& _desc) = 0;
		virtual void Destroy(const ARenderDevice& _device) = 0;
	};
}

#endif // GUARD

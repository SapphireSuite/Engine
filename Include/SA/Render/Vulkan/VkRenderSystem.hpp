// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_VK_RENDER_SYSTEM_GUARD
#define SAPPHIRE_VK_RENDER_SYSTEM_GUARD

#include <SA/Render/Base/ARenderSystem.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class RenderSystem : public ARenderSystem
	{
	public:
		void Create() override final;
		void Destroy() override final;
	};
}

#endif

#endif // GUARD

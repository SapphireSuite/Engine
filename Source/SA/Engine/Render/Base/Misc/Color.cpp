// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Misc/Color.hpp>

namespace SA
{
	const Color Color::red = Color{ 1.0f, 0.0f, 0.0f, 1.0f };
	const Color Color::green = Color{ 0.0f, 1.0f, 0.0f, 1.0f };
	const Color Color::blue = Color{ 0.0f, 0.0f, 1.0f, 1.0f };
	const Color Color::black = Color{ 0.0f, 0.0f, 0.0f, 1.0f };
	const Color Color::white = Color{ 1.0f, 1.0f, 1.0f, 1.0f };

#if SA_VULKAN

	Color::operator VkClearValue() const noexcept
	{
		return VkClearValue{ VkClearColorValue{ { r, g, b, a } } };
	}

	Color::operator VkClearColorValue() const noexcept
	{
		return VkClearColorValue{ { r, g, b, a} };
	}

#endif
}

// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SAMPLE_BITS_GUARD
#define SAPPHIRE_ENGINE_SAMPLE_BITS_GUARD

#include <cstdint>

#include <SA/Support/API/Vulkan.hpp>

namespace SA
{
	enum class SampleBits : uint8_t
	{
		/// no multisampling.
		Sample1Bit = 1 << 0,

		/// 2 bits multisampling.
		Sample2Bits = 1 << 1,

		/// 4 bits multisampling.
		Sample4Bits = 1 << 2,

		/// 8 bits multisampling.
		Sample8Bits = 1 << 3,

		/// 16 bits multisampling.
		Sample16Bits = 1 << 4,

		/// 32 bits multisampling.
		Sample32Bits = 1 << 5,

		/// 64 bits multisampling.
		Sample64Bits = 1 << 6,


		/// Use maximum multisampling allowed by hardware.
		Max,

		Default = Sample8Bits,
	};

#if SA_VULKAN

	namespace VK
	{
		VkSampleCountFlagBits API_GetSampleCount(SampleBits _sampleBits);
	}

#endif
}

#endif // GUARD

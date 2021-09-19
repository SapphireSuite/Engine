// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SPEC_CONSTANT_INFOS_GUARD
#define SAPPHIRE_RENDER_SPEC_CONSTANT_INFOS_GUARD

#include <vector>

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	class SpecConstantInfos
	{
	public:
		struct Descriptor
		{
			uint32 id = 0u;
			uint32 size = 0u;
		};

		std::vector<char> data;
		std::vector<Descriptor> descs;

		template <typename T>
		void Add(uint32 _id, T _specConst);

		bool Empty() const { return descs.empty(); }
	};
}

#include <SA/Render/Base/Shader/SpecConstantInfos.inl>

#endif // GUARD

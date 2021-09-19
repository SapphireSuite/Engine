// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SPEC_CONSTANT_INFOS_GUARD
#define SAPPHIRE_RENDER_SPEC_CONSTANT_INFOS_GUARD

#include <vector>

#include <SA/Render/Base/Shader/SpecConstants/SpecConstant.hpp>
#include <SA/Render/Base/Shader/SpecConstants/DefaultSpecConstant.hpp>

namespace Sa
{
	class SpecConstantInfos
	{
	public:
		std::vector<Intl::SpecConstantBase*> specConsts;

		~SpecConstantInfos();

		template <typename T>
		void Add(uint32 _id, T _specConst);
	};
}

#include <SA/Render/Base/Shader/SpecConstants/SpecConstantInfos.inl>

#endif // GUARD

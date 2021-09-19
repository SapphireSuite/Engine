// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SPEC_CONSTANT_GUARD
#define SAPPHIRE_RENDER_SPEC_CONSTANT_GUARD

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	namespace Intl
	{
		class SpecConstantBase
		{
		public:
			const uint32 id = 0u;
			const uint32 size = 0u;

			SpecConstantBase(uint32 _id, uint32 _size) noexcept;
			virtual ~SpecConstantBase() = default;

			virtual const void* Data() const = 0;
		};
	}


	template <typename T>
	class SpecConstant : public Intl::SpecConstantBase
	{
	public:
		T data = T();


		SpecConstant(uint32 _id, T _data) noexcept;

		const void* Data() const override final;
	};
}

#include <SA/Render/Base/Shader/SpecConstants/SpecConstant.inl>

#endif // GUARD

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SPEC_CONSTANT_GUARD
#define SAPPHIRE_RENDER_SPEC_CONSTANT_GUARD

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	class SpecConstantBase
	{
	protected:
		SpecConstantBase(uint32 _size) noexcept;

	public:
		const uint32 size = 0u;


		virtual ~SpecConstantBase() = default;


		virtual const void* Data() const = 0;
	};


	template <typename T>
	class SpecConstant : public SpecConstantBase
	{
	public:
		T data = T();


		SpecConstant(T _data) noexcept;


		const void* Data() const override final;
	};
}

#include <SA/Render/Base/Pipeline/SpecConstant/SpecConstant.inl>

#endif // GUARD

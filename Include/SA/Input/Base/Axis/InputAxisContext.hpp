// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_AXIS_CONTEXT_GUARD
#define SAPPHIRE_INPUT_INPUT_AXIS_CONTEXT_GUARD

#include <memory>
#include <unordered_map>

#include <SA/Core/Debug.hpp>

#include <SA/Input/Base/Axis/InputAxisBind.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisBinding.hpp>

namespace Sa
{
	class InputAxisContext
	{
		std::unordered_map<Axis, std::vector<std::shared_ptr<InputAxisBinding>>> mMap;

	public:
		template <typename InBindT, typename... Args>
		std::shared_ptr<InputAxisBinding> Bind(const InputAxisBind& _inAxisBind, Args&&... _args);

		void UnBind(Axis _axis);
		void UnBind(std::shared_ptr<InputAxisBinding> _inBinding);

		bool Process(const InputAxis& _inAxis);
	};
}

#include <SA/Input/Base/Axis/InputAxisContext.inl>

#endif // GUARD

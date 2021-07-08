// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_AXIS_CONTEXT_GUARD
#define SAPPHIRE_INPUT_INPUT_AXIS_CONTEXT_GUARD

#include <memory>
#include <unordered_map>

#include <SA/Collections/Debug>

#include <SA/Input/Base/Axis/InputAxis.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisBinding.hpp>

namespace Sa
{
	class InputAxisContext
	{
		std::unordered_map<Axis, std::vector<std::shared_ptr<InputAxisBinding>>> mMap;

	public:
		template <typename InBindT, typename... Args>
		std::shared_ptr<InputAxisBinding> Bind(const Axis& _axis, Args&&... _args);

		void UnBind(Axis _axis);
		void UnBind(std::shared_ptr<InputAxisBinding> _inBinding);

		bool Process(const InputAxis& _inAxis);
	};
}

#include <SA/Input/Base/Axis/InputAxisContext.inl>

#endif // GUARD

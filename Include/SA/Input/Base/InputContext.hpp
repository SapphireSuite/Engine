// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_CONTEXT_GUARD
#define SAPPHIRE_INPUT_INPUT_CONTEXT_GUARD

#include <unordered_map>

#include <SA/Config.hpp>

#include <SA/Input/Base/Types/InputKey.hpp>
#include <SA/Input/Base/Types/InputAxis.hpp>

#include <SA/Input/Base/Bindings/InputAction.hpp>
#include <SA/Input/Base/Bindings/InputRange.hpp>

namespace Sa
{
	class InputContext
	{
		std::unordered_map<InputKey, InputKeyBinding*> mKeyMap;
		std::unordered_map<Axis, InputAxisBinding*> mAxisMap;

	public:
		enum class ProcessMode
		{
			Consume = 1,
			Forward,
		};

		ProcessMode mode = ProcessMode::Consume;

		bool bEnabled = true;


		~InputContext();


		template <typename InBindT>
		void Bind(const InputKey& _inKey, InBindT _binding);

		template <typename InBindT>
		void Bind(Axis _axis, InBindT _binding);


		void UnBind(const InputKey& _inKey);

		void UnBind(Axis _axis);


		bool Process(const InputKey& _inKey);
		
		bool Process(const InputAxis& _inAxis);
	};
}

#include <SA/Input/Base/InputContext.inl>

#endif // GUARD

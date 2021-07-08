// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_CONTEXT_GUARD
#define SAPPHIRE_INPUT_INPUT_CONTEXT_GUARD

#include <SA/Config.hpp>

#include <SA/Input/Base/Types/InputAxis.hpp>

#include <SA/Input/Base/Contexts/InputKeyContext.hpp>

namespace Sa
{
	class InputContext
	{
		std::unordered_map<Axis, InputAxisBinding*> mAxisMap;

	public:
		enum class ProcessMode
		{
			Consume = 1,
			Forward,
		};

		ProcessMode mode = ProcessMode::Consume;

		bool bEnabled = true;

		InputKeyContext key;


		~InputContext();

		template <typename InBindT>
		void Bind(Axis _axis, InBindT _binding);


		void UnBind(Axis _axis);


		bool Process(const InputRawKey& _inKey);
		
		bool Process(const InputAxis& _inAxis);
	};
}

#include <SA/Input/Base/Contexts/InputContext.inl>

#endif // GUARD

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_CONTEXT_GUARD
#define SAPPHIRE_INPUT_INPUT_CONTEXT_GUARD

#include <unordered_map>

#include <SA/Config.hpp>

#include <SA/Input/Base/Types/InputKey.hpp>
#include <SA/Input/Base/Types/InputAxis.hpp>
#include <SA/Input/Base/Types/InputComposite.hpp>

#include <SA/Input/Base/Bindings/InputAction.hpp>
#include <SA/Input/Base/Bindings/InputRange.hpp>

namespace Sa
{
	class InputContext
	{
		std::unordered_map<InputKey, InputBindingBase*> mKeyMap;
		std::unordered_map<InputAxis, InputBindingBase*> mAxisMap;
		//std::unordered_map<InputComposite, InputBindingBase*> mCompositeMap;

	public:
		enum class ProcessMode
		{
			Consume = 1,
			Forward,
		};

		ProcessMode mode = ProcessMode::Consume;

		bool bEnabled = true;


		~InputContext();


		SA_ENGINE_API void Bind(const InputKey& _inKey, InputAction _action);
		SA_ENGINE_API void Bind(const InputAxis& _inAxis, InputRange _range);
		//void Bind(InputComposite _inComp, InputAction _action);

		void UnBind(const InputKey& _inKey);
		void UnBind(const InputAxis& _inAxis);
		//void UnBind(const InputComposite& _inComp);

		bool Process(const InputKey& _inKey);
		bool Process(const InputAxis& _inAxis);
		//bool Process(const InputComposite& _inComp);
	};
}

#endif // GUARD

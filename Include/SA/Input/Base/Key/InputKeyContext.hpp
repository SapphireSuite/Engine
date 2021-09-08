// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_CONTEXT_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_CONTEXT_GUARD

#include <memory>
#include <unordered_map>

#include <SA/Core/Debug.hpp>

#include <SA/Input/Base/Key/InputKeyBind.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyBinding.hpp>

namespace Sa
{
	class InputKeyContext
	{
		std::unordered_map<InputKey, std::vector<std::shared_ptr<InputKeyBinding>>> mMap;

	public:
		template <typename InBindT, typename... Args>
		std::shared_ptr<InputKeyBinding> Bind(const InputKeyBind& _inKeyBind, Args&&... _args);

		void UnBind(const InputKeyBind& _inKeyBind);
		void UnBind(const InputKey& _inKey);
		void UnBind(std::shared_ptr<InputKeyBinding> _inBinding);

		bool Process(const InputKey& _inKey);
	};
}

#include <SA/Input/Base/Key/InputKeyContext.inl>

#endif // GUARD

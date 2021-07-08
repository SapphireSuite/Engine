// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_CONTEXT_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_CONTEXT_GUARD

#include <memory>
#include <unordered_map>

#include <SA/Collections/Debug>

#include <SA/Input/Base/Key/InputKey.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyBinding.hpp>

namespace Sa
{
	class InputKeyContext
	{
		std::unordered_map<InputRawKey, std::vector<std::shared_ptr<InputKeyBinding>>> mMap;

	public:
		template <typename InBindT, typename... Args>
		std::shared_ptr<InputKeyBinding> Bind(const InputKey& _inKey, Args&&... _args);

		SA_ENGINE_API void UnBind(const InputKey& _inKey);
		SA_ENGINE_API void UnBind(const InputRawKey& _inRawKey);
		SA_ENGINE_API void UnBind(std::shared_ptr<InputKeyBinding> _inBinding);

		bool Process(const InputRawKey& _inRawKey);
	};
}

#include <SA/Input/Base/Key/InputKeyContext.inl>

#endif // GUARD

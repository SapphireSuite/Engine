// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_IINPUT_WINDOW_CONTEXT_GUARD
#define SAPPHIRE_INPUT_IINPUT_WINDOW_CONTEXT_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Input/Base/InputContext.hpp>

namespace Sa
{
	class AInputWindowContext : public Abstract
	{
		std::vector<InputContext*> mContexts;

	public:
		virtual ~AInputWindowContext();

		template <typename InputT>
		bool Process(const InputT& _input);

		SA_ENGINE_API InputContext* Create();
		SA_ENGINE_API bool Destroy(const InputContext* _context);

		void Clear();
	};
}

#include <SA/Input/Base/AInputWindowContext.inl>

#endif // GUARD

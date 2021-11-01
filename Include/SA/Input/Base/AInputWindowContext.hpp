// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_IINPUT_WINDOW_CONTEXT_GUARD
#define SAPPHIRE_INPUT_IINPUT_WINDOW_CONTEXT_GUARD

#include <SA/Input/Base/InputContext.hpp>

namespace Sa
{
	class AWindow;

	class AInputWindowContext
	{
		std::vector<InputContext*> mContexts;

	public:
		virtual ~AInputWindowContext();

		template <typename InputT>
		bool Process(const InputT& _input);

		virtual void Create(AWindow* _win) = 0;
		virtual void Destroy() = 0;

		InputContext* CreateContext();
		bool DestroyContext(const InputContext* _context);

		void Clear();
	};
}

#include <SA/Input/Base/AInputWindowContext.inl>

#endif // GUARD

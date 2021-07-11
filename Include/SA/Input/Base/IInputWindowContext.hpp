// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_INPUT_IINPUT_WINDOW_CONTEXT_GUARD
#define SAPPHIRE_INPUT_IINPUT_WINDOW_CONTEXT_GUARD

#include <SA/Core/Types/Interface.hpp>

#include <SA/Input/Base/InputContext.hpp>

namespace Sa
{
	class IWindow;

	class IInputWindowContext : public Interface
	{
		std::vector<InputContext*> mContexts;

	public:
		virtual ~IInputWindowContext();

		template <typename InputT>
		bool Process(const InputT& _input);

		SA_ENGINE_API InputContext* Create();
		SA_ENGINE_API bool Destroy(const InputContext* _context);

		void Clear();
	};
}

#include <SA/Input/Base/IInputWindowContext.inl>

#endif // GUARD

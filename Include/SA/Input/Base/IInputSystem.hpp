// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_SYSTEM_GUARD
#define SAPPHIRE_INPUT_INPUT_SYSTEM_GUARD

#include <vector>

#include <SA/Core/Types/Interface.hpp>

#include <SA/Input/Base/IInputWindowContext.hpp>

namespace Sa
{
	class IWindow;

	class IInputSystem : public Interface
	{
		std::unordered_map<const IWindow*, IInputWindowContext*> mWindowContextMap;

	protected:
		virtual IInputWindowContext* InstantiateWindowContext(IWindow* _win) = 0;
		SA_ENGINE_API virtual void DestroyWindowContext(IInputWindowContext* _winContext);

	public:
		SA_ENGINE_API virtual ~IInputSystem();

		SA_ENGINE_API IInputWindowContext* Register(IWindow* _win);
		SA_ENGINE_API bool UnRegister(const IWindow* _win);

		SA_ENGINE_API void Clear();

		virtual void Update() = 0;
	};
}

#endif // GUARD

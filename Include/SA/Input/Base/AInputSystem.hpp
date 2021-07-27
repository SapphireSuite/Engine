// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_AINPUT_SYSTEM_GUARD
#define SAPPHIRE_INPUT_AINPUT_SYSTEM_GUARD

#include <vector>

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Input/Base/AInputWindowContext.hpp>

namespace Sa
{
	class AWindow;

	class AInputSystem : public Abstract
	{
		std::unordered_map<const AWindow*, AInputWindowContext*> mWindowContextMap;

	protected:
		virtual AInputWindowContext* InstantiateWindowContext(AWindow* _win) = 0;
		SA_ENGINE_API virtual void DestroyWindowContext(AInputWindowContext* _winContext);

	public:
		SA_ENGINE_API virtual ~AInputSystem();

		SA_ENGINE_API AInputWindowContext* Register(AWindow* _win);
		SA_ENGINE_API bool UnRegister(const AWindow* _win);

		SA_ENGINE_API void Clear();


		virtual void Create() = 0;
		SA_ENGINE_API virtual void Destroy();

		virtual void Update() = 0;
	};
}

#endif // GUARD

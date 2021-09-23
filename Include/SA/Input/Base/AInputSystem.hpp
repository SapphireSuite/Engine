// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_AINPUT_SYSTEM_GUARD
#define SAPPHIRE_INPUT_AINPUT_SYSTEM_GUARD

#include <vector>

#include <SA/Core/Types/ASystem.hpp>

#include <SA/Input/Base/AInputWindowContext.hpp>

namespace Sa
{
	class AWindow;

	class AInputSystem : public ASystem
	{
		std::unordered_map<const AWindow*, AInputWindowContext*> mWindowContextMap;

	protected:
		virtual AInputWindowContext* InstantiateWindowContext() = 0;
		virtual void DeleteWindowContext(AInputWindowContext* _winContext) = 0;

	public:
		virtual ~AInputSystem();

		AInputWindowContext* Register(AWindow* _win);
		bool UnRegister(const AWindow* _win);

		void Clear();


		void Destroy() override;

		virtual void Update() = 0;
	};
}

#endif // GUARD

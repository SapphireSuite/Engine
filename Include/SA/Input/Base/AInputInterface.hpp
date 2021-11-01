// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_AINPUT_INTERFACE_GUARD
#define SAPPHIRE_INPUT_AINPUT_INTERFACE_GUARD

#include <vector>

#include <SA/Input/Base/AInputWindowContext.hpp>

namespace Sa
{
	class AWindow;

	class AInputInterface
	{
		std::unordered_map<const AWindow*, AInputWindowContext*> mWindowContextMap;

	protected:
		virtual AInputWindowContext* InstantiateWindowContext() = 0;
		virtual void DeleteWindowContext(AInputWindowContext* _winContext) = 0;

	public:
		virtual ~AInputInterface();

		AInputWindowContext* Register(AWindow* _win);
		bool UnRegister(const AWindow* _win);

		void Clear();

		virtual void Create() = 0;
		virtual void Destroy();

		virtual void Update() = 0;
	};
}

#endif // GUARD

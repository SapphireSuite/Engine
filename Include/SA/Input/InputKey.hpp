// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Window/Config.hpp>

#if SA_GLFW

#include <GLFW/glfw3.h>

#endif

namespace Sa
{
	enum class InputKey : uint16
	{
#if SA_GLFW

		Esc = GLFW_KEY_ESCAPE,

		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,

		_1 = GLFW_KEY_1,
		_2 = GLFW_KEY_2,
		_3 = GLFW_KEY_3,
		_4 = GLFW_KEY_4,
		_5 = GLFW_KEY_5,
		_6 = GLFW_KEY_6,
		_7 = GLFW_KEY_7,
		_8 = GLFW_KEY_8,
		_9 = GLFW_KEY_9,
		_0 = GLFW_KEY_0,

		Q = GLFW_KEY_Q,
		W = GLFW_KEY_W,
		E = GLFW_KEY_E,
		R = GLFW_KEY_R,
		T = GLFW_KEY_T,
		Y = GLFW_KEY_Y,
		U = GLFW_KEY_U,
		I = GLFW_KEY_I,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		A = GLFW_KEY_A,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		Z = GLFW_KEY_Z,
		X = GLFW_KEY_X,
		C = GLFW_KEY_C,
		V = GLFW_KEY_V,
		B = GLFW_KEY_B,
		N = GLFW_KEY_N,
		M = GLFW_KEY_M,

		BackQuote = GLFW_KEY_GRAVE_ACCENT,
		Tab = GLFW_KEY_TAB,
		CapsLock = GLFW_KEY_CAPS_LOCK,
		LeftShift = GLFW_KEY_LEFT_SHIFT,

		Minus = GLFW_KEY_MINUS,
		Equal = GLFW_KEY_EQUAL,
		Backspace = GLFW_KEY_BACKSPACE,

		LeftBracket = GLFW_KEY_LEFT_BRACKET,
		RightBracket = GLFW_KEY_RIGHT_BRACKET,
		BackSlash = GLFW_KEY_BACKSLASH,

		SemiColumn = GLFW_KEY_SEMICOLON,
		Quote = GLFW_KEY_APOSTROPHE,
		Enter = GLFW_KEY_ENTER,

		Comma = GLFW_KEY_COMMA,
		Period = GLFW_KEY_PERIOD,
		Slash = GLFW_KEY_SLASH,
		RightShift = GLFW_KEY_RIGHT_SHIFT,

		LeftCtrl = GLFW_KEY_LEFT_CONTROL,
		LeftFunction,
		LeftOS = GLFW_KEY_LEFT_SUPER,
		LeftAlt = GLFW_KEY_LEFT_ALT,
		Space = GLFW_KEY_SPACE,
		RightAlt = GLFW_KEY_RIGHT_ALT,
		RightOS = GLFW_KEY_RIGHT_SUPER,
		RightFunction,
		Menu = GLFW_KEY_MENU,
		RightCtrl = GLFW_KEY_RIGHT_CONTROL,

		UpArrow = GLFW_KEY_UP,
		LeftArrow = GLFW_KEY_LEFT,
		DownArrow = GLFW_KEY_DOWN,
		RightArrow = GLFW_KEY_RIGHT,

		NumLock = GLFW_KEY_NUM_LOCK,
		KeyPad0 = GLFW_KEY_KP_0,
		KeyPad1 = GLFW_KEY_KP_1,
		KeyPad2 = GLFW_KEY_KP_2,
		KeyPad3 = GLFW_KEY_KP_3,
		KeyPad4 = GLFW_KEY_KP_4,
		KeyPad5 = GLFW_KEY_KP_5,
		KeyPad6 = GLFW_KEY_KP_6,
		KeyPad7 = GLFW_KEY_KP_7,
		KeyPad8 = GLFW_KEY_KP_8,
		KeyPad9 = GLFW_KEY_KP_9,
		KeyPadDivide = GLFW_KEY_KP_DIVIDE,
		KeyPadMultiply = GLFW_KEY_KP_MULTIPLY,
		KeyPadSubstract = GLFW_KEY_KP_SUBTRACT,
		KeyPadAdd = GLFW_KEY_KP_ADD,
		KeyPadEnter = GLFW_KEY_KP_ENTER,
		KeyPadDecimal = GLFW_KEY_KP_DECIMAL,

		Delete = GLFW_KEY_DELETE,
		Pause = GLFW_KEY_PAUSE,
		PrintScreen = GLFW_KEY_PRINT_SCREEN,
		Home = GLFW_KEY_HOME,

#endif

		Max = 102
	};
}

#endif // GUARD

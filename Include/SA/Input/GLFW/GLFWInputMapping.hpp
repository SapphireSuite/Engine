// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_GLFW_INPUT_MAPPING_GUARD
#define SAPPHIRE_INPUT_GLFW_INPUT_MAPPING_GUARD

#include <SA/Core/Support/API/GLFW.hpp>

#include <SA/Core/Debug.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	std::unordered_map<int, Key> gGlfwToEngineInputMap
	{
		{ GLFW_KEY_ESCAPE, Key::Esc },

		{ GLFW_KEY_F1, Key::F1 },
		{ GLFW_KEY_F2, Key::F2 },
		{ GLFW_KEY_F3, Key::F3 },
		{ GLFW_KEY_F4, Key::F4 },
		{ GLFW_KEY_F5, Key::F5 },
		{ GLFW_KEY_F6, Key::F6 },
		{ GLFW_KEY_F7, Key::F7 },
		{ GLFW_KEY_F8, Key::F8 },
		{ GLFW_KEY_F9, Key::F9 },
		{ GLFW_KEY_F10, Key::F10 },
		{ GLFW_KEY_F11, Key::F11 },
		{ GLFW_KEY_F12, Key::F12 },

		{ GLFW_KEY_1, Key::_1 },
		{ GLFW_KEY_2, Key::_2 },
		{ GLFW_KEY_3, Key::_3 },
		{ GLFW_KEY_4, Key::_4 },
		{ GLFW_KEY_5, Key::_5 },
		{ GLFW_KEY_6, Key::_6 },
		{ GLFW_KEY_7, Key::_7 },
		{ GLFW_KEY_8, Key::_8 },
		{ GLFW_KEY_9, Key::_9 },
		{ GLFW_KEY_0, Key::_0 },

		{ GLFW_KEY_Q, Key::Q },
		{ GLFW_KEY_W, Key::W },
		{ GLFW_KEY_E, Key::E },
		{ GLFW_KEY_R, Key::R },
		{ GLFW_KEY_T, Key::T },
		{ GLFW_KEY_Y, Key::Y },
		{ GLFW_KEY_U, Key::U },
		{ GLFW_KEY_I, Key::I },
		{ GLFW_KEY_O, Key::O },
		{ GLFW_KEY_P, Key::P },
		{ GLFW_KEY_A, Key::A },
		{ GLFW_KEY_S, Key::S },
		{ GLFW_KEY_D, Key::D },
		{ GLFW_KEY_F, Key::F },
		{ GLFW_KEY_G, Key::G },
		{ GLFW_KEY_H, Key::H },
		{ GLFW_KEY_J, Key::J },
		{ GLFW_KEY_K, Key::K },
		{ GLFW_KEY_L, Key::L },
		{ GLFW_KEY_Z, Key::Z },
		{ GLFW_KEY_X, Key::X },
		{ GLFW_KEY_C, Key::C },
		{ GLFW_KEY_V, Key::V },
		{ GLFW_KEY_B, Key::B },
		{ GLFW_KEY_N, Key::N },
		{ GLFW_KEY_M, Key::M },


		{ GLFW_KEY_GRAVE_ACCENT, Key::BackQuote },
		{ GLFW_KEY_TAB, Key::Tab },
		{ GLFW_KEY_CAPS_LOCK, Key::CapsLock },
		{ GLFW_KEY_LEFT_SHIFT, Key::LeftShift },

		{ GLFW_KEY_MINUS, Key::Minus },
		{ GLFW_KEY_EQUAL, Key::Equal },
		{ GLFW_KEY_BACKSPACE, Key::Backspace },

		{ GLFW_KEY_LEFT_BRACKET, Key::LeftBracket },
		{ GLFW_KEY_RIGHT_BRACKET, Key::RightBracket },
		{ GLFW_KEY_BACKSLASH, Key::BackSlash },

		{ GLFW_KEY_SEMICOLON, Key::SemiColumn },
		{ GLFW_KEY_APOSTROPHE, Key::Quote },
		{ GLFW_KEY_ENTER, Key::Enter },

		{ GLFW_KEY_COMMA, Key::Comma },
		{ GLFW_KEY_PERIOD, Key::Period },
		{ GLFW_KEY_SLASH, Key::Slash },
		{ GLFW_KEY_RIGHT_SHIFT, Key::RightShift },


		{ GLFW_KEY_LEFT_CONTROL, Key::LeftCtrl },
		{ GLFW_KEY_LEFT_SUPER, Key::LeftOS },
		{ GLFW_KEY_LEFT_ALT, Key::LeftAlt },
		{ GLFW_KEY_SPACE, Key::Space },
		{ GLFW_KEY_RIGHT_ALT, Key::RightAlt },
		{ GLFW_KEY_RIGHT_SUPER, Key::RightOS },
		{ GLFW_KEY_MENU, Key::Menu },
		{ GLFW_KEY_RIGHT_CONTROL, Key::RightCtrl },

		{ GLFW_KEY_UP, Key::UpArrow },
		{ GLFW_KEY_LEFT, Key::LeftArrow },
		{ GLFW_KEY_DOWN, Key::DownArrow },
		{ GLFW_KEY_RIGHT, Key::RightArrow },

		{ GLFW_KEY_NUM_LOCK, Key::NumLock },
		{ GLFW_KEY_KP_0, Key::KeyPad0 },
		{ GLFW_KEY_KP_1, Key::KeyPad1 },
		{ GLFW_KEY_KP_2, Key::KeyPad2 },
		{ GLFW_KEY_KP_3, Key::KeyPad3 },
		{ GLFW_KEY_KP_4, Key::KeyPad4 },
		{ GLFW_KEY_KP_5, Key::KeyPad5 },
		{ GLFW_KEY_KP_6, Key::KeyPad6 },
		{ GLFW_KEY_KP_7, Key::KeyPad7 },
		{ GLFW_KEY_KP_8, Key::KeyPad8 },
		{ GLFW_KEY_KP_9, Key::KeyPad9 },
		{ GLFW_KEY_KP_DIVIDE, Key::KeyPadDivide },
		{ GLFW_KEY_KP_MULTIPLY, Key::KeyPadMultiply },
		{ GLFW_KEY_KP_SUBTRACT, Key::KeyPadSubstract },
		{ GLFW_KEY_KP_ADD, Key::KeyPadAdd },
		{ GLFW_KEY_KP_ENTER, Key::KeyPadEnter },
		{ GLFW_KEY_KP_DECIMAL, Key::KeyPadDecimal },

		{ GLFW_KEY_DELETE, Key::Delete },
		{ GLFW_KEY_PAUSE, Key::Pause },
		{ GLFW_KEY_PRINT_SCREEN, Key::PrintScreen },
		{ GLFW_KEY_HOME, Key::Home },

		{ GLFW_MOUSE_BUTTON_LEFT, Key::MouseLeft },
		{ GLFW_MOUSE_BUTTON_RIGHT, Key::MouseRight },
		{ GLFW_MOUSE_BUTTON_MIDDLE, Key::MouseMiddle },

	};

	KeyState GetKeyState(int _action)
	{
		switch (_action)
		{
			case GLFW_PRESS:
				return KeyState::Pressed;
			case GLFW_RELEASE:
				return KeyState::Released;
			case GLFW_REPEAT:
				return KeyState::Hold;
			default:
				SA_LOG("GLFW Key action [" << _action << "] not supported yet!", Warning, SA/Window/GLFW);
				return KeyState::Pressed;
		}
	}
}

#endif

#endif // GUARD

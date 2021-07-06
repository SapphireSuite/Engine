// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_INPUT_GLFW_INPUT_SYSTEM_GUARD
#define SAPPHIRE_INPUT_GLFW_INPUT_SYSTEM_GUARD

#include <SA/API/GLFW.hpp>

#include <SA/Input/Base/IInputSystem.hpp>

#include <SA/Maths/Space/Vector2.hpp>

#if SA_GLFW

namespace Sa
{
	class GLFWInputSystem : public IInputSystem
	{
		Vec2f mSavedMousePos;

	public:
		void Create(GLFWwindow* _handle);
		void Destroy();

		SA_ENGINE_API void Update() override final;

		void WindowKeyCallback(const InputKey& _inKey);
		void CursorPositionCallback(const Vec2ui& _windowSize, const Vec2f& _mousePos);
	};
}

#endif

#endif // GUARD

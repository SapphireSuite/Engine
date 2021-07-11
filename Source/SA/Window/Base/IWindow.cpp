// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Window/Base/IWindow.hpp>

#include <Input/Base/IInputSystem.hpp>

namespace Sa
{
	bool IWindow::IsMinimized() const
	{
		return bMinimized;
	}

	void IWindow::SetMinimized(bool _bIsMinimized)
	{
		bMinimized = _bIsMinimized;
		onMinimized(_bIsMinimized);
	}


	bool IWindow::IsMaximized() const
	{
		return bMaximized && !bMinimized;
	}

	void IWindow::SetMaximized(bool _bIsMaximized)
	{
		bMaximized = _bIsMaximized;
		onMaximized(_bIsMaximized);
	}


	const Vec2ui& IWindow::GetSize() const
	{
		return mSize;
	}

	void IWindow::SetSize(const Vec2ui& _size)
	{
		mSize = _size;
		onResize(_size);
	}


	WindowMode IWindow::GetWindowMode() const
	{
		return mMode;
	}

	void IWindow::SetWindowMode(WindowMode _mode)
	{
		mMode = _mode;
		onWindowModeChange(_mode);
	}


	void IWindow::Create(const CreateInfos& _infos)
	{
		mSize = _infos.dimension;

		// Always create as Windowed and call SetWindowMode.
		//mMode = _infos.mode;
	}


	void IWindow::Update()
	{
		GetInputSystem().Update();
	}
}

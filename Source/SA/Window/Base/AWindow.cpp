// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Window/Base/AWindow.hpp>

namespace Sa
{
	bool AWindow::IsMinimized() const
	{
		return bMinimized;
	}

	void AWindow::SetMinimized(bool _bIsMinimized)
	{
		bMinimized = _bIsMinimized;
		onMinimized(_bIsMinimized);
	}


	bool AWindow::IsMaximized() const
	{
		return bMaximized && !bMinimized;
	}

	void AWindow::SetMaximized(bool _bIsMaximized)
	{
		bMaximized = _bIsMaximized;
		onMaximized(_bIsMaximized);
	}


	const Vec2ui& AWindow::GetSize() const
	{
		return mSize;
	}

	void AWindow::SetSize(const Vec2ui& _size)
	{
		mSize = _size;
		onResize(_size);
	}


	WindowMode AWindow::GetWindowMode() const
	{
		return mMode;
	}

	void AWindow::SetWindowMode(WindowMode _mode)
	{
		mMode = _mode;
		onWindowModeChange(_mode);
	}


	void AWindow::Create(const CreateInfos& _infos)
	{
		mSize = _infos.dimension;

		// Always create as Windowed and call SetWindowMode.
		//mMode = _infos.mode;
	}
}

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Window/Base/IWindow.hpp>

#include <Input/Base/IInputSystem.hpp>

namespace Sa
{
	const Vec2ui& IWindow::GetSize() const
	{
		return mSize;
	}

	void IWindow::SetSize(const Vec2ui& _size)
	{
		mSize = _size;
		onResize(_size);
	}


	bool IWindow::IsMinimized() const
	{
		return bMinimized;
	}

	void IWindow::SetMinimized(bool _bIsMinimized)
	{
		bMinimized = _bIsMinimized;
		onMinimized(_bIsMinimized);
	}


	void IWindow::Create(uint32 _width, uint32 _height, const std::string& _name)
	{
		(void)_name;

		mSize = Vec2ui{ _width,_height };
	}


	void IWindow::Update()
	{
		GetInputSystem().Update();
	}
}

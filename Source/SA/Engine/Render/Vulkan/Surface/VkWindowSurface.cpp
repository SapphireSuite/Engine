// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

#include <Window/Base/AWindow.hpp>

namespace  SA::VK
{
    void WindowSurface::Create(AWindow* _win,  const Instance& _inst)
    {
        AWindowSurface::Create();

        mWindow = _win;
        mHandle = _win->CreateVkWindowSurfaceHandle(_inst);

		SA_LOG(L"Window Surface [" << mHandle << L"] created.", Infos, SA/Engine/Render/Vulkan);
    }

    void WindowSurface::Destroy(const Instance& _inst)
    {
        AWindowSurface::Destroy();
        
        SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, mWindow, L"Destroy null window surface.");

        mWindow->DestroyVkWindowSurfaceHandle(_inst, mHandle);
        mWindow = nullptr;
		
        SA_LOG(L"Window Surface [" << mHandle << L"] destroyed.", Infos, SA/Engine/Render/Vulkan);
    }


	WindowSurface::operator VkSurfaceKHR() const
    {
        return mHandle;
    }
}

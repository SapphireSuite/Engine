// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/ARenderInterface.hpp>

namespace Sa
{
	void ARenderInterface::DestroyGraphicInterface(ARenderGraphicInterface* _graphics)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _graphics);

		_graphics->Destroy();

		delete _graphics;
	}
}

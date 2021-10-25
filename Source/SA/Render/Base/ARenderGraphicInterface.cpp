// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/ARenderGraphicInterface.hpp>

namespace Sa
{
	void ARenderGraphicInterface::DestroyContextInterface(ARenderContextInterface* _context)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _context);

		_context->Destroy();

		delete _context;
	}
}

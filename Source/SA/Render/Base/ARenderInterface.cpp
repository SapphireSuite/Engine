// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/ARenderInterface.hpp>

#include <Render/Base/ARenderSubInterface.hpp>

namespace Sa
{
	void ARenderInterface::DestroySubInterface(ARenderSubInterface* _intf)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _intf);

		_intf->Destroy();

		delete _intf;
	}
}

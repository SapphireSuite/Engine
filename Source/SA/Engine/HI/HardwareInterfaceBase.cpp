// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Engine/HI/HardwareInterfaceBase.hpp>

#include <SA/Collections/Debug>

namespace Sa
{
	HardwareInterfaceBase::~HardwareInterfaceBase() noexcept(false)
	{
#if SA_DEBUG

		SA_ASSERT(Default, SA/HardwareInterface, !bCreated,
			L"Destructor called without previously calling Destroy().",
			L"Call interface->Destroy() before object destruction.")

#endif
	}


	void HardwareInterfaceBase::Create()
	{
#if SA_DEBUG

		bCreated = true;

#endif
	}

	void HardwareInterfaceBase::Destroy()
	{
		CheckCreated();

		Clear();

#if SA_DEBUG

		bCreated = false;

#endif
	}

	void HardwareInterfaceBase::Clear()
	{
	}


	void HardwareInterfaceBase::CheckCreated() const
	{
#if SA_DEBUG

		SA_ASSERT(Default, SA/HardwareInterface, bCreated,
			L"Interface must be previously created.",
			L"Call interface->Create().");

#endif
	}
}

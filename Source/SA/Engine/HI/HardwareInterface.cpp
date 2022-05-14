// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Collections/Debug>

namespace SA
{
#if SA_DEBUG

	HardwareInterface::~HardwareInterface() noexcept(false)
	{
		SA_ASSERT(Default, SA/Engine/HI, !bCreated,
			L"Destructor called without previously calling Destroy().",
			L"Call interface->Destroy() before object destruction.")

	}

#else

	HardwareInterface::~HardwareInterface()
	{
		
	}

#endif


	void HardwareInterface::Create()
	{
#if SA_DEBUG

		bCreated = true;

#endif
	}

	void HardwareInterface::Destroy()
	{
		Clear();

#if SA_DEBUG

		bCreated = false;

#endif
	}

	void HardwareInterface::Clear()
	{
		CheckCreated();
	}


	void HardwareInterface::CheckCreated() const
	{
#if SA_DEBUG

		SA_ASSERT(Default, SA/Engine/HI, bCreated,
			L"Interface must be previously created.",
			L"Call interface->Create().");

#endif
	}
}

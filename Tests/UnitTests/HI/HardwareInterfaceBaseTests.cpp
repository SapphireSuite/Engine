// Copyright(c) 2022 Sapphire's Suite. All Rights Reserved.

#include <gtest/gtest.h>

#include <SA/Collections/Debug>
#include <SA/Engine/HI/HardwareInterfaceBase.hpp>
using namespace Sa;

namespace Sa::UT::HardwareInterfaceBase
{
#if SA_DEBUG
	// Only throw on debug.
	#define SA_INTERFACE_THROW_TEST(statement) EXPECT_THROW(statement, Exception_Default)
#else
	// Never throw on release.
	#define SA_INTERFACE_THROW_TEST(statement) EXPECT_NO_THROW(statement)
#endif

	class MyInterface : public Sa::HardwareInterfaceBase
	{
	public:
		virtual ~MyInterface() = default;

		void Hello()
		{
			CheckCreated();

			SA_LOG("Hello, World!");
		}
	};


	TEST(HardwareInterfaceBase, NoCreateNoDestroy)
	{
		MyInterface intf;
	}

	TEST(HardwareInterfaceBase, CreateNoDestroy)
	{
		SA_INTERFACE_THROW_TEST([]()
		{
			MyInterface intf;

			intf.Create();

			// Destructor throw.

		}());
	}

	TEST(HardwareInterfaceBase, NoCreateDestroy)
	{
		SA_INTERFACE_THROW_TEST([]()
		{
			MyInterface intf;

			intf.Destroy();

		}());
	}

	TEST(HardwareInterfaceBase, CreateDestroy)
	{
		MyInterface intf;

		intf.Create();
		intf.Destroy();
	}

	TEST(HardwareInterfaceBase, NoCreateCheck)
	{
		SA_INTERFACE_THROW_TEST([]()
		{
			MyInterface intf;

			intf.Hello();

		}());
	}

	TEST(HardwareInterfaceBase, CreateCheck)
	{
		MyInterface intf;

		intf.Create();

		intf.Hello();

		intf.Destroy();
	}
}

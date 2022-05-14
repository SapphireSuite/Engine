// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <gtest/gtest.h>

#include <SA/Collections/Debug>
#include <SA/Engine/HI/Cast.hpp>
using namespace SA;

namespace SA::UT::Cast
{
	struct BaseStruct
	{
		int i = 0;
	};

	struct DerivedStruct : public BaseStruct
	{
		int j = 0;
	};


	class BaseClass
	{
	public:
		virtual ~BaseClass() = default;

		virtual void Do() = 0;
	};

	class DerivedClass : public BaseClass
	{
	public:
		void Do() override final
		{
		}
	};

	class OtherClass
	{
	};


	template <typename BaseT, typename DerivT>
	struct TypeDef
	{
		using BaseType = BaseT;
		using DerivType = DerivT;
	};

	template <typename T>
	class CastTest : public testing::Test
	{
	};

	using TestTypes = testing::Types<
		TypeDef<BaseStruct, DerivedStruct>,
		TypeDef<const BaseStruct, const DerivedStruct>,
		TypeDef<BaseClass, DerivedClass>,
		TypeDef<const BaseClass, const DerivedClass>
	>;
	TYPED_TEST_SUITE(CastTest, TestTypes);

	#define BaseT typename TypeParam::BaseType
	#define DerivT typename TypeParam::DerivType


	TYPED_TEST(CastTest, Ref)
	{
		DerivT derv;
		BaseT& base = derv;

		// Cast.
		DerivT& castDerv = SA::Cast<DerivT>(base);
		EXPECT_EQ(&castDerv, &derv);

		// CastRef.
		DerivT& castDerivRef = SA::CastRef<DerivT>(base);
		EXPECT_EQ(&castDerivRef, &derv);
	}


	TYPED_TEST(CastTest, Ptr)
	{
		DerivT* const derv = new DerivT();
		BaseT* const base = derv;

		// Cast.
		DerivT* const castDerv = SA::Cast<DerivT>(base);
		EXPECT_EQ(castDerv, derv);

		// CastRef.
		DerivT& castDerivRef = SA::CastRef<DerivT>(base);
		EXPECT_EQ(&castDerivRef, derv);


		// Only test with polymorphism.
		if constexpr (std::is_same_v<std::remove_const_t<BaseT>, BaseClass>)
		{
			EXPECT_THROW(SA::CastRef<OtherClass>(base), Exception_Nullptr);
		}


		delete derv;
	}

}

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_FUNCTION_GUARD
#define SAPPHIRE_CORE_FUNCTION_GUARD

#include <SA/Collections/Debug>

namespace Sa
{
	namespace Intl
	{
		/**
		*	\brief Base struct of member function data.
		*
		*	Interface class with virtual destructor to store template child class.
		*/
		struct FuncMemberDataBase
		{
			/**
			*	\brief default virtual destructor.
			*	Ensure correct child class destruction on delete.
			*/
			virtual ~FuncMemberDataBase() = default;
		};

		/**
		*	\brief Data struct for <b>typed</b> member function.
		*
		*	\tparam C		Caller type of function's declaration.
		*	\tparam R		Return type of function's declaration.
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename C, typename R, typename... Args>
		struct FuncMemberData : public FuncMemberDataBase
		{
			/// Caller ptr handle.
			C* caller = nullptr;

			/// Function ptr handle.
			R(C::* func)(Args...) = nullptr;

			/**
			*	\brief Default value constructor.
			*
			*	\param[in] _caller	Caller of the member function.
			*	\param[in] _func	Member function to call.
			*/
			FuncMemberData(C* _caller, R(C::* _func)(Args...));

			static R InterfaceCall(void*, Args...);
		};
	}

	template <typename T>
	class Function;

	template <typename R, typename... Args>
	class Function<R(Args...)>
	{
		/// Abstract member data (used by function interface for member function call).
		Intl::FuncMemberDataBase* mData = nullptr;

		union
		{
			/// Static function ptr.
			R(*mSfunc)(Args...) = nullptr;

			/// Internal interface function ptr (handle for member function call).
			R(*mIntlFunc)(void*, Args...);
		};

	public:

//{ Constructors

		Function() = default;

		Function(R(*_func)(Args...)) noexcept;

		template <typename C>
		Function(C* _caller, R(C::*_func)(Args...));

//}

//{ Methods

		void Set(R(*_func)(Args...));
		
		template <typename C>
		void Set(C* _caller, R(C::* _func)(Args...));


		void Clear();

		bool IsEmpty() const noexcept;


		R Execute(Args... _args);
//}

//{ Operators

		Function& operator=(R(*_func)(Args...)) noexcept;

		//template <typename C>
		//Function& operator=(C* _caller, R(C::* _func)(Args...));

		R operator()(Args... _args);

//}
	};
}


#include <SA/Core/Types/Variadics/Function.inl>

#endif // GUARD

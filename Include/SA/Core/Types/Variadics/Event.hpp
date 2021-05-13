// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_EVENT_GUARD
#define SAPPHIRE_CORE_EVENT_GUARD

#include <vector>

#include <SA/Collections/Debug>

/**
*	\file Event.hpp
*
*	\brief \b Definition of Sapphire \b Event type.
*
*	\ingroup Core_Types
*	\{
*/


namespace Sa
{
	namespace Intl
	{
		/**
		*	\brief Handle struct for a function.
		* 
		*	\tparam R		Return type of function's declaration.
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename R, typename... Args>
		struct FuncHandle
		{
			/// Function ptr handle.
			R(*func)(Args...) = nullptr;

			/// result ptr handle.
			R* result = nullptr;
		};

		/**
		*	\brief Handle struct for a function with void return type.
		* 
		*	Template specialization of FuncHandle for function with void return type.
		* 
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename... Args>
		struct FuncHandle<void, Args...>
		{
			/// Function ptr handle.
			void(*func)(Args...) = nullptr;
		};


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
			FuncMemberData(C* _caller, R(C::* _func)(Args...)) :
				caller{ _caller },
				func{ _func }
			{
			}
		};

		/**
		*	\brief Handle struct for a member function.
		*
		*	\tparam R		Return type of function's declaration.
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename R, typename... Args>
		struct FuncMemberHandle
		{
			/// Abstract member data (used by function interface).
			FuncMemberDataBase* data = nullptr;

			/// Interface function ptr handle.
			R(*func)(void*, Args...) = nullptr;

			/// result ptr handle.
			R* result = nullptr;
		};

		/**
		*	\brief Handle struct for a member function with void return type.
		* 
		*	Template specialization of FuncMemberHandle for member function with void return type.
		* 
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename... Args>
		struct FuncMemberHandle<void, Args...>
		{
			/// Abstract member data (used by function interface).
			FuncMemberDataBase* data = nullptr;

			/// Interface function ptr handle.
			void(*func)(void*, Args...) = nullptr;
		};
	}


	/**
	*	\brief Sapphire Event default (undefined) declaration.
	* 
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class Event;

	/**
	*	\brief Sapphire Event class.
	* 
	*	Template specialization for R(Args...) deduction.
	* 
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class Event<R(Args...)>
	{
		/// Function handle type.
		using FuncHandle = Intl::FuncHandle<R, Args...>;

		/// Member function handle type.
		using FuncMemberHandle = Intl::FuncMemberHandle<R, Args...>;

		/// Registered functions.
		std::vector<FuncHandle> mFunctions;

		/// Registered member functions.
		std::vector<FuncMemberHandle> mMemberFunctions;

	public:
		/// Default constructor.
		Event() = default;

		/// Deleted move constructor.
		Event(Event&&) = delete;

		/// Deleted copy constructor.
		Event(const Event&) = delete;

		/// Destructor (auto clean).
		~Event();


		/**
		*	\brief Check whether this event is <b>empty</b> (no function registered).
		* 
		*	\returns true if empty.
		*/
		bool IsEmpty() const noexcept;

		/**
		*	\brief <b>Clear</b> all registered function.
		*/
		void Clear();


		/**
		*	\brief <b>Add</b> a function to <b>register</b>.
		* 
		*	Ensure <b>registered order</b> on execution.
		* 
		*	\param[in] _func	Function to register.
		*	\param[in] _result	Optionnal result handle.
		*/
		void Add(R(*_func)(Args...), R* _result = nullptr);

		/**
		*	\brief <b>Add</b> a member function to <b>register</b>.
		* 
		*	Ensure <b>registered order</b> on execution.
		* 
		*	\tparam C			Caller type.
		* 
		*	\param[in] _caller	Caller instance to call function from.
		*	\param[in] _func	Member function to register.
		*	\param[in] _result	Optionnal result handle.
		*/
		template <typename C>
		void Add(C* _caller, R(C::* _func)(Args...), R* _result = nullptr);


		/**
		*	\brief <b>Remove</b> a registered function.
		* 
		*	Start function iteration from <b>first</b> to <b>last</b> registered.
		* 
		*	\param[in] _func	Function to unregister.
		* 
		*	\returns true if successfully removed, otherwise false.
		*/
		bool Remove(R(*_func)(Args...));

		/**
		*	\brief <b>Remove</b> a registered member function.
		* 
		*	Start function iteration from <b>first</b> to <b>last</b> registered.
		*
		*	\param[in] _caller	Caller instance of registered function.
		*	\param[in] _func	Member function to unregister.
		* 
		*	\returns true if successfully removed, otherwise false.
		*/
		template <typename C>
		bool Remove(const C* _caller, R(C::* _func)(Args...));


		/**
		*	\brief <b>Reverse Remove</b> a registered function.
		* 
		*	Start function iteration from <b>last</b> to <b>first</b> registered.
		*
		*	\param[in] _func	Function to unregister.
		* 
		*	\returns true if successfully removed, otherwise false.
		*/
		bool RRemove(R(*_func)(Args...));

		/**
		*	\brief <b>Reverse Remove</b> a registered member function.
		* 
		*	Start function iteration from <b>last</b> to <b>first</b> registered.
		*
		*	\param[in] _caller	Caller instance of registered function.
		*	\param[in] _func	Member function to unregister.
		* 
		*	\returns true if successfully removed, otherwise false.
		*/
		template <typename C>
		bool RRemove(const C* _caller, R(C::* _func)(Args...));


		/**
		*	\brief <b>Execute</b> all <b>registered</b> functions.
		* 
		*	Ensure <b>registered order</b> execution.
		* 
		*	\param[in] _args	Argument to forward to functions.
		*/
		void Execute(const Args&... _args);

		/**
		*	\brief <b>Execute</b> all <b>registered</b> functions.
		* 
		*	Ensure <b>registered order</b> execution.
		* 
		*	\param[in] _results	Optionnal output results (append).
		*	\param[in] _args	Argument to forward to functions.
		*/
		void Execute(std::vector<R>& _results, const Args&... _args);


		/**
		*	\brief Deleted move operator.
		* 
		*	\return this.
		*/
		Event& operator=(Event&&) = delete;

		/**
		*	\brief Deleted copy operator.
		* 
		*	\return this.
		*/
		Event& operator=(const Event&) = delete;


		/**
		*	\brief <b>Add</b> a function to <b>register</b>.
		* 
		*	Use Add() method.
		*
		*	\param[in] _func	Function to register.
		* 
		*	\returns This event.
		*/
		Event& operator+=(R(*_func)(Args...));

		/**
		*	\brief <b>Remove</b> a registered function.
		* 
		*	Use Remove() method.
		* 
		*	\param[in] _func	Function to unregister.
		* 
		*	\returns This event.
		*/
		Event& operator-=(R(*_func)(Args...));


		/**
		*	\brief <b>Execute</b> all <b>registered</b> functions.
		* 
		*	Use Execute() method.
		*
		*	\param[in] _args	Argument to forward to functions.
		*/
		void operator()(const Args&... _args);

		/**
		*	\brief <b>Execute</b> all <b>registered</b> functions.
		* 
		*	Use Execute() method.
		*	Ensure <b>registered order</b> execution.
		* 
		*	\param[in] _results	Optionnal output results (append).
		*	\param[in] _args	Argument to forward to functions.
		*/
		void operator()(std::vector<R>& _results, const Args&... _args);
	};
}

#include <SA/Core/Types/Variadics/Event.inl>
	

/** \} */

#endif // GUARD

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_ARGS_STR_GUARD
#define SAPPHIRE_CORE_ARGS_STR_GUARD

#include <string>
#include <vector>

#include <SA/Core/Debug/ToString.hpp>

/**
*	\file ArgsStr.hpp
* 
*	\brief \b Convert variadic parameters to string.
* 
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// Convert variadic macro parameters into strings.
	class ArgsStr
	{
	public:
		/// Pair of param name and value.
		struct Param
		{
			/// Param's name.
			std::string name;

			/// Param's value as a string.
			std::string value;
		};

		/// Parameters parsing results.
		std::vector<Param> params;


		/// Default constructor.
		ArgsStr() = default;

		/**
		*	\brief \e Value constructor with names only.
		* 
		*	Parse _paramNames.
		*
		*	\param[in] _paramNames	String containing all parameters' names.
		*/
		SA_ENGINE_API ArgsStr(const std::string& _paramNames);

		/**
		*	\brief \e Value constructor
		* 
		*	Parse _paramNames and _args.
		*
		*	\tparam Args	Args types.
		* 
		*	\param[in] _paramNames	String containing all parameters' names.
		*	\param[in] _args		Argument's values.
		*/
		template <typename... Args>
		ArgsStr(const std::string& _paramNames, const Args&... _args);


		/**
		*	\brief \e Append parameters' name only at the end.
		* 
		*	Parse _paramNames.
		*
		*	\param[in] _paramNames	String containing all parameters' names.
		*/
		SA_ENGINE_API void Append(const std::string& _paramNames);

		/**
		*	\brief \e Append parameters at the end.
		* 
		*	Parse _paramNames and _args.
		*
		*	\tparam FirstT	first arg type.
		*	\tparam Args	Args types.
		* 
		*	\param[in] _paramNames	String containing all parameters' names.
		*	\param[in] _first		First Argument's value.
		*	\param[in] _args		Argument's values.
		*/
		template <typename FirstT, typename... Args>
		void Append(const std::string& _paramNames, const FirstT& _first, const Args&... _args);


		/**
		*	\brief \b params \e member access operator.
		* 
		*	\return handled params.
		*/
		SA_ENGINE_API std::vector<Param>* operator->() noexcept;

		/**
		*	\brief \b params \e member access operator.
		* 
		*	\return handled params.
		*/
		SA_ENGINE_API const std::vector<Param>* operator->() const noexcept;


		/**
		*	\brief \b param \e member access operator.
		* 
		*	\param[in] _index	Index to access at.
		* 
		*	\return handled param at index.
		*/
		SA_ENGINE_API Param& operator[](uint32 _index);

		/**
		*	\brief \b param \e member access operator.
		* 
		*	\param[in] _index	Index to access at.
		*
		*	\return handled param at index.
		*/
		SA_ENGINE_API const Param& operator[](uint32 _index) const;
	};


	/**
	*	\def SA_STR_ARGS(...)
	* 
	*	\brief Helper macro to create ArgsStr from variadic macro.
	* 
	*	\param[in] ...	variadic macro parameters used as input.
	* 
	*	\return Created ArgsStr from input.
	*/
	#define SA_STR_ARGS(...) ArgsStr(#__VA_ARGS__, ##__VA_ARGS__)

	#define SA_STR_ARGS_NAMES(...) ArgsStr(#__VA_ARGS__)


#endif
}

#include <SA/Core/Debug/ArgsStr.inl>


/** \} */

#endif // GUARD

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
	class ArgsStr
	{
		/// \brief Generate Params from params' names and values.
		template <typename FirstT, typename... Args>
		void GenerateParamStr(std::string _paramNames, const FirstT& _first, const Args&... _args);

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
		*	\return handled param at index.
		*/
		SA_ENGINE_API Param& operator[](uint32 _index);

		/**
		*	\brief \b param \e member access operator.
		* 
		*	\return handled param at index.
		*/
		SA_ENGINE_API const Param& operator[](uint32 _index) const;
	};


	/**
	*	\def SA_STR_ARGS
	* 
	*	\brief Helper macro to create ArgsStr from variadic macro.
	* 
	*	\param[in] __VA_ARGS__	variadic macro parameters used as input.
	* 
	*	\return Created ArgsStr from input.
	*/
	#define SA_STR_ARGS(...) ArgsStr(#__VA_ARGS__, ##__VA_ARGS__)
}


/** \} */

#include <SA/Core/Debug/ArgsStr.inl>

#endif // GUARD

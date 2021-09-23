// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_RAII_GUARD
#define SAPPHIRE_CORE_RAII_GUARD

#include <SA/Config.hpp>

/**
*	\file RAII.hpp
*
*	\brief \b RAII base type implementation.
*
*	\ingroup Core_Types
*	\{
*/


namespace Sa
{
	/// \cond Internal

	namespace Intl
	{
		/// RAII Base class (remove move and copy operations).
		class RAIIBase
		{
		public:
			/// \b Default constructor.
			RAIIBase() = default;

			/// \b Deleted \e move constructor.
			RAIIBase(RAIIBase&&) = delete;

			/// \b Deleted \e copy constructor.
			RAIIBase(const RAIIBase&) = delete;


			/**
			*	\brief \b Deleted \e move operator.
			*
			*	\return this instance.
			*/
			RAIIBase& operator=(RAIIBase&&) = delete;

			/**
			*	\brief \b Deleted \e copy operator.
			*
			*	\return this instance.
			*/
			RAIIBase& operator=(const RAIIBase&) = delete;
		};
	}

	/// \endcond

	/**
	*	\brief Template class for RAII definitions.
	*
	*	This is only a forward declaration.
	*	The final class must be defined by the user by creating
	*	a template specialization of RAII class which inherit from RAIIBase.
	*
	*	\implements RAIIBase
	*/
	template <typename T>
	class RAII;


	/**
	*	\brief RAII specialization for bool.
	*
	*	\implements RAII
	*/
	template <>
	class RAII<bool> final : Intl::RAIIBase
	{
		/// The handled bool.
		bool& mHandle;

	public:
		/**
		*	\brief \e Value constructor
		*
		*	\param[in, out] _handle		Bool to handle.
		*	\param[in] _value			Value to assign to the handle.
		*/
		RAII(bool& _handle, bool _value = true) noexcept;

		/// \b Reset handle to !value.
		~RAII() noexcept;
	};
}


/** \} */

#endif // GUARD

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_SIZE_OF_GUARD
#define SAPPHIRE_CORE_SIZE_OF_GUARD

#include <SA/Core/Types/Int.hpp>
#include <SA/Core/Types/Variadics/HasMember.hpp>

/**
*	\file SizeOf.hpp
* 
*	\brief \b SizeOf algorithms implementation.
* 
*	\ingroup Core_Algorithms
*	\{
*/

namespace Sa
{
	/// \cond Internal

	namespace Intl
	{
		SA_DEFINE_HAS_MEMBER(size);
		SA_DEFINE_HAS_MEMBER(Size);
	}

	/// \endcond

	/**
	*	\brief \e Get number of elements in _elems.
	* 
	*	\tparam T	Element type.
	* 
	*	\param[in] _elems	elements to count.
	* 
	*	\return number of elements in param.
	*/
	template <typename SizeT = uint64, typename T>
	SizeT SizeOf(const T& _elems)
	{
		if constexpr (!std::is_arithmetic<T>::value)
		{
			if constexpr (Intl::HM_size<T>::value)
				return static_cast<uint32>(_elems.size());
			else if constexpr (Intl::HM_Size<T>::value)
				return static_cast<uint32>(_elems.Size());
		}
		else
			return 1u;
	}

	/**
	*	\brief \e Get number of elements in _tab.
	* 
	*	Template specialization for tab.
	* 
	*	\tparam T		Element type.
	*	\tparam uint32	Tab size.
	* 
	*	\param[in] _tab	Tab to count.
	* 
	*	\return number of elements in tab.
	*/
	template <typename SizeT = uint64, typename T, uint32 size>
	constexpr SizeT SizeOf(const T(&_tab)[size])
	{
		(void)_tab;

		return size;
	}

	/**
	*	\brief \e Get number of \b octets of _elems.
	* 
	*	\tparam T	Element type.
	* 
	*	\param[in] _elems	elements to count.
	* 
	*	\return octets number of _elems.
	*/
	template <typename SizeT = uint64, typename T>
	constexpr SizeT OctSizeOf(const T& _elems)
	{
		const SizeT sizeOf = SizeOf(_elems);

		if constexpr (!std::is_arithmetic<T>::value)
		{
			if constexpr (Intl::HM_size<T>::value)
				return sizeOf * sizeof(typename T::value_type);
			else if constexpr (Intl::HM_Size<T>::value)
				return sizeOf * sizeof(typename T::Type);
		}
		else
			return sizeOf * sizeof(T);
	}


	/**
	*	\brief \e Get number of \b octets in _tab.
	* 
	*	Template specialization for tab.
	* 
	*	\tparam T		Element type.
	*	\tparam uint32	Tab size.
	* 
	*	\param[in] _tab	Tab to count.
	* 
	*	\return octets number of tab.
	*/
	template <typename SizeT = uint64, typename T, uint32 size>
	constexpr SizeT OctSizeOf(const T(&_tab)[size])
	{
		return SizeOf(_tab) * sizeof(T);
	}


	/**
	*	\brief \e Get number of \b bits of _elems.
	* 
	*	\tparam T	Element type.
	* 
	*	\param[in] _elems	elements to count.
	* 
	*	\return bits number of _elems.
	*/
	template <typename SizeT = uint64, typename T>
	constexpr SizeT BitSizeOf(const T& _elems)
	{
		return OctSizeOf(_elems) * 8u;
	}

	/**
	*	\brief \e Get number of \b bits in _tab.
	* 
	*	Template specialization for tab.
	* 
	*	\tparam T		Element type.
	*	\tparam uint32	Tab size.
	* 
	*	\param[in] _tab	Tab to count.
	* 
	*	\return bits number of tab.
	*/
	template <typename SizeT = uint64, typename T, uint32 size>
	constexpr SizeT BitSizeOf(const T(&_tab)[size])
	{
		return OctSizeOf(_tab) * 8u;
	}


	/**
	*	\brief \e Get size of packed _args.
	* 
	*	Helper for sizeof variadic macro parameters.
	* 
	*	\tparam Args		Argument types.
	* 
	*	\param[in] _args	Argument values.
	* 
	*	\return	Size of argument pack.
	*/
	template <typename SizeT = uint64, typename... Args>
	constexpr SizeT SizeOfArgs(const Args&... _args)
	{
		return sizeof...(_args);
	}
}


/** \} */

#endif // GUARD

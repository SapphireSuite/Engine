// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_DEBUG_MACROS_GUARD
#define SAPPHIRE_CORE_DEBUG_MACROS_GUARD

#include <SA/Core/Support/Compilers.hpp>
#include <SA/Core/Support/Stringify.hpp>

#include <SA/Core/Debug/ToString.hpp>
#include <SA/Core/Debug/Log/Logger.hpp>
#include <SA/Core/Debug/Streams/ConsoleLogStream.hpp>

/**
*	\file Debug.hpp
* 
*	\brief \b Debug Core implementation.
* 
*	Define Debug log and assertion macros.
* 
*	\ingroup Core_Debug
*	\{
*/


namespace Sa::Debug
{
#if SA_LOGGING

	/// \cond Internal

	namespace Intl
	{
		/**
		*	\brief \e Getter of file name from file path.
		*
		*	\param[in] _filePath	Full path to the file.
		*
		*	\returns pointer to the file name in _filePath.
		*/
		const wchar* GetFileNameFromPath(const wchar* _filePath) noexcept;

		/**
		*	\brief Remove spaces in string.
		* 
		*	\param[in] _str	string to remove spaces in.
		* 
		*	\return New string without spaces.
		*/
		std::wstring RemoveSpaces(std::wstring _str) noexcept;
	}

#if SA_GNU || SA_CLANG && !SA_MSVC

	#define __SA_FUNC_NAME __PRETTY_FUNCTION__

#elif SA_MSVC

	#define __SA_FUNC_NAME __FUNCSIG__

#else

	#define __SA_FUNC_NAME __FUNCTION__

#endif

	#define __SA_FILE_NAME Sa::Debug::Intl::GetFileNameFromPath(SA_WIDE(__FILE__))

	#define __SA_CHAN_NAME(_chan) Sa::Debug::Intl::RemoveSpaces(SA_WSTR(_chan))

	#define __SA_CREATE_LOG(_str, _lvl, _chan, _dets) Sa::Log(\
		__SA_FILE_NAME,\
		__LINE__,\
		__SA_FUNC_NAME,\
		(std::wstring() << _str),\
		Sa::LogLevel::_lvl,\
		__SA_CHAN_NAME(_chan),\
		(std::wstring() << _dets)\
	)

	#define __SA_CREATE_EXCEPTION(_type, _chan, ...) __SA_CREATE_EXCEPTION_##_type(\
		(Sa::Exception::BaseInfos{\
			__SA_FILE_NAME,\
			__LINE__,\
			__SA_FUNC_NAME,\
			__SA_CHAN_NAME(_chan)\
		}),\
		##__VA_ARGS__\
	)

	/// \endcond Internal

	/// Console log stream instance.
	extern ConsoleLogStream csl;

	/// Logger instance.
	extern Logger logger;


	/// \cond Internal

	#define __SA_SELECT_LOG_MACRO(_1, _2, _3, _4, _name, ...) _name

	#define __SA_LOG4(_str, _lvl, _chan, _dets)	{ Sa::Debug::logger.Push(__SA_CREATE_LOG(_str, _lvl, _chan, _dets)); }
	#define __SA_LOG3(_str, _lvl, _chan)	__SA_LOG4(_str, _lvl, _chan, L"")
	#define __SA_LOG2(_str, _lvl)			__SA_LOG3(_str, _lvl, Default)
	#define __SA_LOG1(_str)					__SA_LOG2(_str, Normal)
	
	/// \endcond Internal

#if !defined(DOXYGEN)

	#define SA_LOG(...) __SA_SELECT_LOG_MACRO(__VA_ARGS__, __SA_LOG4, __SA_LOG3, __SA_LOG2, __SA_LOG1)(__VA_ARGS__)


	#define __SA_COND_LOG(_pred, _lvl, ...)		{ if(!(_pred)) SA_LOG(SA_WSTR(_pred), _lvl, ##__VA_ARGS__) }

	#define SA_WARN(_pred, ...) __SA_COND_LOG(_pred, Warning, ##__VA_ARGS__)
	#define SA_ERROR(_pred, ...) __SA_COND_LOG(_pred, Error, ##__VA_ARGS__)


	#if SA_DEBUG // Assertion requieres active Debug.

		#define SA_ASSERT(_type, _chan, ...) { Sa::Debug::logger.Assert(__SA_CREATE_EXCEPTION(_type, _chan, ##__VA_ARGS__)); }

		#define SA_ASSERT_EXEC(_type, _chan, _exec, ...) SA_ASSERT(_type, _chan, _exec, ##__VA_ARGS__)

	#else

		#define SA_ASSERT(...) {}
	
		#define SA_ASSERT_EXEC(_type, _chan, _exec, ...) { _exec; }

	#endif

#else

	#define SA_LOG(_str, _lvl, _chan, _dets)
	/**
	*	\def SA_LOG(_str, _lvl, _chan, _dets)
	*
	*	\brief Sapphire Log macro.
	*
	*	Helper macro to use Debug::Log.
	*
	*	\param[in] _str		String message of the log.
	*	\param[in] _lvl		Level of the log (optional).
	*	\param[in] _chan	Channel of the log (optional).
	*	\param[in] _dets	Additional details string of the log (optional).
	*/

	#define SA_WARN(_pred, _chan, _dets)
	/**
	*	\def SA_WARN(_pred, _chan, _dets)
	*
	*	\brief Sapphire Log "warning if" macro.
	*
	*	Helper macro to use conditionnal Debug::Log warning.
	*
	*	\param[in] _pred	predicate of the Log. Output warnings on false.
	*	\param[in] _chan	Channel of the log.
	*	\param[in] _dets	Additional details string of the log (optional).
	*/

	#define SA_ERROR(_pred, _chan, _dets)
	/**
	*	\def SA_ERROR(_pred, _chan, _dets)
	*
	*	\brief Sapphire Log "error if" macro.
	*
	*	Helper macro to use conditionnal Debug::Log error.
	*
	*	\param[in] _pred	predicate of the Log. Output error on false.
	*	\param[in] _chan	Channel of the log.
	*	\param[in] _dets	Additional details string of the log (optional).
	*/

	#define SA_ASSERT(_type, _chan, ...)
	/**
	*	\def SA_ASSERT(_type, _chan, ...)
	*
	*	\brief Sapphire Assertion macro.
	*
	*	Helper macro to use Debug::Assert.
	*
	*	\param[in] _type		type of the exception.
	*	\param[in] _chan		Channel of the assert.
	*	\param[in] ...			Additionnal args for exception (depends on _type).
	*/

	#define SA_ASSERT_EXEC(_type, _chan, _exec, ...)
	/**
	*	\def SA_ASSERT_EXEC(_type, _chan, _exec, ...)
	*
	*	\brief Sapphire Assertion execution macro.
	*	_exec will still be executed in non-debug but no debug infos will be generated.
	*
	*	Helper macro to use Debug::Assert.
	*
	*	\param[in] _type		type of the exception.
	*	\param[in] _chan		Channel of the assert.
	*	\param[in] _exec		Method to execute (even in non-debug).
	*	\param[in] ...			Additionnal args for exception (depends on _type).
	*/

#endif

#else

	#define SA_LOG(...) {}

	#define SA_WARN(...) {}

	#define SA_ASSERT(...) {}

	#define SA_ASSERT_EXEC(_type, _chan, _exec, ...) { _exec; }

#endif
}

/** \} */

#endif // GUARD

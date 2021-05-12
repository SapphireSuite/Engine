// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_DEBUG_MACROS_GUARD
#define SAPPHIRE_CORE_DEBUG_MACROS_GUARD

#include <SA/Core/Support/Compilers.hpp>
#include <SA/Core/Support/Stringify.hpp>

#include <SA/Core/Debug/ToString.hpp>
#include <SA/Core/Debug/Log/Logger.hpp>
#include <SA/Core/Debug/Log/Streams/LogConsoleStream.hpp>

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
		SA_ENGINE_API const wchar* GetFileNameFromPath(const wchar* _filePath) noexcept;

		/**
		*	\brief Remove spaces in string.
		* 
		*	\param[in] _str	string to remove spaces in.
		* 
		*	\return New string without spaces.
		*/
		SA_ENGINE_API std::wstring RemoveSpaces(std::wstring _str) noexcept;
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

	#define __SA_CREATE_LOG(_str, _lvl, _chan) Sa::Log(\
		__SA_FILE_NAME,\
		__LINE__,\
		__SA_FUNC_NAME,\
		(std::wstring() << _str),\
		Sa::LogLevel::_lvl,\
		__SA_CHAN_NAME(_chan)\
	)

	#define __SA_CREATE_WARNING(_pred, _chan, _dets) Sa::Log(\
		__SA_FILE_NAME,\
		__LINE__,\
		__SA_FUNC_NAME,\
		SA_WSTR(_pred),\
		Sa::LogLevel::Warning,\
		__SA_CHAN_NAME(_chan),\
		(std::wstring() << _dets)\
	)

	#define __SA_CREATE_EXCEPTION(_type, _chan, ...) Sa::Exception_##_type(\
		__SA_FILE_NAME,\
		__LINE__,\
		__SA_FUNC_NAME,\
		__SA_CHAN_NAME(_chan),\
		##__VA_ARGS__\
	)

	/// \endcond Internal

	SA_ENGINE_API extern LogConsoleStream csl;
	SA_ENGINE_API extern Logger logger;


	/// \cond Internal

	#define __SA_SELECT_LOG_MACRO(_1, _2, _3, _name, ...) _name

	#define __SA_LOG3(_str, _lvl, _chan)	{ Sa::Debug::logger.Log(__SA_CREATE_LOG(_str, _lvl, _chan)); }
	#define __SA_LOG2(_str, _lvl)			__SA_LOG3(_str, _lvl, Default)
	#define __SA_LOG1(_str)					__SA_LOG2(_str, Normal)
	
	/// \endcond Internal

	/**
	*	\def SA_LOG(_str, _lvl, _chan)
	*
	*	\brief Sapphire Log macro.
	*
	*	Helper macro to use Debug::Log.
	*
	*	\param[in] _str		String message of the log.
	*	\param[in] _lvl		Level of the log (optional).
	*	\param[in] _chan	Channel of the log (optional).
	*/
	#define SA_LOG(...) __SA_SELECT_LOG_MACRO(__VA_ARGS__, __SA_LOG3(__VA_ARGS__), __SA_LOG2(__VA_ARGS__), __SA_LOG1(__VA_ARGS__))
	//#define SA_LOG(...) __SA_SELECT_LOG_MACRO(__VA_ARGS__, __SA_LOG3, __SA_LOG2, __SA_LOG1)(__VA_ARGS__)


	/// \cond Internal

	#define __SA_WARN3(_pred, _chan, _dets)	{ if(!(_pred)) Sa::Debug::logger.Log(__SA_CREATE_WARNING(_pred, _chan, _dets)); }
	#define __SA_WARN2(_pred, _chan)		__SA_WARN3(_pred, _chan, L"")
	
	/// \endcond Internal

	/**
	*	\def SA_WARN(_pred, _chan, _dets)
	*
	*	\brief Sapphire Log "warning if" macro.
	*
	*	Helper macro to use Debug::Log warning.
	*
	*	\param[in] _pred	predicate of the Log. Output warnings on false.
	*	\param[in] _chan	Channel of the log.
	*	\param[in] _dets	String message of the log (optional).
	*/
	#define SA_WARN(...) __SA_SELECT_LOG_MACRO(__VA_ARGS__, __SA_WARN3(__VA_ARGS__), __SA_WARN2(__VA_ARGS__))
	//#define SA_WARN(...) __SA_SELECT_LOG_MACRO(__VA_ARGS__, __SA_WARN3, __SA_WARN2)(__VA_ARGS__)

	/**
	*	\def SA_ASSERT(_type, _chan, ...)
	*
	*	\brief Sapphire Assertion macro.
	*
	*	Helper macro to use Debug::Assert.
	*
	*	\param[in] _type		type of the exception.
	*	\param[in] _chan		Channel of the assert.
	*	\param[in] __VA_ARGS_	Additionnal args for exception (depends on _type).
	*/
	#define SA_ASSERT(_type, _chan, ...) { Sa::Debug::logger.Assert(__SA_CREATE_EXCEPTION(_type, _chan, ##__VA_ARGS__)); }

#else

	#define SA_LOG(...) {}

	#define SA_WARN(...) {}

	#define SA_ASSERT(...) {}

#endif
}

#endif // GUARD
// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_ILOG_GUARD
#define SAPPHIRE_CORE_ILOG_GUARD

#include <SA/Core/Debug/Log/LogBase.hpp>

namespace Sa
{
#if SA_LOGGING

	class ILog
	{
	public:
		virtual ~ILog() = default;

		const LogBase& GetBase() const;
	};

	template <typename StreamT>
	class ILogT : public ILog
	{
	public:
		virtual void Output(StreamT& _stream) const;

		/**
		*	\brief ToWString implementation
		*
		*	Convert this log to wstring.
		*
		*	\return this as a wstring.
		*/
		virtual std::wstring ToWString() const = 0;
	};

#endif
}

#include <SA/Core/Debug/Log/ILog.inl>

#endif // GUARD

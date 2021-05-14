// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_COUNTER_GUARD
#define SAPPHIRE_UTH_COUNTER_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Debug/Log/Log_Token.hpp>

namespace Sa::UTH
{
	struct Counter
	{
		/// Counter of success.
		uint32 success = 0;

		/// Counter of failure.
		uint32 failure = 0;

		/// Total count.
		uint32 Total() const;

		/// Update counter from predicate.
		void Increment(bool _pred);

		Counter& operator+=(const Counter& _rhs) noexcept;

		void AppendLog(Log_Token& _log) const;

		bool IsEmpty() const;
	};
}

#endif // GUARD

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Counter.hpp>

#include <UTH/Step.hpp>

namespace Sa::UTH
{
	uint32 Counter::Total() const
	{
		return success + failure;
	}

	void Counter::Increment(bool _pred)
	{
		if (_pred)
			++success;
		else
			++failure;
	}

	Counter& Counter::operator+=(const Counter& _rhs) noexcept
	{
		success += _rhs.success;
		failure += _rhs.failure;

		return *this;
	}

	void Counter::AppendLog(Log& _log) const
	{
		_log.AddToken(Step::TestNum);
		_log.AddString(std::to_wstring(Total()));

		if (failure)
		{
			_log.AddString(L" (");

			_log.AddToken(Step::Success);
			_log.AddString(std::to_wstring(success));

			_log.AddToken(Step::TestNum);
			_log.AddString(L"/");

			_log.AddToken(Step::Failure);
			_log.AddString(std::to_wstring(failure));

			_log.AddToken(Step::TestNum);
			_log.AddString(L")");
		}
	}

	bool Counter::IsEmpty() const
	{
		return success != 0 && failure != 0;
	}
}

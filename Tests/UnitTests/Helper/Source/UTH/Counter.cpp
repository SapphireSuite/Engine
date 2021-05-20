// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Counter.hpp>

#include <UTH/Step.hpp>

#include <SA/Core/Debug/ToString.hpp>

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

	bool Counter::IsEmpty() const
	{
		return success == 0 && failure == 0;
	}

	void Counter::AppendStr(StringToken& _str) const
	{
		_str.AppendToken(Step::TestNum);
		_str.AppendString(Sa::ToWString(Total()));

		if (failure)
		{
			_str.AppendString(L" (");

			_str.AppendToken(Step::Success);
			_str.AppendString(Sa::ToWString(success));

			_str.AppendToken(Step::TestNum);
			_str.AppendString(L"/");

			_str.AppendToken(Step::Failure);
			_str.AppendString(Sa::ToWString(failure));

			_str.AppendToken(Step::TestNum);
			_str.AppendString(L")");
		}
	}
}

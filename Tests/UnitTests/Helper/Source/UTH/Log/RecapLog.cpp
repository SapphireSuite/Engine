// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Log/RecapLog.hpp>
#include <UTH/Step.hpp>

namespace Sa::UTH
{
	StringToken RecapLog::ToStringToken() const
	{
		StringToken str;

		if (tests.empty())
			return str;

		str.AppendToken(Step::Exit);
		str.AppendString(L"---------- Test Recap ----------");
		str.AppendToken(Step::None);

		for (auto it = tests.cbegin(); it != tests.cend(); ++it)
		{
			str.EndOfLine();
			str.AppendString(it->ToStringToken().handle);
		}

		return str;
	}
}

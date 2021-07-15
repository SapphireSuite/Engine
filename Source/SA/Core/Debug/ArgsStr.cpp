// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/ArgsStr.hpp>

#include <Collections/Debug>

namespace Sa
{
#if SA_LOGGING

	ArgsStr::ArgsStr(const std::string& _paramNames)
	{
		Append(_paramNames);
	}


	void ArgsStr::Append(const std::string& _paramNames)
	{
		uint64 prevIndex = 0;

		while (true)
		{
			const uint64 commaIndex = _paramNames.find_first_of(',', prevIndex);
			const uint64 pthesisIndex = _paramNames.find_first_of('(', prevIndex);
			const uint64 chevIndex = _paramNames.find_first_of('<', prevIndex);

			// Default use comma index.
			uint64 index = commaIndex;

			// Parenthesis or chevron in string before comma.
			if ((pthesisIndex != uint64(-1) && pthesisIndex < commaIndex) || (chevIndex != uint64(-1) && chevIndex < commaIndex))
				index = _paramNames.find_first_of(',', _paramNames.find_first_of(')', prevIndex));

			params.push_back(Param{ _paramNames.substr(prevIndex, index) });

			if (index == uint64(-1))
				break;
			else
				prevIndex = index + 2; // remove comma + space.
		}
	}


	std::vector<ArgsStr::Param>* ArgsStr::operator->() noexcept
	{
		return &params;
	}

	const std::vector<ArgsStr::Param>* ArgsStr::operator->() const noexcept
	{
		return &params;
	}


	ArgsStr::Param& ArgsStr::operator[](uint32 _index)
	{
		SA_ASSERT(OutOfRange, Core, _index, 0u, static_cast<uint32>(params.size()));

		return params[_index];
	}

	const ArgsStr::Param& ArgsStr::operator[](uint32 _index) const
	{
		SA_ASSERT(OutOfRange, Core, _index, 0u, static_cast<uint32>(params.size()));
	
		return params[_index];
	}

#endif
}

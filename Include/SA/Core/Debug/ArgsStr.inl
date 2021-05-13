// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename... Args>
	ArgsStr::ArgsStr(const std::string& _paramNames, const Args&... _args)
	{
		GenerateParamStr(_paramNames, _args...);
	}

	/// \brief Generate Params from params' names and values.
	template <typename FirstT, typename... Args>
	void ArgsStr::GenerateParamStr(std::string _paramNames, const FirstT& _first, const Args&... _args)
	{
		const uint64 commaIndex = _paramNames.find_first_of(',');
		const uint64 pthesisIndex = _paramNames.find_first_of('(');
		const uint64 chevIndex = _paramNames.find_first_of('<');

		// Default use comma index.
		uint64 index = commaIndex;

		// Parenthesis or chevron in string before comma.
		if ((pthesisIndex != uint64(-1) && pthesisIndex < commaIndex) || (chevIndex != uint64(-1) && chevIndex < commaIndex))
			index = _paramNames.find_first_of(',', _paramNames.find_first_of(')'));

		params.push_back(Param{ _paramNames.substr(0u, index), ToString(_first) });

		// Recursive call for next params.
		if constexpr (sizeof...(_args) != 0u)
			GenerateParamStr(_paramNames.substr(index + 2), _args...);
	}
}

// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Log/TestLog.hpp>

#include <UTH/Step.hpp>
#include <UTH/Instance.hpp>

namespace Sa::UTH
{
	TestLog::TestLog(
		std::wstring&& _file,
		uint32 _line,
		std::string&& _function,
		std::string&& _result,
		bool _bResult,
		ArgsStr&& _params
	) noexcept :
		Log(_bResult ? LogLevel::Normal : LogLevel::Error),
		file{ std::move(_file) },
		line{ _line },
		function{ std::move(_function) },
		result{ std::move(_result) },
		bResult{ _bResult },
		params{ std::move(_params) }
	{
		const std::vector<Group>& groups = Intl::instance.GetGroups();

		for (auto it = groups.begin(); it != groups.end(); ++it)
		{
			groupTrace.AppendToken(Step::Group);
			groupTrace.AppendString(it->name);

			if (it + 1 != groups.end())
			{
				groupTrace.AppendToken(Step::Title);
				groupTrace.AppendString(L"/");
			}
		}
	}


	StringToken TestLog::ToStringToken() const
	{
		/**
		*	[SA-UTH] <Success/Failure> <func> -- <file>:<line>
		*	<param1_name>:
		*	<param1_value>
		*	<param2_name>:
		*	<param2_value>
		*/

		StringToken str;

		// Title.
		{
			str.AppendToken(Step::Title);

			str.AppendString(std::wstring(tabNum, '\t'));
			str.AppendString(L"[SA-UTH] ");

			if (bResult)
			{
				str.AppendToken(Step::Success);
				str.AppendString(L"Success ");
			}
			else
			{
				str.AppendToken(Step::Failure);
				str.AppendString(L"Failure ");
			}

			str.AppendToken(Step::None);
			str.AppendString(Sa::ToWString(function));

			if (!result.empty())
			{
				str.AppendToken(Step::Title);
				str.AppendString(L" == ");

				str.AppendToken(Step::None);
				str.AppendString(Sa::ToWString(result));
			}

			str.AppendToken(Step::Title);
			str.AppendString(L" -- " + file + L':' + Sa::ToWString(line));

			if (!bResult && !groupTrace.handle.empty())
			{
				str.AppendString(L"\tGroup: ");
				str.AppendString(groupTrace.handle);
			}

			str.AppendToken(Step::None);
		}

		// Params.
		if ((bResult && (verbosity & Verbosity::ParamsSuccess)) ||		// Should output params on success.
			(!bResult && (verbosity & Verbosity::ParamsFailure)))		// Should output params on failure.
		{
			for (auto it = params->begin(); it != params->end(); ++it)
			{
				if (verbosity & Verbosity::ParamsName)
				{
					str.EndOfLine(tabNum);
					str.AppendString(Sa::ToWString(it->name) + L':');
					str.EndOfLine(tabNum);
				}

				if (it->value.empty())
				{
					str.AppendString(L"-No debug string-\t");
					str.AppendToken(Step::ParamWarning);

					str.AppendString(L"Implement ToString() in class or UTH::ToString template specialization.");
					str.AppendToken(Step::None);
				}
				else
				{
					std::wstring vStr = Sa::ToWString(it->value);

					// Indent all '\n' in value string.
					{
						const std::wstring indentStr = std::wstring(tabNum, L'\t');
						size_t index = vStr.find(L'\n');

						while (index != std::string::npos)
						{
							vStr.insert(index + 1, indentStr);

							index = vStr.find(L'\n', index + indentStr.size() + 1);
						}
					}

					str.AppendString(vStr);
				}
			}
		}

		return str;
	}
}

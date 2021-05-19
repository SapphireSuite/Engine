// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Test.hpp>

#include <UTH/Instance.hpp>

#include <SA/Core/Debug/ToString.hpp>

namespace Sa::UTH
{
	Test::Test(
		const std::wstring& _file,
		uint32 _line,
		const std::string& _function,
		const std::string& _result,
		bool _bResult,
		ArgsStr&& _params
	) noexcept :
		file{ _file },
		line{ _line },
		function{ _function },
		result{ _result },
		bResult{ _bResult },
		params{ std::move(_params) }
	{
	}

	Log Test::MakeLog() const
	{
		/**
		*	[SA-UTH] <Success/Failure> <func> -- <file>:<line>
		*	<param1_name>:
		*	<param1_value>
		*	<param2_name>:
		*	<param2_value>
		*/

		Log log(file, line, function);

		log.AddToken(Step::Title);

		log.AddString(L"[SA-UTH] ");

		if (bResult)
		{
			log.AddToken(Step::Success);
			log.AddString(L"Success ");
		}
		else
		{
			log.AddToken(Step::Failure);
			log.AddString(L"Failure ");
		}

		log.AddToken(Step::None);
		log.AddString(Sa::ToWString(function));

		if (!result.empty())
		{
			log.AddToken(Step::Title);
			log.AddString(L" == ");

			log.AddToken(Step::None);
			log.AddString(Sa::ToWString(result));
		}

		log.AddToken(Step::Title);
		log.AddString(L" -- " + file + L':' + Sa::ToWString(line));

		log.AddToken(Step::None);

		if ((bResult && (verbosity & Verbosity::ParamsSuccess)) ||		// Should output params on success.
			(!bResult && (verbosity & Verbosity::ParamsFailure)))		// Should output params on failure.
		{
			for (auto it = params->begin(); it != params->end(); ++it)
			{
				if (verbosity & Verbosity::ParamsName)
				{
					log.EndOfLine();
					log.AddString(Sa::ToWString(it->name) + L':');
					log.EndOfLine();
				}

				if (it->value.empty())
				{
					log.AddString(L"-No debug string-\t");
					log.AddToken(Step::ParamWarning);

					log.AddString(L"Implement ToString() in class or UTH::ToString template specialization.");
					log.AddToken(Step::None);
				}
				else
				{
					std::wstring vStr = Sa::ToWString(it->value);

					// Indent all '\n' in value string.
					{
						const std::wstring indentStr = std::wstring(Intl::instance.GetGroupNum(), L'\t');
						size_t index = vStr.find(L'\n');

						while (index != std::string::npos)
						{
							vStr.insert(index + 1, indentStr);

							index = vStr.find(L'\n', index + indentStr.size() + 1);
						}
					}

					log.AddString(vStr);
				}
			}
		}

		return log;
	}
}
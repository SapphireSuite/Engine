// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <ctime>

#include <Core/Time/DateTime.hpp>

#include <Collections/Debug>

#if SA_WIN
#else

	#include <sys/stat.h>

#endif

namespace Sa
{
	DateTime::DateTime(uint8 _second,
		uint8 _minute,
		uint8 _hour,
		uint8 _day,
		uint8 _month,
		uint16 _year,
		uint8 _weekday
	) noexcept :
		second{ _second },
		minute{ _minute },
		hour{ _hour },
		day{ _day },
		month{ _month },
		year{ _year },
		weekday{ _weekday }
	{
	}

	DateTime::DateTime(const tm& _time) noexcept :
		second{ static_cast<uint8>(_time.tm_sec) },
		minute{ static_cast<uint8>(_time.tm_min) },
		hour{ static_cast<uint8>(_time.tm_hour) },
		day{ static_cast<uint8>(_time.tm_mday) },
		month{ static_cast<uint8>(_time.tm_mon + 1) },		// January is month 1.
		year{ static_cast<uint16>(_time.tm_year + 1900) },	// tm_year is the year since 1900.
		weekday{ static_cast<uint8>(_time.tm_wday) }
	{
	}


	const char8* DateTime::GetDayName() const
	{
		SA_ASSERT(OutOfRange, SA-Core, weekday, 0u, 6u, L"Invalid weekDay member!");

		return DateTime::sDays[weekday];
	}

	const char8* DateTime::GetMonthName() const
	{
		SA_ASSERT(OutOfRange, SA-Core, month, 1u, 12u, L"Invalid month member!");
		
		return DateTime::sMonths[month - 1];
	}


	DateTime DateTime::FileStats(const std::string _path)
	{
		struct stat backupStat;
		stat(_path.c_str(), &backupStat);

		tm qTime; // Queried time.

#if SA_WIN
		localtime_s(&qTime, &backupStat.st_mtime);
#else
		localtime_r(&backupStat.st_mtime, &qTime);
#endif

		return DateTime{ qTime };
	}


#if SA_LOGGING

	std::string DateTime::ToString() const
	{
		return Sa::ToString(month) + '.' +
			Sa::ToString(day) + '.' +
			Sa::ToString(year) + '-' +
			Sa::ToString(hour) + 'h' +
			Sa::ToString(minute) + 'm' +
			Sa::ToString(second) + 's';
	}

#endif
}

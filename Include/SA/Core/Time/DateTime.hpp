// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_DATE_TIME_GUARD
#define SAPPHIRE_CORE_DATE_TIME_GUARD

#include <string>

#include <SA/Config.hpp>

#include <SA/Core/Types/Char.hpp>
#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Debug/Config.hpp>

/**
*	\file DateTime.hpp
*
*	\brief \b Definition of Sapphire Engine \b Date time.
*
*	\ingroup Core_Time
*	\{
*/


namespace Sa
{
	/**
	*	\brief \e Time-relative struct which provide <b>date time service</b>.
	*/
	struct DateTime
	{
		/// Week days 3-char8 name.
		static constexpr const char8* sDays[7]{ "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

		/// Month 3-char8 name.
		static constexpr const char8* sMonths[12]{ "Jan", "Fev", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		/// second number [0, 59].
		uint8 second = 0;

		/// minute number [0, 59].
		uint8 minute = 0;

		/// hour number [0, 23].
		uint8 hour = 0;

		/// day of the month number [1, 31].
		uint8 day = 0;

		/// month number [1, 12].
		uint8 month = 0;

		/// Year number.
		uint16 year = 0;

		/// day number of the week [0, 6].
		uint8 weekday = 0;


		/// Default constructor.
		DateTime() = default;

		/**
		*	Default \e Value constructor.
		* 
		*	\param[in] _second	second values.
		*	\param[in] _minute	minute values.
		*	\param[in] _hour	hour values.
		*	\param[in] _day		day values.
		*	\param[in] _month	month values.
		*	\param[in] _year	year values.
		*	\param[in] _weekday	weekday values.
		*/
		DateTime(uint8 _second,
			uint8 _minute = 0_ui8,
			uint8 _hour = 0_ui8,
			uint8 _day = 0_ui8,
			uint8 _month = 0_ui8,
			uint16 _year = 0_ui16,
			uint8 _weekday = 0_ui8
		) noexcept;

		/**
		*	Value constructor from tm struct.
		* 
		*	\param[in] _time	tm values.
		*/
		DateTime(const struct tm& _time) noexcept;


		/**
		*	\brief \e Getter of day name.
		*
		*	\return 3 char8 of day name.
		*/
		const char8* GetDayName() const;

		/**
		*	\brief \e Getter of month name.
		*
		*	\return 3 char8 of month name.
		*/
		const char8* GetMonthName() const;
		
		
		/**
		*	\brief Query file date time stats at path.
		* 
		*	\param[in] _path	File path.
		* 
		*	\return DateTime stats of the file at path.
		*/
		static DateTime FileStats(const std::string _path);


#if SA_LOGGING

		/**
		*	\brief Convert to string to date-time format.
		* 
		*	\<month\>.\<day\>.\<year\>-\<hour\>h\<minute\>m\<second\>s
		*	Ex: 2/27/2021 at 12:07:43	=> "2.27.2021-12h07m43s"
		*
		*	\return this as a string.
		*/
		std::string ToString() const;

#endif
	};
}


/** \} */

#endif // GUARD

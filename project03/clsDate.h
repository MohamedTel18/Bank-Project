#pragma warning(disable : 4996)
#pragma once

#include <iostream>
#include "clsString.h";
#include <string>
#include <vector>

using namespace std;

class clsDate
{

private:

	short _Year;
	short _Month;
	short _Day;

public:

	static clsDate GetSystemDate()
	{
		//system date
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return clsDate(Day, Month, Year);
	}

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	clsDate(string Date)
	{
		vector <string> vString = clsString::Split("/", Date);

		_Day = stoi(vString[0]);
		_Month = stoi(vString[1]);
		_Year = stoi(vString[2]);
	}

	clsDate(int D,int M,int Y)
	{
		_Day = D;
		_Month = M;
		_Year = Y;
	}

	clsDate(int DaysFromBeginOfYear,int Y)
	{
		clsDate Date = GetDateFromDayOrderInYear(DaysFromBeginOfYear, Y);
		
		_Day = Date.Day;
		_Month = Date.Month;
		_Year = Date.Year;
	}

	void Print()
	{
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}

	void SetDay(int D)
	{
		_Day = D;
	}

	short GetDay()
	{
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(int M)
	{
		_Month = M;
	}

	short GetMonth()
	{
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(int Y)
	{
		_Year = Y;
	}

	short GetYear()
	{
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	static bool IsLeap(short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}

	static short NumberOfDaysInMonth(short Mn,short Yr)
	{
		short Arr[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Mn == 2 ? (IsLeap(Yr) ? 29 : 28) : Arr[Mn - 1]);
	}

	clsDate GetDateFromDayOrderInYear(short DaysFromBeginOfYear, short Y)
	{
		clsDate Date;
		
		Date.Day = 0;
		Date.Month = 1;
		Date.Year = Y;

		while (DaysFromBeginOfYear > 0)
		{
			if (DaysFromBeginOfYear > NumberOfDaysInMonth(Date.Month, Date.Year))
			{
				Date.Month++;
				DaysFromBeginOfYear -= NumberOfDaysInMonth(Date.Month, Date.Year);
			}

			else
			{
				Date.Day += DaysFromBeginOfYear;
				DaysFromBeginOfYear = 0;
			}
		}

		return Date;
	}

	static bool IsLastMonthInYear(short M)
	{
		return M == 12;
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}

		else
		{
			Date.Month++;

			if (Date.Day > NumberOfDaysInMonth(Date.Month, Date.Year))
				Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
		}

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	static string MonthString(short M)
	{
		string Arr[] = { "JAN","FEB","MAR","APR","MAY","JUNE","JUL",
		"AUG","SEP","OCT","NOV","DEC" };

		return Arr[M - 1];
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static void PrintMonthCalender(short M,short y)
	{
		short FirstDayOrder = DayOfWeekOrder(1, M, y);

		cout << "\n_______________" << MonthString(M) << "________________\n";
		cout << " SAT  SUN  MON  TUE  WED  THU  FRI\n";

		short i;
		for (i = 0; i < FirstDayOrder; i++)
			cout << "     ";
		
		for (short j = 1; j <= NumberOfDaysInMonth(M, y); j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

	}

	void PrintMonthCalender()
	{
		PrintMonthCalender(this->Month, this->Year);
	}

	static void PrintYearCalendar(clsDate Date)
	{
		cout << "\n__________________________________\n";
		cout << "\t  Calender-" << Date.Year;
		cout << "\n__________________________________\n";

		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalender(i, Date.Year);
		}
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(*this);
	}

	static bool ISValid(clsDate Date)
	{
		if (Date.Month > 12 || Date.Month < 1)
			return false;

		else
		{
			if (Date.Day<1 || Date.Day>NumberOfDaysInMonth(Date.Month, Date.Year))
			{
				return false;
			}

			else
			{
				return true;
			}
		}
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return Date1.Year > Date2.Year ? false : (Date1.Year == Date2.Year ?
			(Date1.Month > Date2.Month ? false : (Date1.Month == Date2.Month ?
				(Date1.Day > Date2.Day ? false : true) : true)) : true);
	}

	short IsValid()
	{
		return ISValid(*this) ? 1 : 0;
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year);
	}

	static bool IsLastMonth(short M)
	{
		return M == 12;
	}

	static clsDate AddOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	void AddOneDay()

	{
		*this = AddOneDay(*this);
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2)
	{
		int Days = 1;
		short SawpFlagValue = 1;

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return Days;
	}

	int GetDifferenceInDays(clsDate Date2)
	{
		return GetDifferenceInDays(*this, Date2);
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate());
	}

	static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year) && (Date1.Month == Date2.Month)
			&& (Date1.Day == Date2.Day);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2)) && (!IsDate1EqualToDate2(Date1, Date2));
	}

	static string GetSystemDateTimeString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + " - " +
			to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
	}

};
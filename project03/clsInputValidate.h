#pragma once

#include <iostream>
#include "clsDate.h";
#include "clsUtil.h";

using namespace std;

class clsInputValidate
{
	
public:

	static bool IsNumberBetween(int N, int From, int To)
	{
		if (From > To)
			clsUtil::Swap(From, To);

		return (From <= N) && (N <= To);
	}

	static bool IsNumberBetween(double N, double From, double To)
	{
		if (From > To)
			clsUtil::Swap(From, To);

		return (From <= N) && (N <= To);
	}

	static bool IsDateBetween(clsDate N, clsDate From, clsDate To)
	{
		if (!clsDate::IsDate1BeforeDate2(From, To))
			clsUtil::Swap(From, To);

		return (clsDate::IsDate1BeforeDate2(From, N) && clsDate::IsDate1AfterDate2(To, N))
			|| clsDate::IsDate1EqualToDate2(From, N) || clsDate::IsDate1EqualToDate2(To, N);
		
	}

	static int ReadIntNumber(string Message= "Invalid Number, Enter again:\n")
	{
		int x;

		cin >> x;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;
			cin >> x;
		}

		return x;
	}

	static double ReadDblNumber(string Message= "Invalid Number, Enter again:\n")
	{
		double x;

		cin >> x;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;
			cin >> x;
		}

		return x;
	}

	static int ReadIntNumberBetween(int N1, int N2, string Message = "Number is not within range, Enter again:\n")
	{
		int x = ReadIntNumber();

		while (!IsNumberBetween(x, N1, N2))
		{
			cout << Message;
			cin >> x;
		}

		return x;
	}

	static double ReadDblNumberBetween(double N1, double N2, string Message = "Number is not within range, Enter again:\n")
	{
		double x = ReadDblNumber();

		while (!IsNumberBetween(x, N1, N2))
		{
			cout << Message;
			cin >> x;
		}

		return x;
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::ISValid(Date);
	}

	static string ReadString()
	{
		string S;
		getline(cin >> ws, S);
		return S;
	}

};
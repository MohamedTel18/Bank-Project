#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "clsString.h"
#include <string>
using namespace std;

class clsCurrency
{

private:

	enum enType { emptyMode = 1, UpdateMode = 2 };

	enType _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	double _ExchangeRate;

	static clsCurrency _EmptyCurrency()
	{
		return clsCurrency(enType::emptyMode, "", "", "", 0);
	}

	static clsCurrency _ConvertLineToCurrency(string Line, string Del = "#//#")
	{
		vector <string> vString = clsString::Split(Del, Line);

		return clsCurrency(enType::UpdateMode, vString[1], vString[0], vString[2], stod(vString[3]));
	}

	static vector <clsCurrency> _LoadCurrencyDataFrom()
	{
		vector <clsCurrency> vCurrency;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vCurrency.push_back(_ConvertLineToCurrency(Line));
			}

			MyFile.close();
		}

		return vCurrency;
	}

	static string _ConvertCurrencyRecordToLine(clsCurrency Cur, string Del = "#//#")
	{
		string S;

		S = Cur.Country() + Del;
		S += Cur.CurrencyCode() + Del;
		S += Cur.CurrencyName() + Del;
		S += to_string(Cur.ExchangeRate);

		return S;
	}

	static void _SaveVectortoFile(vector <clsCurrency> vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsCurrency& i : vCurrencies)
			{
				string Line = _ConvertCurrencyRecordToLine(i);

				MyFile << Line << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> vCurrencies = _LoadCurrencyDataFrom();

		for (clsCurrency& i : vCurrencies)
		{
			if (i.CurrencyCode() == CurrencyCode())
			{
				i = *this;
			}
		}
		
		_SaveVectortoFile(vCurrencies);
	}

public:

	clsCurrency(enType Type, string Currencycode, string Country,
		string CurrencyName, double ExchangeRate)
	{
		_Mode = Type;
		_CurrencyCode = Currencycode;
		_Country = Country;
		_CurrencyName = CurrencyName;
		_ExchangeRate = ExchangeRate;
	}

	bool IsEmpty()
	{
		return _Mode == enType::emptyMode;
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void SetExchangeRate(double ExchangeRate)
	{
		_ExchangeRate = ExchangeRate;
	}

	double GetExchangeRate()
	{
		return _ExchangeRate;
	}

	__declspec(property(get = GetExchangeRate, put = SetExchangeRate))double ExchangeRate;

	static clsCurrency FindByCountry(string country)
	{
		vector <clsCurrency> vCurrency = _LoadCurrencyDataFrom();

		for (clsCurrency& i : vCurrency)
		{
			if (clsString::UpperAllString(i.Country()) == clsString::UpperAllString(country))
			{
				return i;
			}
		}

		return _EmptyCurrency();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		vector <clsCurrency> vCurrency = _LoadCurrencyDataFrom();

		for (clsCurrency& i : vCurrency)
		{
			if (clsString::UpperAllString(i.CurrencyCode()) == clsString::UpperAllString(CurrencyCode)) 
			{
				return i;
			}
		}

		return _EmptyCurrency();
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFrom();
	}

	void UpdateRate(float New)
	{
		_ExchangeRate = New;
		_Update();
	}

	static bool IsExist(string CurrCode)
	{
		clsCurrency Curr = clsCurrency::FindByCode(CurrCode);
		return !Curr.IsEmpty();
	}

	float ConvertToUsd(float Amount)
	{
		return Amount / ExchangeRate;
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUsd(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}


		return AmountInUSD * Currency2.ExchangeRate;
	}

};
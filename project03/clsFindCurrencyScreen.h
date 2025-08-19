#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsFindCurrencyScreen :protected clsScreen
{

private:



	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n___________________";
		cout << "\nCountry   : " << Currency.Country();
		cout << "\nCurr.Code    : " << Currency.CurrencyCode();
		cout << "\nCurr.Name   : " << Currency.CurrencyName();
		cout << "\nRate(1$)       : " << Currency.ExchangeRate;
		cout << "\n___________________\n";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (Currency.IsEmpty())
		{
			cout << "\nCurrency not Exist!\n";
		}

		else
		{
			cout << "\nCurrency Founded :-)\n";
			_PrintCurrency(Currency);
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{

		_DrawScreenHeader("\t Find Currency Screen");
 
		cout << "Find By: [1] Code or [2] Country? ";
		short Answer = 1;

		cin >> Answer;


		if (Answer == 1)
		{
			string CurrencyCode;
			cout << "\nPlease Enter CurrencyCode: ";
			CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
		}

		else
		{
			string D;
			cout << "please enter Country? ";
			D = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(D);
			_ShowResults(Currency);
		}
	}

};
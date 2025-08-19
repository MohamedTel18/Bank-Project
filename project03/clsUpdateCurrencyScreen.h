#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsUpdateCurrencyScreen : protected clsScreen
{

private:

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n_____________________________\n";
		cout << "\nCountry   : " << Currency.Country();
		cout << "\nCurr.Code    : " << Currency.CurrencyCode();
		cout << "\nCurr.Name   : " << Currency.CurrencyName();
		cout << "\nRate(1$)       : " << Currency.ExchangeRate;
		cout << "\n_____________________________\n";
	}

	static float _ReadUpdatedRate()
	{
		float N;

		cout << "\nUpdate Currency Rate :";
		cout << "\n_____________________________\n";
		cout << "enter New Rate :";
		cin >> N;

		return N;
	}

public:

	static void UpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\t  Update Currency Rate");

		string CurrCode;
		cout << "enter Currency Code : ";
		CurrCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsExist(CurrCode))
		{
			cout << "Currency doesn't exist, please enter another one? ";
			CurrCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrCode);
		_PrintCurrency(Currency);

		char Continue;
		cout << "Are u sure u want to update the rate of this currency?(y:yes)? ";
		cin >> Continue;

		if (toupper(Continue) == 'Y')
		{
			Currency.UpdateRate(_ReadUpdatedRate());

			cout << "\nCurrency Rate Updated Succefully :-)\n";
			_PrintCurrency(Currency);
		}

		else
			cout << "\nUpdate Rate was Fail!\n";
	}

};
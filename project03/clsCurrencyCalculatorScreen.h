#pragma once

#include <iostream>
#include"clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{

private:

	static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
	{

		cout << "\n" << Title << "\n";
		cout << "_____________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCode          : " << Currency.CurrencyCode();
		cout << "\nName          : " << Currency.CurrencyName();
		cout << "\nRate(1$) =    : " << Currency.ExchangeRate;
		cout << "\n_____________________________\n\n";

	}

	static clsCurrency _GetCurrency(string Messge)
	{
		string currCode;
		cout << Messge << endl;
		currCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsExist(currCode))
		{
			cout << "Currency Code doesn't exist, please enter another code? ";
			currCode = clsInputValidate::ReadString();
		}

		return clsCurrency::FindByCode(currCode);
	}

	static void _PrintCalculationResult(float Amount, clsCurrency Curr1, clsCurrency Curr2)
	{
		
		_PrintCurrencyCard(Curr1, "\nConvert From :");
		cout << Amount << " " << Curr1.CurrencyCode() << " = "
			<< Curr1.ConvertToUsd(Amount) << " USD.\n";

		if (Curr2.CurrencyCode() == "USD")
		{
			return;
		}

		cout << "Converting from USD ";
		_PrintCurrencyCard(Curr2, "\nTo:");

		float AmountInCurr2 = Curr1.ConvertToOtherCurrency(Amount, Curr2);
		cout << Amount << " " << Curr1.CurrencyCode() << " = "
			<< AmountInCurr2 << " " << Curr2.CurrencyCode() << endl;

	}

public:

	static void CurrencyCalculatorScreen()
	{
		char Continue;
		do
		{
			system("cls");
			_DrawScreenHeader("\t  Currency Calculator Screen");

			clsCurrency Currency1 = _GetCurrency("Please enter Currency1 Code: ");
			clsCurrency Currency2 = _GetCurrency("Please enter Currency2 Code: ");

			float Amount;
			cout << "\nplease enter Amount : ";
			cin >> Amount;

			_PrintCalculationResult(Amount, Currency1, Currency2);

			
			cout << "Would u performe another calculation? (Y:yes)";
			cin >> Continue;

		} while (toupper(Continue) == 'Y');
		
	}

};
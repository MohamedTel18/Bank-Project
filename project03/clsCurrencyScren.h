#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyScren :protected clsScreen
{

private:

	enum enCurrency {
		eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
		eCurrencyCalculator = 4, eMainMenue = 5
	};

	static short _ReadCurrencyMenueOption()
	{
		cout << setw(37) << left << "" << "\tChoose what do u want to do?[1-5]?  ";
		short N = clsInputValidate::ReadIntNumberBetween(1, 5);
		return N;
	}

	static void _GoBackToCurrencyMenue()
	{
		cout << "\nPress Any Key To go back to Currency menue...";

		system("pause>0");
		ShowCurrencyScreen();
	}

	static void  _PerformCurrencyMenueOption(enCurrency Cur)
	{
		switch (Cur)

		{

		case clsCurrencyScren::eListCurrencies:

			system("cls");
			_ListCurrenciesScreen();
			_GoBackToCurrencyMenue();
			break;

		case clsCurrencyScren::eFindCurrency:

			system("cls");
			_FindCurrencyScreen();
			_GoBackToCurrencyMenue();
			break;

		case clsCurrencyScren::eUpdateRate:

			system("cls");
			_UpdateRateScreen();
			_GoBackToCurrencyMenue();
			break;

		case clsCurrencyScren::eCurrencyCalculator:

			system("cls");
			_CurrencyCalculator();
			_GoBackToCurrencyMenue();
			break;
			
		case clsCurrencyScren::eMainMenue:
			break;

		}
	}

	static void _ListCurrenciesScreen()
	{
		clsCurrencyListScreen::ShowCurrenciesList();
	}

	static void _FindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _UpdateRateScreen()
	{
		clsUpdateCurrencyScreen::UpdateCurrencyRateScreen();
	}

	static void _CurrencyCalculator()
	{
		clsCurrencyCalculatorScreen::CurrencyCalculatorScreen();
	}

public:

	static void ShowCurrencyScreen()
	{
		system("cls");

		if (!CheckAccessRights(clsUser::pTransaction))
		{
			return;
		}

		_DrawScreenHeader("\t  Currency Exchange Main Screen");

		cout << setw(37) << left << "" << "\t==========================================\n";
		cout << setw(37) << left << "" << "\t\t  Currency Exchange Menue\n";
		cout << setw(37) << left << "" << "\t==========================================\n";
		cout << setw(37) << left << "" << "\t  [1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t  [2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t  [3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t  [4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t  [5] MainMenue.\n";
		cout << setw(37) << left << "" << "\t==========================================\n";

		_PerformCurrencyMenueOption((enCurrency)_ReadCurrencyMenueOption());

	}
};
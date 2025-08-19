#pragma once

#include <iostream>
#include "clsScreen.h"
#include <vector>
#include "clsCurrency.h"
#include <iomanip>

using namespace std;

class clsCurrencyListScreen : protected clsScreen
{

private:

    static void _PrintUserRecordLine(clsCurrency Currency)
    {

        cout << "| " << setw(35) << left << Currency.Country();
        cout << "| " << setw(5) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(15) << left << Currency.ExchangeRate;


    }

public:

    static void ShowCurrenciesList()
    {
        vector <clsCurrency> vCurrency = clsCurrency::GetCurrenciesList();
        string Title = "\t  Currency List Screen";
        string SubTitle = "\t    (" + to_string(vCurrency.size()) + ") Currencies.";

        _DrawScreenHeader(Title, SubTitle);

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(35) << "country";
        cout << "| " << left << setw(5) << "Curr. Code";
        cout << "| " << left << setw(45) << "Curr. Name";
        cout << "| " << left << setw(15) << "Exchange Rate";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrency.size() == 0)
            cout << "\t\t\t\tNo Curre,cies Available In the System!";
        else

            for (clsCurrency Currency : vCurrency)
            {

                _PrintUserRecordLine(Currency);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }


};
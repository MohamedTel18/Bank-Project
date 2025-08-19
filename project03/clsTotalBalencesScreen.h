#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsBankClient.h"
#include "clsUtil.h"

using namespace std;

class clsTotalBalencesScreen : protected clsScreen
{

private:

    static void _PrintClientRecordBAlenceLine(clsBankClient Client)
    {

        cout << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }

public:

    static void ShowTotalBalences()

    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t  Total Balences Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        double TotaleBalences = clsBankClient::GetTotalBalences();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {

                _PrintClientRecordBAlenceLine(Client);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "\t\t\t\tTotalBalences :" << TotaleBalences << endl;
        cout << "\t\t\t\t (" << clsUtil::NumberToText(TotaleBalences) << ")\n";

    }
};
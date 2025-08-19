#pragma once

#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsScreen.h"

using namespace std;

class clsTransferLog : protected clsScreen
{

private:

    static void _PrintClientRecordLine(clsBankClient::stTransfer Trns)
    {
        cout << "| " << setw(20) << left << Trns.Date;
        cout << "| " << setw(10) << left << Trns.AccountFrom;
        cout << "| " << setw(10) << left << Trns.AccountTo;
        cout << "| " << setw(15) << left << Trns.Amount;
        cout << "| " << setw(15) << left << Trns.NewBalenceFrom;
        cout << "| " << setw(15) << left << Trns.NewBalenceTo;
        cout << "| " << setw(10) << left << Trns.User;
    }

public:

    static void TransferLogList()
    {

        vector <clsBankClient::stTransfer> vClient = clsBankClient::LoadDataFromFile();
        string Title = "\t  Transfer Register Screen";
        string SubTitle = "\t    (" + to_string(vClient.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(20) << "Date";
        cout << "| " << left << setw(10) << "Acc.N From";
        cout << "| " << left << setw(10) << "Acc.N To";
        cout << "| " << left << setw(15) << "Amount";
        cout << "| " << left << setw(15) << "New Bal From";
        cout << "| " << left << setw(15) << "New Bal To";
        cout << "| " << left << setw(10) << "User Name";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClient.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsBankClient::stTransfer trns : vClient)
            {

                _PrintClientRecordLine(trns);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

};
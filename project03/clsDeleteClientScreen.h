#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{

private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

public:

    static void DeleteClient()
    {

        if (!CheckAccessRights(clsUser::pDeleteClient))
        {
            return;
        }

        _DrawScreenHeader("\t  Delete Client screen");

        string AccountNumber = "";
        cout << "please enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number is not founded, enter another account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char Continue;
        cout << "Are u sure want to delete this client (Y:yes)? ";
        cin >> Continue;

        if (toupper(Continue) == 'Y')
        {

            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfull :-)\n";

                _PrintClient(Client);
            }

            else
                cout << "\nError Client was not Deleted\n";
        }
    }

};


#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{

private:

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter First Name: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Pin Code: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balence: ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();

    }

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

	static void AddNewClient()
    {
        if (!CheckAccessRights(clsUser::pAddNewClient))
        {
            return;
        }

        clsScreen::_DrawScreenHeader("\t Add New Client Screen");

        string AccountNumber = "";

        cout << "please enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number is Already exist, enter another account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClient(AccountNumber);
        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResult SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::svSucceeded:

            cout << "Client Added Succuflly! :-)\n";
            _PrintClient(NewClient);
            break;

        case clsBankClient::svFaildEmptyObject:

            cout << "\nError account was not saved because it's Empty";
            break;

        case clsBankClient::svFaileAccountNumberExists:

            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
    }

};
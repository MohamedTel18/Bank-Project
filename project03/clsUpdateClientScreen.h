#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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


    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::pUpdateClient))
        {
            return;
        }

        _DrawScreenHeader("\t  pdate Client Screen");
        string AccountNumber = "";

        cout << "please enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number is not founded, enter another account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\nUpdate Client Info:";
        "\n___________________\n";
        _ReadClientInfo(Client1);


        clsBankClient::enSaveResult SaveResult;
        SaveResult = Client1.Save();

        switch (SaveResult)
        {

        case clsBankClient::svSucceeded:

            cout << "Client updated Succefully! :-)\n";
            _PrintClient(Client1);
            break;

        case clsBankClient::svFaildEmptyObject:

            cout << "\nError account was not saved because it's Empty";
            break;

        }

    }

};
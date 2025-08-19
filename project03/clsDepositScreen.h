#pragma once

#include <iostream>
#include"clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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

	static void ShowDepositscreen()
	{
		_DrawScreenHeader("\t  Deposit screen");

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

        double Amount = 0;
        cout << "\nplease enter deposit amount ? ";
        Amount = clsInputValidate::ReadDblNumber();

        char Continue;
        cout << "Would u confirme this transaction?(Y:yes)? ";
        cin >> Continue;

        if (toupper(Continue) == 'Y')
        {
            Client.Deposit(Amount);
            cout << "Amount Desposit Successfully!\n";
            cout << "New Balence : " << Client.AccountBalance << endl;
            
        }

        
	}

};


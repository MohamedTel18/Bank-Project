#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}


public:

	static void TransferScreen()
	{
		_DrawScreenHeader("\t  Transfer Screen.");

		string AccountNumber1, Accountnumber2;

		cout << "please enter Account Number to transfer From: ";
		AccountNumber1 = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber1))
		{
			cout << "Account Number doesn't exist, please enter anouther one? ";
			AccountNumber1 = clsInputValidate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber1);
		_PrintClient(Client1);

		cout << "please enter Account Number to transfer To: ";
		Accountnumber2 = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(Accountnumber2))
		{
			cout << "Account Number doesn't exist, please enter anouther one? ";
			Accountnumber2 = clsInputValidate::ReadString();
		}

		clsBankClient Client2 = clsBankClient::Find(Accountnumber2);
		_PrintClient(Client2);

		double TransferAmount;
		cout << "Enter Tranfer Amount? ";
		TransferAmount = clsInputValidate::ReadDblNumber();

		while (TransferAmount > Client1.AccountBalance)
		{
			cout << "Amount Exceeds the available Balence, Enter Anouther Amount? ";
			TransferAmount = clsInputValidate::ReadDblNumber();
		}

		char Continue;
		cout << "Would u Performe this transfer? (Y:yes)? ";
		cin >> Continue;

		if (toupper(Continue))
		{
			if (Client1.Transfer(TransferAmount, Client2, CurrentUser.UserName))
			{
				cout << "\nTransfer Done Successfully!\n";
				_PrintClient(Client1);
				_PrintClient(Client2);
			}

			else 
				cout << "\nTransfer Faild!\n";


		}


	}

};
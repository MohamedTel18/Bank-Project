#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionScreen.h"
#include "clsManageUsers.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyScren.h"

using namespace std;

class clsMainScreen : protected clsScreen
{

	enum enMainMenueOptions {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7, eLogInRegister = 8, eCurrency = 9, eExit = 10
	};

	static short _ReadMianMenueoption()
	{
		cout << setw(37) << left << "" << "\tChoose what do u want to do?[1-10]?  ";
		short N=clsInputValidate::ReadIntNumberBetween(1, 10);
		return N;
	}

	static void _GoBackToMainMenue()
	{
		cout << "\n\n\tPress Any Key to go back to main menue....";
		system("pause>0");
		ShowMainMenue();
	}

	static void _ClientsListScreen()
	{
		clsClientListScreen::ShowClientList();
	}

	static void _AddNewClientScreen()
	{
		clsAddNewClientScreen::AddNewClient();
	}

	static void _DeleteClientScreen()
	{
		//cout << "Delete Client Screen Will be soon...\n";

		clsDeleteClientScreen::DeleteClient();
	}

	static void _UpdateClientScreen()
	{
		//cout << "Update Client Screen Will be soon...\n";

		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _FindClientScreen()
	{
		//cout << "Find Client Screen Will be soon...\n";

		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _TransactionScreen()
	{
		//cout << "Transaction Screen Will be soon...\n";

		clsTransactionScreen::ShowTransactionScreen();
	}

	static void _ManageUsersScreen()
	{
		//cout << "Mange Users Screen Will be soon...\n";

		clsManageUsers::ShowMangeUsersScreen();
	}

	static void _LogOutScreen()
	{
		//cout << "Add New Client Screen Will be soon...\n";

		CurrentUser = clsUser::Find("", "");
	}

	static void _LoginRegisterScreen()
	{
		clsLoginRegisterScreen::LoginRegisterList();
	}

	static void _CurrencyScreen()
	{
		clsCurrencyScren::ShowCurrencyScreen();
	}

	static void _PerformeMainMenueOption(enMainMenueOptions MmO)
	{
		switch (MmO)

		{

		case clsMainScreen::eListClients:
			system("cls");
			_ClientsListScreen();
			_GoBackToMainMenue();
			break;

		case clsMainScreen::eAddNewClient:
			system("cls");
			_AddNewClientScreen();
			_GoBackToMainMenue();
			break;

		case clsMainScreen::eDeleteClient:
			system("cls");
			_DeleteClientScreen();
			_GoBackToMainMenue();
			break;

		case clsMainScreen::eUpdateClient:
			system("cls");
			_UpdateClientScreen();
			_GoBackToMainMenue();
			break;

		case clsMainScreen::eFindClient:
			system("cls");
			_FindClientScreen();
			_GoBackToMainMenue();
			break;

		case clsMainScreen::eShowTransactionsMenue:
			system("cls");
			_TransactionScreen();
			_GoBackToMainMenue();
			break;

		case clsMainScreen::eManageUsers:
			system("cls");
			_ManageUsersScreen();
			_GoBackToMainMenue();
			break;

		case clsMainScreen::eExit:
			system("cls");
			_LogOutScreen();
			break;

		case eLogInRegister:
			system("cls");
			_LoginRegisterScreen();
			_GoBackToMainMenue();
			break;

		case eCurrency:

			system("cls");
			_CurrencyScreen();
			_GoBackToMainMenue();
			break;

		}
	}

public:

	static void ShowMainMenue()
	{
		system("color 0F");
		system("cls");
		
		_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "\t==========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "\t==========================================\n";
		cout << setw(37) << left << "" << "\t  [1]Show Clients List.\n";
		cout << setw(37) << left << "" << "\t  [2]Add New Client.\n";
		cout << setw(37) << left << "" << "\t  [3]Delete Client.\n";
		cout << setw(37) << left << "" << "\t  [4]Update Client.\n";
		cout << setw(37) << left << "" << "\t  [5]Find Client.\n";
		cout << setw(37) << left << "" << "\t  [6]Transaction.\n";
		cout << setw(37) << left << "" << "\t  [7]Manage Users.\n";
		cout << setw(37) << left << "" << "\t  [8]Login Register.\n";
		cout << setw(37) << left << "" << "\t  [9]Currency Main.\n";
		cout << setw(37) << left << "" << "\t  [10]Log out.\n";
		cout << setw(37) << left << "" << "\t==========================================\n";
		_PerformeMainMenueOption((enMainMenueOptions)_ReadMianMenueoption());
	}


};
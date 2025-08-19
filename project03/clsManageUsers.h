#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsers : protected clsScreen
{

	enum enMainMenueOptions {
		eListUsers = 1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4,
		eFindUser = 5
	};

	static short _ReadMianMenueoption()
	{
		cout << setw(37) << left << "" << "\tChoose what do u want to do?[1-6]?  ";
		short N = clsInputValidate::ReadIntNumberBetween(1, 6);
		return N;
	}

	static void _GoBackToMangeUserMenue()
	{
		cout << "\nPress Any Key To go back to mange users menue....";

		system("pause>0");
		ShowMangeUsersScreen();
	}

	static void _UsersListScreen()
	{
		//cout << "Users List Screen Will be soon...";

		clsUsersListScreen::ShowUsersList();
	}

	static void _AddNewUserScreen()
	{
		//cout << "Add New User Screen Will be soon...";
		
		clsAddNewUserScreen::AddNewUser();
	}

	static void _DeleteUserScreen()
	{
		//cout << "Delete Client Screen Will be soon...\n";

		clsDeleteUserScreen::DeleteUserScreen();
	}

	static void _UpdateUserScreen()
	{
		//cout << "Update User Screen Will be soon...\n";

		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _FindUserScreen()
	{
		//cout << "Find User Screen Will be soon...\n";

		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformeMangeUsersMenueOption(enMainMenueOptions Mng)
	{
		switch (Mng)

		{

		case clsManageUsers::eListUsers:
			system("cls");
			_UsersListScreen();
			_GoBackToMangeUserMenue();
			break;

		case clsManageUsers::eAddUser:

			system("cls");
			_AddNewUserScreen();
			_GoBackToMangeUserMenue();
			break;

		case clsManageUsers::eDeleteUser:

			system("cls");
			_DeleteUserScreen();
			_GoBackToMangeUserMenue();
			break;

		case clsManageUsers::eUpdateUser:
			system("cls");
			_UpdateUserScreen();
			_GoBackToMangeUserMenue();
			break;

		case clsManageUsers::eFindUser:
			system("cls");
			_FindUserScreen();
			_GoBackToMangeUserMenue();
			break;

		}

	}

public:

	static void ShowMangeUsersScreen()
	{
		system("cls");

		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		_DrawScreenHeader("\t\tManage Users Screen");

		cout << setw(37) << left << "" << "\t==========================================\n";
		cout << setw(37) << left << "" << "\t\t\tManage Users Menue\n";
		cout << setw(37) << left << "" << "\t==========================================\n";
		cout << setw(37) << left << "" << "\t  [1] List Users.\n";
		cout << setw(37) << left << "" << "\t  [2] Add New User.\n";
		cout << setw(37) << left << "" << "\t  [3] Delete User.\n";
		cout << setw(37) << left << "" << "\t  [4] Update User.\n";
		cout << setw(37) << left << "" << "\t  [5] Find User.\n";
		cout << setw(37) << left << "" << "\t  [6] Main Menue.\n";
		cout << setw(37) << left << "" << "\t==========================================\n";
		_PerformeMangeUsersMenueOption((enMainMenueOptions)_ReadMianMenueoption());
	}
	

};
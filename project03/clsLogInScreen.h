#pragma once

#include <iostream>
#include "clsScreen.h"
#include "Global.h"
#include "clsMainScreen.h"

using namespace std;

class clsLogInScreen : protected clsScreen
{

private:

	static bool _LogIn()
	{
		string UserName;
		string Password;
		short Faild = 0;
		bool LogInfaild = false;

		do
		{

			if (LogInfaild)
			{
				Faild++;
				cout << "\nInValid User Name/Password\n";
				cout << "You have " << 3 - Faild << " Trys\n\n";
			}

			if (Faild == 3)
			{
				system("color 4F");
				cout << "You are Locked After 3 failed trails.\n\n";
				return false;
			}

			cout << "Enter User Name? ";
			cin >> UserName;

			cout << "Enter Password? ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);
			LogInfaild = CurrentUser.IsEmpty();

		} while (LogInfaild);

		CurrentUser.SaveUserToFile();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLogInScreen()
	{
		system("cls");
		_DrawScreenHeader("Log In Screen");
		return _LogIn();
	}

};
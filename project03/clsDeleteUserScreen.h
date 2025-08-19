#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{

private:

	static void _PrintUser(clsUser User)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermission     : " << User.Permission;
		cout << "\n___________________\n";
	}

public:

	static void DeleteUserScreen()
	{
		_DrawScreenHeader("\t Delete User");

		string UserName;
		cout << "please enter User Name? ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "UserName is not exist, enter another account Number : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Continue;
		cout << "would u Delete this user ?(y:yes)? ";
		cin >> Continue;

		if (toupper(Continue) == 'Y')
		{
			if (User.Delete())
			{
				cout << "User Deleted Succefully !";
				User = clsUser::GetEmptyUsrr();
				_PrintUser(User);
			}

			else
				cout << "Error Operation\n";
		}
	}


};
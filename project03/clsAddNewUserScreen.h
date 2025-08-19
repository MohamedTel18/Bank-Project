#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{

private:

    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter First Name: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter Last Name: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Pin Code: ";
        User.Password = clsInputValidate::ReadString();

        cout << "Enter Permission :\n";
        User.Permission = _RadPermission();

    }

    static void _PrintClient(clsUser User)
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

    static short _RadPermission()
    {
        short Per = 0;
        char Continue;


        cout << "\nDo u want to give Full access? (y:Yes) ";
        cin >> Continue;
        if (toupper(Continue) == 'Y')
            return -1;

        cout << "\n\nDo u want to give access to :\n ";

        cout << "Show Clients List ?(y:Yes) ";
        cin >> Continue;
        if (toupper(Continue) == 'Y')
            Per += 1;

        cout << "Add New Client ?(y:Yes) ";
        cin >> Continue;
        if (toupper(Continue) == 'Y')
            Per += 2;

        cout << "Delete Client ?(y:Yes) ";
        cin >> Continue;
        if (toupper(Continue) == 'Y')
            Per += 4;

        cout << "Update Client ?(y:Yes) ";
        cin >> Continue;
        if (toupper(Continue) == 'Y')
            Per += 8;

        cout << "Find Client ?(y:Yes) ";
        cin >> Continue;
        if (toupper(Continue) == 'Y')
            Per += 16;

        cout << "Transaction ?(y:Yes) ";
        cin >> Continue;
        if (toupper(Continue) == 'Y')
            Per += 32;

        cout << "MAnage Users ?(y:Yes) ";
        cin >> Continue;
        if (toupper(Continue) == 'Y')
            Per += 64;

        return Per;
    }

public:

    static void AddNewUser()
    {
        clsScreen::_DrawScreenHeader("\t Add New User Screen");

        string UserName = "";

        cout << "please enter User Name : ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName))
        {
            cout << "UserName is Already exist, enter another account Number : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewClient = clsUser::GetAddNewUser(UserName);
        _ReadUserInfo(NewClient);


        clsUser::enSaveResult SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsUser::svSucceeded:

            cout << "Client Added Succuflly! :-)\n";
            _PrintClient(NewClient);
            break;

        case clsUser::svFaildEmptyObject:

            cout << "\nError account was not saved because it's Empty";
            break;

        case clsUser::svFaileAccountNumberExists:

            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
    }

};
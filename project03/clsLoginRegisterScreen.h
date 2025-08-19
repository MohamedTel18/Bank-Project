#pragma once

#include <iostream>
#include "clsScreen.h"
#include <vector>
#include "clsBankClient.h"
#include <iomanip>

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{

private:

    static void _PrintClientRecordLine(clsUser::stUser Usr)
    {
        cout << "| " << setw(15) << left << Usr.Date;
        cout << "| " << setw(20) << left << Usr.UsrNm;
        cout << "| " << setw(12) << left << Usr.Pstruct;
        cout << "| " << setw(20) << left << Usr.Prm;
    }

public:

    static void LoginRegisterList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pLoginregister))
        {
            return;
        }


        vector <clsUser::stUser> vUser = clsUser::GetLogInRegister();
        string Title = "\t  Login Register Screen";
        string SubTitle = "\t    (" + to_string(vUser.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Date";
        cout << "| " << left << setw(20) << "User Name";
        cout << "| " << left << setw(12) << "Password";
        cout << "| " << left << setw(20) << "Permission";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vUser.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser::stUser User : vUser)
            {

                _PrintClientRecordLine(User);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
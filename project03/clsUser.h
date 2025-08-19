#pragma once

#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{

private:

	enum enType { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enType _Mode;
	short _Permession;
	string _Password;
	string _UserName;
	bool _MarkForDelete = false;

	static clsUser _GetClassInfo(string S, string Del)
	{
		vector <string> vString = clsString::Split("#//#", S);

		return clsUser(enType::UpdateMode, vString[0], vString[1], vString[2], vString[3],
			vString[4], clsUtil::DecryptText(vString[5], 3), stoi(vString[6]));
	}

	static vector <clsUser> _LoadDataFileTovector()
	{
		vector <clsUser> vUser;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vUser.push_back(_GetClassInfo(Line, "#//#"));
			}

			MyFile.close();
		}

		return vUser;
	}

	static string _ConvertUserRecordToLine(clsUser User, string Del = "#//#")
	{
		string S = "";

		S += User.FirstName + Del;
		S += User.LastName + Del;
		S += User.Email + Del;
		S += User.Phone + Del;
		S += User.UserName + Del;
		S += clsUtil::EncryptText(User.Password, 3) + Del;
		S += to_string(User.Permission);

		return S;
	}

	static clsUser _GetemptyUser()
	{
		return clsUser(enType::EmptyMode, "", "", "", "", "", "", 0);
	}

	static void _SaveVectorToFile(vector <clsUser> vUser)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsUser& i : vUser)
			{
				if (i._MarkForDelete == false)
				{
					string Line = _ConvertUserRecordToLine(i);

					MyFile << Line << endl;
				}

			}
		}

		MyFile.close();
	}

	void _Update()
	{
		vector <clsUser> vUser = _LoadDataFileTovector();

		for (clsUser& i : vUser)
		{
			if (i.UserName == _UserName)
			{
				i = *this;
			}
		}

		_SaveVectorToFile(vUser);
	}

	void _AddDataLineToFile(string L)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << L << endl;

			MyFile.close();
		}

	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserRecordToLine(*this));
	}

	string _UserRecordToline(string Del = "#//#")
	{
		string S = "";

		S = clsDate::GetSystemDateTimeString() + Del;
		S += _UserName + Del;
		S += _Password + Del;
		S += to_string(_Permession);

		return S;
	}

	struct stUser;
	static stUser _ConvertLineToLoginRecord(string Line, string Del = "#//#")
	{
		vector <string> vString = clsString::Split(Del, Line);

		stUser Usr;
		Usr.Date = vString[0];
		Usr.UsrNm = vString[1];
		Usr.Pstruct = vString[2];
		Usr.Prm = stod(vString[3]);

		return Usr;
	}

public:

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8,
		pFindClient = 16, pTransaction = 32, pManageUsers = 64, pLoginregister = 128
	};

	clsUser(enType Type, string FirstName, string LastName, string Email, string Phone,
		string UserName, string Password, short Permession) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Type;
		_Permession = Permession;
		_Password = Password;
		_UserName = UserName;
	}

	struct stUser
	{
		string Date;
		string UsrNm;
		string Pstruct;
		short Prm;
	};

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	string GetUserName()
	{
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName))string UserName;


	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword))string Password;


	void SetPermission(short Permession)
	{
		_Permession = Permession;
	}

	short GetPermission()
	{
		return _Permession;
	}

	__declspec(property(get = GetPermission, put = SetPermission))short Permission;

	static clsUser Find(string UserName)
	{
		vector <clsUser> vUser = _LoadDataFileTovector();

		for (clsUser& i : vUser)
		{
			if (i.UserName == UserName)
			{
				return i;
			}
		}

		return _GetemptyUser();
	}

	static clsUser Find(string UserName, string Password)
	{
		vector <clsUser> vUser = _LoadDataFileTovector();

		for (clsUser& i : vUser)
		{
			if (i.UserName == UserName && i.Password == Password)
			{
				return i;
			}
		}

		return _GetemptyUser();
	}

	static bool IsUserExist(string UserName)
	{
		vector <clsUser> vUser = _LoadDataFileTovector();

		for (clsUser& i : vUser)
		{
			if (i.UserName == UserName)
			{
				return true;
			}
		}

		return false;
	}

	enum enSaveResult { svSucceeded = 1, svFaildEmptyObject = 2, svFaileAccountNumberExists = 3 };

	enSaveResult Save()
	{
		switch (_Mode)

		{

		case clsUser::EmptyMode:

			return svFaildEmptyObject;
			break;

		case clsUser::UpdateMode:

			_Update();
			return svSucceeded;
			break;

		case clsUser::AddNewMode:

			if (IsUserExist(_UserName))
				return svFaileAccountNumberExists;

			else
			{
				_Mode = enType::UpdateMode;
				_AddNew();
				return svSucceeded;
			}

			break;

		}
	}

	bool Delete()
	{
		vector <clsUser> vUser = _LoadDataFileTovector();

		for (clsUser& i : vUser)
		{
			if (i.UserName == _UserName)
			{
				i._MarkForDelete = true;
				break;
			}
		}

		_SaveVectorToFile(vUser);
		*this = _GetemptyUser();

		return true;
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadDataFileTovector();
	}

	static clsUser GetAddNewUser(string Username)
	{
		return clsUser(enType::AddNewMode, "", "", "", "", Username, "", 0);
	}

	static clsUser GetEmptyUsrr()
	{
		return clsUser(enType::EmptyMode, "", "", "", "", "", "", 0);
	}

	bool IsEmpty()
	{
		return !IsUserExist(_UserName);
	}

	bool CheckAccessPermission(enPermissions Per)
	{
		if (this->Permission == -1)
			return true;
		
		short K = this->Permission & Per;
		if (K == Per)
			return true;

		else
			return false;
	}

	void SaveUserToFile()
	{
		string Line = _UserRecordToline();
		fstream MyFile;
		MyFile.open("UserRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << Line << endl;

			MyFile.close();
		}
	}

	static vector <stUser> GetLogInRegister()
	{
		vector <stUser> vUser;

		fstream MyFile;
		MyFile.open("UserRegister.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vUser.push_back(_ConvertLineToLoginRecord(Line));
			}


			MyFile.close();
		}

		return vUser;
	}
};
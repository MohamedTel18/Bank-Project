#pragma once

#include <iostream>
#include "clsPerson.h";
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h";

using namespace std;

class clsBankClient :public clsPerson
{

private:

	enum enType { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enType _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _FillClientObject(string S, string Del = "#//#")
	{
		vector <string> vString = clsString::Split(Del, S);

		return clsBankClient(enType::UpdateMode, vString[0], vString[1], vString[2], vString[3],
			vString[4], vString[5], stod(vString[6]));
	}

	static vector <clsBankClient> _FillVectorObject()
	{
		vector <clsBankClient> vClient;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vClient.push_back(_FillClientObject(Line));
			}


			MyFile.close();
		}

		return vClient;
	}

	static clsBankClient _EmptyClient()
	{
		return clsBankClient(enType::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _clsClientToString(clsBankClient Client, string Del = "#//#")
	{
		string S;

		S = Client.FirstName + Del;
		S = S + Client.LastName + Del;
		S = S + Client.Email + Del;
		S = S + Client.Phone + Del;
		S = S + Client.AccountNumber() + Del;
		S = S + Client.PinCode + Del;
		S += to_string(Client.AccountBalance);

		return S;
	}

	static void _SaveVectorToFile(vector <clsBankClient> _vClient)
	{
		fstream Myfile;
		Myfile.open("Clients.txt", ios::out);

		if (Myfile.is_open())
		{

			for (clsBankClient& i : _vClient)
			{
				if (i._MarkedForDelete == false)
				{
					string Line = _clsClientToString(i);

					Myfile << Line << endl;
				}
			}

			Myfile.close();
		}
	}
	
	void _Update()
	{
		vector <clsBankClient> _vClient = _FillVectorObject();

		for (clsBankClient& i : _vClient)
		{
			if (i.AccountNumber() == AccountNumber())
			{
				i = *this;
				break;
			}
		}

		_SaveVectorToFile(_vClient);
	}

	void _AddDataLineToFile(string L)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << L << endl;

			MyFile.close();
		}

	}

	void _AddNew()
	{
		_AddDataLineToFile(_clsClientToString(*this));
	}

	string _TransferRecordToFile(float Amount, clsBankClient AccountTo, string UserName, string Del = "#//#")
	{
		string S;

		S = clsDate::GetSystemDateTimeString() + Del;
		S += _AccountNumber + Del;
		S += AccountTo.AccountNumber() + Del;
		S += to_string(Amount) + Del;
		S += to_string(_AccountBalance) + Del;
		S += to_string(AccountTo.AccountBalance) + Del;
		S += UserName;

		return S;
	}

	void _RegisterTransferLog(float Amount, clsBankClient AccountTo, string UserName)
	{
		string Line = _TransferRecordToFile(Amount, AccountTo, UserName);
		fstream MyFile;
		MyFile.open("RegisterTransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;

			MyFile.close();
		}
	}

	struct stTransfer;
	static stTransfer _ConvertLineToTransRecord(string Line, string Del = "#//#")
	{
		vector <string> vSting = clsString::Split(Del, Line);
		stTransfer Trns;

		Trns.Date = vSting[0];
		Trns.AccountFrom = vSting[1];
		Trns.AccountTo = vSting[2];
		Trns.Amount = stod(vSting[3]);
		Trns.NewBalenceFrom = stod(vSting[4]);
		Trns.NewBalenceTo = stod(vSting[5]);
		Trns.User = vSting[6];

		return Trns;
	}

public:

	clsBankClient(enType Type, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PIN, double Balence) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_AccountNumber = AccountNumber;
		_PinCode = PIN;
		_AccountBalance = Balence;
		_Mode = Type;
	}

	struct stTransfer
	{
		string Date;
		string AccountFrom;
		string AccountTo;
		double Amount;
		double NewBalenceFrom;
		double NewBalenceTo;
		string User;
	};

	bool IsEmpty()
	{
		return _Mode == enType::EmptyMode;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPIN(string PIN)
	{
		_PinCode = PIN;
	}

	string GetPIN()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPIN, put = SetPIN))string PinCode;


	void SetBalence(double Balence)
	{
		_AccountBalance = Balence;
	}

	double GetBalence()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetBalence, put = SetBalence))double AccountBalance;

	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient> vClient = _FillVectorObject();

		for (clsBankClient& i : vClient)
		{
			if (i.AccountNumber() == AccountNumber)
			{
				return i;
			}
		}

		return _EmptyClient();
	}

	static clsBankClient Find(string AccountNumber, string Pin)
	{
		vector <clsBankClient> vClient = _FillVectorObject();

		for (clsBankClient& i : vClient)
		{
			if (i.AccountNumber() == AccountNumber && i.PinCode == Pin)
			{
				return i;
			}
		}

		return _EmptyClient();
	}

	static bool IsClientExist(string AN)
	{
		clsBankClient Client1 = clsBankClient::Find(AN);

		return !Client1.IsEmpty();
	}

	enum enSaveResult { svSucceeded = 1, svFaildEmptyObject = 2, svFaileAccountNumberExists = 3 };

	enSaveResult Save()
	{
		switch (_Mode)

		{

		case clsBankClient::EmptyMode:

			return svFaildEmptyObject;
			break;

		case clsBankClient::UpdateMode:

			_Update();
			return svSucceeded;
			break;

		case clsBankClient::AddNewMode:

			if (IsClientExist(_AccountNumber))
				return svFaileAccountNumberExists;

			else
			{
				_AddNew();
				_Mode = clsBankClient::UpdateMode;
				return svSucceeded;
			}
			break;

		}
	}

	static clsBankClient GetAddNewClient(string AN)
	{
		return clsBankClient(enType::AddNewMode, "", "", "", "", AN, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> vClient = _FillVectorObject();
		
		for (clsBankClient& i : vClient)
		{
			if (i.AccountNumber() == _AccountNumber)
			{
				i._MarkedForDelete = true;
				break;
			}
		}
		_SaveVectorToFile(vClient);
		*this = _EmptyClient();

		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _FillVectorObject();
	}

	static double GetTotalBalences()
	{
		double Totale = 0;
		vector <clsBankClient> vClients = _FillVectorObject();

		for (clsBankClient& i : vClients)
		{
			Totale += i.AccountBalance;
		}

		return Totale;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}


	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
		}

	}

	bool Transfer(float Amount,clsBankClient& AccountTo,string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		AccountTo.Deposit(Amount);
		_RegisterTransferLog(Amount, AccountTo, UserName);
	}

	static vector <stTransfer> LoadDataFromFile()
	{
		vector <stTransfer> vTrans;
		fstream MyFile;
		MyFile.open("RegisterTransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string line;

			while (getline(MyFile, line))
			{
				vTrans.push_back(_ConvertLineToTransRecord(line));
			}

			MyFile.close();
		}

		return vTrans;
	}

};
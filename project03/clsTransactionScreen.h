#pragma once

#include <iostream>
#include"clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalencesScreen.h"
#include "clsTransfScreen.h"
#include "clsTransferLog.h"

using namespace std;

class clsTransactionScreen :protected clsScreen
{

private:

	enum enTransaction {
		eDeposit = 1, eWithdraw = 2, eShowTotalBalences = 3,
		eTransfer = 4, eTransferLog = 5, eShowMainMenue = 6
	};

	static short _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "\tChoose what do u want to do?[1-6]?  ";
		short N = clsInputValidate::ReadIntNumberBetween(1, 6);
		return N;

	}

	static void _GoBackToTransactionMenue()
	{
		cout << "\nPress Any Key To go back to transaction menue...";

		system("pause>0");
		ShowTransactionScreen();
	}

	static void _ShowDepositScreen()
	{
		//cout << "Deposit Screen will be soon.....\n";

		clsDepositScreen::ShowDepositscreen();
	}

	static void _ShowWithdrawScreen()
	{
		//cout << "WithDraw Screen will be soon.....\n";

		clsWithdrawScreen::ShowDepositscreen();
	}

	static void _ShowTotalBalencesScreen()
	{
		//cout << "Total Balences Screen will be soon.....\n";

		clsTotalBalencesScreen::ShowTotalBalences();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::TransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLog::TransferLogList();
	}

	static void _PerformTransactionsMenueOption(enTransaction Trns)
	{
		switch (Trns)

		{

		case clsTransactionScreen::eDeposit:

			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionMenue();
			break;

		case clsTransactionScreen::eWithdraw:

			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionMenue();
			break;

		case clsTransactionScreen::eShowTotalBalences:

			system("cls");
			_ShowTotalBalencesScreen();
			_GoBackToTransactionMenue();
			break;

		case clsTransactionScreen::eShowMainMenue:
			//clsMainScreen::ShowMainMenue();
			break;

		case clsTransactionScreen::eTransfer:

			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionMenue();
			break;

		case clsTransactionScreen::eTransferLog:

			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionMenue();
			break;

		}

	}


public:

	static void ShowTransactionScreen()
	{
		system("cls");

		if (!CheckAccessRights(clsUser::pTransaction))
		{
			return;
		}

		_DrawScreenHeader("\t  Transaction Screen");

		cout << setw(37) << left << "" << "\t==========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transaction Menue\n";
		cout << setw(37) << left << "" << "\t==========================================\n";
		cout << setw(37) << left << "" << "\t  [1] Deposit.\n";
		cout << setw(37) << left << "" << "\t  [2] WithDraw.\n";
		cout << setw(37) << left << "" << "\t  [3] Total Balences.\n";
		cout << setw(37) << left << "" << "\t  [4] Transfer.\n";
		cout << setw(37) << left << "" << "\t  [5] Transfer Log List.\n";
		cout << setw(37) << left << "" << "\t  [6] MainMenue.\n";
		cout << setw(37) << left << "" << "\t==========================================\n";

		_PerformTransactionsMenueOption((enTransaction)_ReadTransactionsMenueOption());
	}

};
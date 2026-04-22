#pragma once

#include <iostream>
#include "clsInputVaildate.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsDepositeClient.h"
#include "clsWithDrawScreen.h"
#include "clsTotalBalance.h"
#include "clsTransfer.h"
#include "clsShowList.h"

using namespace std;


class clsTransactionScreen:protected clsScreen
{
private:
	enum _enTransaction{eDeposite=1,eWithDraw=2,eTotalBalance=3
		,eTransfer=4,eListTransfer=5,eMainMenu=6};
	static void Deposite()
	{

	}
	static void WithDraw()
	{
		//cout << "\nWithDraw Here ";
		clsWithDrawScreen::ShowWithdrawScreen();
	}
	static void TotalBalance()
	{
		//cout << "\nTotal Balance Here ";
		clsTotalBalance::ShowTotalBalances();
	}
	static void _Transfer()
	{
		clsTransfer::ShowTransferSreen();
	}
	static void _TransferLog()
	{
		clsShowList::ShowTransferLogScreen();
	}
	static void OperateProcessingOfTransaction(_enTransaction Transaction)
	{
		

		switch (Transaction)
		{
		case _enTransaction::eDeposite:
		{
			system("cls");
			Deposite();
			_MainMenuOfTransaction();
			break;
		}
		case _enTransaction::eWithDraw:
		{
			system("cls");
			WithDraw();
			_MainMenuOfTransaction();
			break;
		}
		case _enTransaction::eTotalBalance:
		{
			system("cls");
			TotalBalance();
			cout << "\nPress Any Botton ";
			system("pause>0");
			_MainMenuOfTransaction();
			break;
		}
		case _enTransaction::eTransfer:
		{
			system("cls");
			_Transfer();
			cout << "\nPress Any Botton ";
			system("pause>0");
			_MainMenuOfTransaction();
			break;
		}
		case _enTransaction::eListTransfer:
		{
			system("cls");
			_TransferLog();
			cout << "\nPress Any Botton ";
			system("pause>0");
			_MainMenuOfTransaction();
			break;
		}
		case _enTransaction::eMainMenu:
		{
			system("cls");
			//cout << "\nMainMenu";

			break;
		}
		

		}
		

	}
	static void _MainMenuOfTransaction()
	{
		system("cls");
		cout << "\n\t\t\t\t\t==========================================\n";
		cout << "\n\t\t\t\t\t\t Transactions Menu \n";
		cout << "\n\t\t\t\t\t==========================================";
		cout << "\n\t\t\t\t\t[1]  Deposite";
		cout << "\n\t\t\t\t\t[2]  WithDraw";
		cout << "\n\t\t\t\t\t[3]  Total Balance";
		cout << "\n\t\t\t\t\t[4]  Transfer";
		cout << "\n\t\t\t\t\t[5]  Transfer Log ";
		cout << "\n\t\t\t\t\t[6]  MainMenu : ";
		cout << "\n\t\t\t\t\t==========================================";
		cout << "\n\t\t\t\t\tChoose what do you want to do? [1 to 5]?";
		int choice = clsInputVaildate::ReadIntBetween(1, 6);
		OperateProcessingOfTransaction((_enTransaction)choice);
	}
public:
	static void ShowTransactionScreen()
	{
		if (!CheckAccessRigths(clsUser::enPermission::pTransactions))
		{
			return;
		}
		_DrawScreenHeader("\t Transaction Screen");
		_MainMenuOfTransaction();
	}
};


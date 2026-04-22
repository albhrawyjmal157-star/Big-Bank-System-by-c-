#pragma once
#include "clsUser.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputVaildate.h"
#include<string>
#include <fstream>
#include "clsDate.h"

class clsTransfer : protected clsScreen
{
private:

	static void _FillDataFile(string Line)
	{
		fstream MyFile;
		MyFile.open("Transfer.txt", ios::app | ios::out);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}
	static string _ConvertLineToData(clsBankClient Client1,clsBankClient Client2
	,float Amount,string Seporitor="#//#")
	{
		string Data = "";
		Data += clsDate::GetDateAndTimeString() + Seporitor;
			Data += Client1.GetAccountNumber() + Seporitor;
			Data += Client2.GetAccountNumber() + Seporitor;
		Data += to_string(Amount) + Seporitor;
		Data += to_string(Client1.AccountBalance) + Seporitor;
		Data += to_string(Client2.AccountBalance) + Seporitor;
		Data += CurrentUser.GetUserName();
		return Data;
	}
public:
	static void ShowTransferSreen()
	{

		string AccountNumber1;
		string AccountNumber2;
		double Amount;
		char Answer = 'n';

		clsScreen::_DrawScreenHeader("\nTransfer Screen");

		cout << "\nPlease Enter AccountNumber to transfer from : ";
		cin >> AccountNumber1;
		

		while (!clsBankClient::IsClientExists(AccountNumber1))
		{
			cout << "\nPlease Enter AccountNumber to transfer from : ";
			cin >> AccountNumber2;
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber1);
		clsBankClient::PrintShort(Client1);

		//###############################################
		cout << "\nPlease Enter another AccountNumber to transfer from : ";
		cin >> AccountNumber2;


		while (!clsBankClient::IsClientExists(AccountNumber2))
		{
			cout << "\nPlease Enter another AccountNumber to transfer from : ";
			cin >> AccountNumber2;
		}
		
		clsBankClient Client2 = clsBankClient::Find(AccountNumber2);
		clsBankClient::PrintShort(Client2);

		cout << "\nEnter Transfer Amount : ";
		Amount = clsInputVailddate::ReadDoubleNumber();

		if (Amount > Client1.GetAccountBalance())
		{
			cout << "\namount Exceeds the aviable balance , Enter another Amount ";
			Amount = clsInputVailddate::ReadDoubleNumber();
		}

		cout << "\nAre You want to perfrom this operation (y,n)";
		cin >> Answer;
		
		if (Answer == 'y' || Answer == 'Y')
		{
			Client1.Withdraw(Amount);
			Client2.Deposite(Amount);
			cout << "\nTransfer Done Successfully ";
			
			_FillDataFile(_ConvertLineToData(Client1,Client2,Amount));
			clsBankClient::PrintShort(Client1);
			clsBankClient::PrintShort(Client2);
		}



	}
};


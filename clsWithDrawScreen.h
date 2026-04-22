#pragma once
#include <iostream>
#include "clsInputVaildate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsWithDrawScreen :protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card: \n";
		cout << "\n------------------------------";
		cout << "\nFirst Name        : " << Client.FirstName;
		cout << "\nLast Name         : " << Client.LastName;
		cout << "\nFull Name         : " << Client.FullName();
		cout << "\nEmail             : " << Client.Email;
		cout << "\nPhone             : " << Client.Phone;
		cout << "\nAcc. Number       : " << Client.GetAccountNumber();
		cout << "\nPassword          : " << Client.GetPincode();
		cout << "\nBalance           : " << Client.GetAccountBalance();
		cout << "\n------------------------------\n";
	}

public:
	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t Withdraw Screen ");
		string AccountNumber = "";
		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputVailddate::ReadString();
		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			cout << "\nAccount number is Not Exisat , choose another one: ";
			AccountNumber = clsInputVailddate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		cout << "\nPlease Enter withDraw Amount: ";
		float amount = clsInputVailddate::ReadDoubleNumber();

		char answer = 'n';
		cout << "\nAre You Sure To withDraw (y,n)";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			if (Client.AccountBalance < amount)
			{
				cout << "\nThe Balance Doesn't enugth ";
			}
			else
			{
				Client.Withdraw(amount);
				cout << "\nThe Processing Of Deposite Is Sueccsully";
				cout << "\nNew Balance : " << Client.GetAccountBalance();
			}
		}
		else
		{
			cout << "\nYou Are Cancelled The Older . ";
		}
		cout << "\n\nPress Any Botton To Continue ";
		system("pause>0");
	}
};


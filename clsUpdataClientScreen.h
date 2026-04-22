#pragma once

#include <iostream>
#include "clsInputVaildate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;


class clsUpdataClientScreen : clsScreen
{
private :
	static void ReadClientInfo(clsBankClient& Client)

	{
		cout << "\nEnter First Name: ";
		Client.FirstName = clsInputVaildate::ReadString();
		cout << "\nEnter Last Name: ";
		Client.LastName = clsInputVaildate::ReadString();
		cout << "\nEnter Email: ";
		Client.Email = clsInputVaildate::ReadString();
		cout << "\nEnter Phone: ";
		Client.Phone = clsInputVaildate::ReadString();
		cout << "\nEnter Pincode: ";
		Client.Pincode = clsInputVaildate::ReadString();
		cout << "\nEnter Account Balane: ";
		Client.AccountBalance = clsInputVaildate::ReadDoubleNumber();

	}
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

public :
	static void ShowUpdataClientScreen()
	{
		if (!CheckAccessRigths(clsUser::enPermission::UpdateClient))
		{
			return;
		}

		_DrawScreenHeader("\t Updata Client Screen ");
		string AccountNumber = "";
		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputVaildate::ReadString();
		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
				AccountNumber = clsInputVaildate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);


		char anwser = 'n';

		cout << "\nDo you want to update Data Of Client (y,n) ";
		cin >> anwser;

		if (anwser=='y' || anwser=='Y')
		{
			cout << "\nUpdate Client Info: ";
			cout << "\n---------------------\n";

			ReadClientInfo(Client1);

			clsBankClient::enSaveResult SaveResult;

			SaveResult = Client1.Save();

			switch (SaveResult)
			{
			case clsBankClient::enSaveResult::svSuccessed:
			{
				cout << "\nAccount Apdated Successsfully :-)\n";
				_PrintClient(Client1);
				break;
			}

			case clsBankClient::enSaveResult::svFailEmptyobject:
			{
				cout << "\nError account was not saved because it's Empty";
				break;
			}
			}
		}
	}

};


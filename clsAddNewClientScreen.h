#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputVaildate.h"
using namespace std;


class clsAddNewClientScreen : protected clsScreen
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
public:
	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRigths(clsUser::enPermission::pAddNewClient))
		{
			return;
		}

		_DrawScreenHeader(" \tAdd New Client Screen ");
		string AccountNumber = "";
		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputVaildate::ReadString();
		while (clsBankClient::IsClientExists(AccountNumber))
		{
			cout << "\nAccount number is Exisat , choose another one: ";
			AccountNumber = clsInputVaildate::ReadString();
		}

		clsBankClient Client = clsBankClient::GetAddNewClientObject(AccountNumber);

		ReadClientInfo(Client);

		clsBankClient::enSaveResult SaveResult;
		SaveResult = Client.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResult::svSuccessed:
		{
			cout << "\nAccount Added Successsfully :-)\n";
			cout << "\n\n";
			_PrintClient(Client);
			break;
		}

		case clsBankClient::enSaveResult::svFailEmptyobject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		case clsBankClient::enSaveResult::FaildAccountNumber:
			cout << "\nError Account Number Is Exists ";
			break;
		}
	}
};


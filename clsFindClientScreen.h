#pragma once

#include <iostream>
#include <fstream>
#include "clsBankClient.h"
#include "clsInputVaildate.h"
#include "clsScreen.h"

using namespace std;


class clsFindClientScreen : protected clsScreen
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
	
public :

	static void ShowFindClientScreen()
	{

		if (!CheckAccessRigths(clsUser::enPermission::pFindClient))
		{
			return;
		}

		_DrawScreenHeader("\t Find Client Screen ");
		string AccountNumber = "";
		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputVaildate::ReadString();
		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputVaildate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		if (!Client1.IsEmpty())
		{
			cout << "\n Client Found ";
			_PrintClient(Client1);

		}
		else
		{
			cout << "\n Client Not Found ";
		}



	}
	
};


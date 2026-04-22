#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputVaildate.h"

using namespace std;


class clsDeleteClientScreen : protected clsScreen
{
private :
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
	static void DeleteClient()
	{
		if (!CheckAccessRigths(clsUser::enPermission::pDeleteClient))
		{
			return;
		}


		_DrawScreenHeader("\tDelete Client Screen");
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

		char answer = 'n';
		cout << "\nDo You Want to Delete Client (y,n): ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			if (Client1.Delete())
			{
				cout << "\nClient Deleted Successfully ";
				_PrintClient(Client1);

			}
			else
			{
				cout << "\nError Client Doesn't Deleted ";
			}
		}


	}

};


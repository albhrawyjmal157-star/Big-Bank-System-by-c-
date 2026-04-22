#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>


using namespace std;



class clsShowAllClientsScreen : protected clsScreen
{
private :
	static void PrintClientRecordLine(clsBankClient Client)
	{

		cout << setw(8) << left << "\t| " << setw(15) << left << Client.GetAccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(20) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.Pincode;
		cout << "| " << setw(12) << left << Client.AccountBalance;

	}


public :
	static void ShowClientsList()
	{

		if (!CheckAccessRigths(clsUser::enPermission::pListClients))
		{
			return; 
		}

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\tClients List Screen ";
		string SubTitle = "\tClient List (" + to_string(vClients.size()) + ") Client(s).";
		
		_DrawScreenHeader(Title, SubTitle);
		cout << setw(8)<<left<<"" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8)<<left<<"" <<"| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance\n";
		cout << setw(8) << left << "\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else

			for (clsBankClient Client : vClients)
			{

				PrintClientRecordLine(Client);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}

};


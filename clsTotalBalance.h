#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsUtil.h"
class clsTotalBalance :protected clsScreen
{
private :
	static void PrintClientRecordBalanceLine(clsBankClient Client)
{

	cout << "| " << setw(15) << left << Client.GetAccountNumber();
	cout << "| " << setw(40) << left << Client.FullName();
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
public :
	static void ShowTotalBalances()
		{
		
			vector <clsBankClient> vClients = clsBankClient::GetClientsList();
			string sudtitle = "\t Balances List(" + to_string(vClients.size()) + ") Client(s).";
			_DrawScreenHeader("\t Total Balance ",sudtitle);
			cout << "\n_______________________________________________________";
			cout << "_________________________________________\n" << endl;
		
			cout << "| " << left << setw(15) << "Accout Number";
			cout << "| " << left << setw(40) << "Client Name";
			cout << "| " << left << setw(12) << "Balance";
			cout << "\n_______________________________________________________";
			cout << "_________________________________________\n" << endl;
		
			double TotalBalances = clsBankClient::GetTotalBalance();
		
			if (vClients.size() == 0)
				cout << "\t\t\t\tNo Clients Available In the System!";
			else
		
				for (clsBankClient Client : vClients)
				{
					PrintClientRecordBalanceLine(Client);
					cout << endl;
				}
		
			cout << "\n_______________________________________________________";
			cout << "_________________________________________\n" << endl;
			cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
			cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances)<< ")";
		}
};


#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
using namespace std;


class clsShowListScreen : protected clsScreen
{
private:
	static void PrintUserRecordLine(clsUser User)
	{

		cout << setw(8) << left << "\t| " << setw(15) << left << User.GetUserName();
		cout << "| " << setw(20) << left << User.FullName();
		cout << "| " << setw(12) << left << User.Phone;
		cout << "| " << setw(20) << left << User.Email;
		cout << "| " << setw(10) << left << User.Password;
		cout << "| " << setw(12) << left << User.Permissions;

	}


public:
	static void ShowUsersList()
	{

		vector <clsUser> vUsers = clsUser::GetUsersList();

		string Title = "\tUsers List Screen ";
		string SubTitle = "\tUser List (" + to_string(vUsers.size()) + ") User(s).";

		_DrawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "|" << left << setw(15) << "User Name";
		cout << "\t|" << left << setw(20) << "Full Name";
		cout << "|" << left << setw(12) << "Phone";
		cout << "|" << left << setw(20) << "Email";
		cout << "|" << left << setw(10) << "Password";
		cout << "|" << left << setw(12) << "Permissions\n";
		cout << setw(8) << left << "\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vUsers.size() == 0)
			cout << "\t\t\t\tNo Users Available In the System!";
		else

			for (clsUser User : vUsers)
			{

				PrintUserRecordLine(User);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}
};


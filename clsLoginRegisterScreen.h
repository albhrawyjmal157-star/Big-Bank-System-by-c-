#pragma once

#include "clsUser.h"
#include <vector>
#include "clsScreen.h"
#include <fstream>
#include <iomanip>

class clsLoginRegisterScreen : protected clsScreen
{

private :
	struct strLoginRegister
	{
		string DateAndTime;
		string UserName;
		string Password;
		string Permissions;
	};
	static void PrintLoginRegisterRecordLine(strLoginRegister LoginUser)
	{


		cout << setw(8) << left << "" << "| " << setw(35) << left << LoginUser.DateAndTime;
		cout << "| " << setw(20) << left <<LoginUser.UserName;
		cout << "| " << setw(20) << left << LoginUser.Password;
		cout << "| " << setw(10) << left << LoginUser.Permissions << endl;;
	}
	
	static vector<string> SplitSatament(string Statement, string Separator = "#//#")
	{
		vector<string> vWords;
		int position = 0;

		string sWord = "";

		while ((position = int(Statement.find(Separator))) != std::string::npos)
		{
			sWord = Statement.substr(0, position);

			if (sWord != "")
			{
				vWords.push_back(sWord);
			}

			Statement.erase(0, position + Separator.length());
		}

		if (Statement != "")
		{
			vWords.push_back(Statement);
		}

		return vWords;
	}
	static vector<strLoginRegister>_LoadDateOfLoginRegister()
	{
		vector <strLoginRegister>vLoginUsers = {};
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);
		if (MyFile.is_open())
		{
			strLoginRegister User;
			string Line;
			while (getline(MyFile, Line))
			{
				vector<string>vUsersLoginRegister = SplitSatament(Line);
				User.DateAndTime = vUsersLoginRegister[0];
				User.UserName = vUsersLoginRegister[1];
				User.Password = vUsersLoginRegister[2];
				User.Permissions = vUsersLoginRegister[3];
				vLoginUsers.push_back(User);
			}
			MyFile.close();
			return vLoginUsers;
		}

	}
	static void _LoginRegister()
	{

		if (!CheckAccessRigths(clsUser::enPermission::pLoginRegister))
		{
			return;
		}
		vector<strLoginRegister> vUsersLogin = _LoadDateOfLoginRegister();
		string Title = "\tLogin Register Screen ";
		string SubTitle = "\tUsers List (" + to_string(vUsersLogin.size()) + ") User(s).";
		clsScreen::_DrawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		if (vUsersLogin.size() == 0)
		{
			cout << "\t\t\t\tNo Logins Available In the System!";
		}
		else 
		{
			for (strLoginRegister User : vUsersLogin)
			{
				PrintLoginRegisterRecordLine(User);
			}
		}

	}
public:
	static void ShowLoginRegisterScreen()
	{
		_LoginRegister();
	}

};


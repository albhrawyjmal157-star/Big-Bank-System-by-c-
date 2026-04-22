#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Global.h"
#include "clsMainScreen.h"
#include <string>
#include "clsUser.h"
#include "clsDate.h"
#include <fstream>
#include "clsInputVaildate.h"

using namespace std; 

class clsLoginUserScreen :protected clsScreen

{
private:

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		
		string DataLine = "";
		DataLine += clsDate::GetDateAndTimeString() + Seperator;

		DataLine += User.GetUserName() + Seperator;
		DataLine += User.Password + Seperator;
		DataLine += to_string(User.GetPermissions());

		return DataLine;
	}
	
	static bool _Login()
	{
		string _UserName = "";
		string _Password = "";
		bool _UserLoginFaild = false;
		short FaildLoginCount = 0;


		do
		{
			if (_UserLoginFaild)
			{
				FaildLoginCount++; 
				cout << "\nInvaild UserName/Password .";
				cout << "\nYou have " << 3-FaildLoginCount << " to Login . ";
				


			}
			if (FaildLoginCount == 3)
			{
				cout << "\nYour are Loked after 3 faild trials \n\n";
				return false;
			}
			cout << "\n\nEnter UserName ? ";
			cin >> _UserName;
			cout << "\nEnter Password ? ";
			cin >> _Password;


			CurrentUser = clsUser::Find(_UserName, _Password);
			_UserLoginFaild = CurrentUser.IsEmpty();
		} while (_UserLoginFaild);
		clsUser::LoginRegistor(_ConvertUserObjectToLine(CurrentUser));
		clsMainScreen::ShowMainMenue();

	}
public:
	static bool ShowLoginScreen( )
	{
		system("cls");
		clsScreen::_DrawScreenHeader("\t\tLogin");
		return _Login();
	}
};


#pragma once
#include <iostream>
#include "clsInputVaildate.h"
#include "clsScreen.h"
#include "clsUser.h"
class clsFindUserScreen : protected clsScreen

{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card: \n";
		cout << "\n------------------------------";
		cout << "\nFirst Name        : " << User.FirstName;
		cout << "\nLast Name         : " << User.LastName;
		cout << "\nFull Name         : " << User.FullName();
		cout << "\nEmail             : " << User.Email;
		cout << "\nPhone             : " << User.Phone;
		cout << "\nUser Name        : " << User.GetUserName();
		cout << "\nPassword          : " << User.GetPassword();
		cout << "\nPermissions           : " << User.GetPermissions();
		cout << "\n------------------------------\n";
	}

public:

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t Find User Screen ");
		string UserName = "";
		cout << "\nPlease Enter User Name : ";
		UserName = clsInputVailddate::ReadString();
		while (!clsUser::IsUserExists(UserName))
		{
			cout << "\nUser is not found, choose another one: ";
			UserName = clsInputVailddate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		if (!User.IsEmpty())
		{
			cout << "\n User Found ";
			_PrintUser(User);

		}
		else
		{
			cout << "\n User Not Found ";
		}



	}

};


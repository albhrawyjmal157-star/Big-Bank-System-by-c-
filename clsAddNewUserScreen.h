#pragma once
#include <iostream>
#include <fstream>
#include "clsUser.h"
#include "clsInputVaildate.h"
#include "clsScreen.h"
class clsAddNewUserScreen :protected clsScreen
{
private:
	static void ReadUserInfo(clsUser& User)

	{
		cout << "\nEnter First Name: ";
		User.FirstName = clsInputVailddate::ReadString();
		cout << "\nEnter Last Name: ";
		User.LastName = clsInputVailddate::ReadString();
		cout << "\nEnter Email: ";
		User.Email = clsInputVailddate::ReadString();
		cout << "\nEnter Phone: ";
		User.Phone = clsInputVailddate::ReadString();
		cout << "\nEnter Password: ";
		User.Password = clsInputVailddate::ReadString();
		cout << "\nEnter Permission: ";
		User.Permissions = _ReadPermissions();

	}
	static void _PrintUser(clsUser User)
	{
		cout << "\nUSer Card: \n";
		cout << "\n------------------------------";
		cout << "\nFirst Name        : " << User.FirstName;
		cout << "\nLast Name         : " << User.LastName;
		cout << "\nFull Name         : " << User.FullName();
		cout << "\nEmail             : " << User.Email;
		cout << "\nPhone             : " << User.Phone;
		cout << "\nUser Name         : " << User.GetUserName();
		cout << "\nPassword          : " << User.GetPassword();
		cout << "\nPermissions       : " << User.GetPermissions();
		cout << "\n------------------------------\n";
	}
	static int  _ReadPermissions()
	{
		int Permission = 0; 
		char Answer = 'n';
		cout << "\nDo you Want To give full access? (y,n)";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			return -1;
		}

		cout << "\nDo You Want to give access to : \n";

		cout << "\nShow Client List : (y/n)";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission+=clsUser::enPermission::pListClients;
		}
		cout << "\nAdd New Client (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pAddNewClient;
		}
		cout << "\nDelete Client (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pDeleteClient;
		}
		cout << "\nUpdate Client (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::UpdateClient;
		}
		cout << "\nFind Client (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pFindClient;
		}
		cout << "\nTransactions Client (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pTransactions;
		}
		cout << "\nManage Users  Client (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pManagesUsers;
		}
		cout << "\nLogin Register (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pLoginRegister;
		}

		return Permission;

	}
public:
	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader(" \tAdd New User Screen ");
		string UserName = "";
		cout << "\nPlease Enter User Name : ";
		UserName = clsInputVailddate::ReadString();
		while (clsUser::IsUserExists(UserName))
		{
			cout << "\nUser Name is Exisat , choose another one: ";
			UserName = clsInputVailddate::ReadString();
		}

		clsUser User = clsUser::GetAddNewUserObject(UserName);

		ReadUserInfo(User);

		clsUser::enSaveResult SaveResult;
		SaveResult = User.Save();

		switch (SaveResult)
		{
		case clsUser::enSaveResult::svSuccessed:
		{
			cout << "\nAccount Added Successsfully :-)\n";
			cout << "\n\n";
			_PrintUser(User);
			break;
		}

		case clsUser::enSaveResult::svFailEmptyobject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		case clsUser::enSaveResult::FaildUserName:
			cout << "\nError Account Number Is Exists ";
			break;
		}
	}
};


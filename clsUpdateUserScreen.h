#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputVaildate.h"
#include "clsUser.h"
class clsUpdateUserScreen : protected clsScreen
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
		cout << "\nEnter Password : ";
		User.Password = clsInputVailddate::ReadString();
		cout << "\nEnter Permissions : ";
		User.Permissions = _ReadPermissions();

	}
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

		cout << "\nShow User List : (y/n)";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pListClients;
		}
		cout << "\nAdd New User (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pAddNewClient;
		}
		cout << "\nDelete User (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pDeleteClient;
		}
		cout << "\nUpdate User (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::UpdateClient;
		}
		cout << "\nFind User (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pFindClient;
		}
		cout << "\nTransactions User (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permission += clsUser::enPermission::pTransactions;
		}
		cout << "\nManage Users  User (y/n)? ";
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
	static void ShowUpdataUserScreen()
	{
		_DrawScreenHeader("\t Updata User Screen ");
		string UserName = "";
		cout << "\nPlease Enter User Name : ";
		UserName = clsInputVailddate::ReadString();
		while (!clsUser::IsUserExists(UserName))
		{
			cout << "\nUser Name is not found, choose another one: ";
			UserName = clsInputVailddate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);


		char anwser = 'n';

		cout << "\nDo you want to update Data Of User (y,n) ";
		cin >> anwser;

		if (anwser == 'y' || anwser == 'Y')
		{
			cout << "\nUpdate User Info: ";
			cout << "\n---------------------\n";

			ReadUserInfo(User);

			clsUser::enSaveResult SaveResult;

			SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsUser::enSaveResult::svSuccessed:
			{
				cout << "\nAccount Apdated Successsfully :-)\n";
				_PrintUser(User);
				break;
			}

			case clsUser::enSaveResult::svFailEmptyobject:
			{
				cout << "\nError User Name  was not saved because it's Empty";
				break;
			}
			}
		}
	}

};


#pragma once
#include <iostream>
#include "clsPerson.h"
#include <vector>
#include "clsUtil.h"
#include "clsString.h"
#include <fstream>
using namespace std;


class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkForDelete = false;

	static clsUser _ConvertLineToObject(string Line, string Seperator = "#//#")
	{
		vector <string> vWords;
		vWords = clsString::Split(Line, Seperator); //from class clString 
		if (vWords.size() < 7)
		{
			return _GetEmptyUserObject();
		}
		return clsUser(enMode::UpdateMode, vWords[0], vWords[1], vWords[2], vWords[3], vWords[4]
			, clsUtil::DecrptionWord(vWords[5]), stoi(vWords[6]));
	}
	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string DataLine = "";
		DataLine += User.FirstName + Seperator;
		DataLine += User.LastName + Seperator;
		DataLine += User.Email + Seperator;
		DataLine += User.Phone + Seperator;
		DataLine += User.GetUserName() + Seperator;
		DataLine += clsUtil::EncrptionWord(User.Password) + Seperator;
		DataLine += to_string(User.GetPermissions());

		return DataLine;
	}
	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static vector<clsUser>_LoadUsersDataFromFile()
	{
		vector<clsUser>vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToObject(Line);
				vUsers.push_back(User);

			}
			MyFile.close();
		}
		return vUsers;
	}
	static void _SaveUsersDataToFile(vector <clsUser>_vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsUser& c : _vUsers)
			{
				if (!c._MarkForDelete)
				{
					MyFile << _ConvertUserObjectToLine(c) << endl;
				}

			}
			MyFile.close();
		}
	}
	void _Update()
	{
		vector<clsUser>_vUsers;
		_vUsers = _LoadUsersDataFromFile();
		for (clsUser& c : _vUsers)
		{
			if (c.GetUserName() == GetUserName())
			{
				c = *this;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);
	}
	static void _AddDatatLineToFile(string Line)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}
	void _AddNew()
	{
		_AddDatatLineToFile(_ConvertUserObjectToLine(*this));
	}
public:
	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone
		, string UserName, string Password, int Permissions)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_Password = Password;
		_UserName = UserName;
		_Permissions = Permissions;
		
	}

	enum enPermission{ eAll=-1,pListClients=1,pAddNewClient=2,pDeleteClient=4,UpdateClient=8
	,pFindClient=16,pTransactions=32,pManagesUsers=64,pLoginRegister=128};


	string GetUserName()
	{
		return _UserName;
	}

	static void LoginRegistor(string Line)
	{
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app );
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword))string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;



	string FullName()
	{
		return FirstName + "  " + LastName;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsUser Find(string UserName)
	{
		vector<clsUser>vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToObject(Line);
				if (UserName == User.GetUserName())
				{
					MyFile.close();
					return User;
				}
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}
	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser Client = _ConvertLineToObject(Line);
				if (UserName == Client.GetUserName() &&
					Password == Client.Password)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static bool IsUserExists(string UserName)
	{
		clsUser Client = Find(UserName);
		return (!Client.IsEmpty());
	}

	enum enSaveResult { svFailEmptyobject = 0, svSuccessed = 1, FaildUserName };
	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return enSaveResult::svFailEmptyobject;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResult::svSuccessed;
			break;
		}

		case enMode::AddNewMode:
		{
			if (IsUserExists(_UserName))
			{
				return enSaveResult::FaildUserName;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSuccessed;

			}
		}
		}
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete()
	{
		vector<clsUser>vUsers;
		vUsers = _LoadUsersDataFromFile();
		for (clsUser& User : vUsers)
		{
			if (_UserName == User.GetUserName())
			{
				User._MarkForDelete = true;
				break;
			}

		}
		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}


	bool CheckAccessPermission(enPermission Permission)
	{
		if (this->Permissions == enPermission::eAll)
		{
			return true;
		}
		if ((Permission & this->Permissions) == Permission)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
};


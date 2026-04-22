#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include <fstream>
#include<string>
#include <vector>


using namespace std;


class clsBankClient : public clsPerson
{
private :
	enum enMode{EmptyMode = 0,UpdateMode =1,AddNewMode=2};
	enMode _Mode;


	string _UserName;
	string _Pincode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToObject(string Line ,string Seperator ="#//#")
	{
		vector <string> vWords;
		vWords = clsString::Split(Line,Seperator); //from class clString 
		if (vWords.size() != 7)
		{
			return _GetEmptyClientObject();
		}
		return clsBankClient(enMode::UpdateMode, vWords[0], vWords[1], vWords[2], vWords[3], vWords[4]
			,clsUtil::DecrptionWord(vWords[5]), stof(vWords[6]));
	}
	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string DataLine = "";
		DataLine += Client.FirstName + Seperator;
		DataLine += Client.LastName + Seperator;
		DataLine += Client.Email + Seperator;
		DataLine += Client.Phone + Seperator;
		DataLine += Client.GetAccountNumber() + Seperator;
		DataLine += clsUtil::EncrptionWord(Client.Pincode) + Seperator;
		DataLine += to_string(Client.AccountBalance);

		return DataLine;
	}
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static vector<clsBankClient>_LoadClientsDataFromFile()
	{
		vector<clsBankClient>vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToObject(Line);
				vClients.push_back(Client);

			}
			MyFile.close();
		}
		return vClients;
	}
	static void _SaveClientsDataToFile(vector <clsBankClient>_vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsBankClient& c : _vClients)
			{
				if (!c._MarkForDelete)
				{
					MyFile << _ConvertClientObjectToLine(c) << endl;
				}
					
			}
			MyFile.close();
		}
	}
	void _Update()
	{
		vector<clsBankClient>_vClients;
		_vClients = _LoadClientsDataFromFile();
		for (clsBankClient& c : _vClients)
		{
			if (c.GetAccountNumber() == GetAccountNumber())
			{
				c = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}
	static void _AddDatatLineToFile(string Line)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}
	void _AddNew()
	{
		_AddDatatLineToFile(_ConvertClientObjectToLine(*this));
	}
public :
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone
		, string AccountNumber, string Pincode, float AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = AccountNumber;
		_Pincode = Pincode;
		_AccountBalance = AccountBalance;
	}

	  string GetAccountNumber()
	{
		return _UserName;
	}


	void SetPincode(string Pincode)
	{
		_Pincode = Pincode;
	}
	string GetPincode()
	{
		return _Pincode;
	}
	__declspec(property(get = GetPincode, put = SetPincode))string Pincode;


	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;


	string FullName()
	{
		return FirstName + "  " + LastName;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToObject(Line);
				if (AccountNumber == Client.GetAccountNumber())
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber,string Pincode)
	{
		vector<clsBankClient>vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToObject(Line);
				if (AccountNumber == Client.GetAccountNumber() &&
					Pincode==Client.Pincode)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExists(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	static void PrintShort(clsBankClient Client)
	{
		cout << "\nClient Card : \n\n";
		cout << "\n----------------------------------------------";
		cout << "\nFull Name : " << Client.FullName();
		cout << "\nAcc. Num    : " << Client.GetAccountNumber();
		cout << "\nBalance       : " << Client.GetAccountBalance();
		cout << "\n----------------------------------------------";
	}
	enum enSaveResult{svFailEmptyobject=0,svSuccessed=1,FaildAccountNumber};
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
			if (IsClientExists(_UserName))
			{
				return enSaveResult::FaildAccountNumber;
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

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient>vClients;
		vClients = _LoadClientsDataFromFile();
		for (clsBankClient& client : vClients)
		{
			if (_UserName == client.GetAccountNumber() )
			{
				client._MarkForDelete = true;
				break;
			}
			
		}
		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}


	static double GetTotalBalance()
	{
		vector <clsBankClient>vClients;
		vClients = _LoadClientsDataFromFile();

		double TotalBalance = 0;
		for (clsBankClient c : vClients)
		{
			TotalBalance += c.GetAccountBalance();
		}

		return TotalBalance;
	}
	void Deposite(float amount)
	{
		_AccountBalance += amount;
		Save();
	}
	void Withdraw(float amount)
	{

		_AccountBalance -= amount;
		Save();
	}
};


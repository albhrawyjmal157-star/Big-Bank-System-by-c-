#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include"clsScreen.h"


using namespace std;


class clsShowList : protected clsScreen
{
private:
	struct _stShowListTransfer
	{
		string TimeAndData;
		string AccountFrom;
		string AccountTo;
		double Amount=0;
		double BalanceFrom=0;
		double BalanceTo=0;
		string UserName="";

	};
	static vector<string> _Split(string Statement, string Separator = "#//#")
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
	static _stShowListTransfer ConvertDataToStruct(string Line)
	{
		_stShowListTransfer Data;
		vector<string> vData;
		vData = _Split(Line);
		Data.TimeAndData = vData[0];
		Data.AccountFrom = vData[1];
		Data.AccountTo = vData[2];
		Data.Amount = stod(vData[3]);
		Data.BalanceFrom = stod(vData[4]);
		Data.BalanceTo = stod(vData[5]);
		Data.UserName = vData[6];
		return Data;
	}

	static vector<_stShowListTransfer>LoadDataFromFile()
	{
		vector<_stShowListTransfer>vWords;
		fstream MyFile;
		MyFile.open("Transfer.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				_stShowListTransfer Data = ConvertDataToStruct(Line);
				vWords.push_back(Data);
			}
			MyFile.close();
		}
		return vWords;
	}
	static void PrintTransferLogRecordLine(_stShowListTransfer Data)
	{

		cout << setw(8) << left << "" << "| " << setw(23) << left << Data.TimeAndData;
		cout << "| " << setw(8) << left << Data.AccountFrom;
		cout << "| " << setw(8) << left << Data.AccountTo;
		cout << "| " << setw(8) << left << Data.Amount;
		cout << "| " << setw(10) << left << Data.BalanceFrom;
		cout << "| " << setw(10) << left << Data.BalanceTo;
		cout << "| " << setw(8) << left << Data.UserName;


	}


public :
	
public:

	static void ShowTransferLogScreen()
	{


		vector <_stShowListTransfer >vData =  LoadDataFromFile();

		string Title = "\tTransfer Log List Screen";
		string SubTitle = "\t    (" + to_string(vData.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(8) << "User";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vData.size() == 0)
			cout << "\t\t\t\tNo Transfers Available In the System!";
		else

			for (_stShowListTransfer Data : vData)
			{

				PrintTransferLogRecordLine(Data);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}
	
};


#pragma once
#include <iostream>
#include <vector>
#include"clsString.h"
#include <fstream>
#include <string>


using namespace std;


class clsCurrency
{

private:
	enum enMode {

		
		emptyMode=1,
		UpdateMode=2,
	};

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;
		
	static vector<string> Split(string Statement, string Separator = "#//#")
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
	static clsCurrency _GetEmptyObject()
	{
		return clsCurrency(enMode::emptyMode, "", "","", 0);
	}
	static clsCurrency _ConvertLineDataToObject(string Line)
	{
		vector<string>vData;
		vData = Split(Line);
		if (vData.size() != 4)
		{
			return _GetEmptyObject();
		}
		return clsCurrency(enMode::UpdateMode, vData[0], vData[1], vData[2], stof(vData[3]));

	}
	static string _ConvertObjectDataToLine(clsCurrency Currency, string Separator = "#//#")
	{
		string Line="";
		Line += Currency.Country() + Separator;
		Line += Currency.CurrencyCode() + Separator;
		Line += Currency.CurrencyName() + Separator;
		Line += to_string(Currency.Rate());
		return Line;
		
	}
	static vector<clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector<clsCurrency>vCurrencyData;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				
				clsCurrency Currency = _ConvertLineDataToObject(Line);
				vCurrencyData.push_back(Currency);
			}
			MyFile.close();
			return vCurrencyData;
		}

	}
	void _Update()
	{
		vector<clsCurrency> CurrencyData;
		CurrencyData = _LoadCurrencyDataFromFile();

		for (clsCurrency& currency : CurrencyData)
		{
			if (CurrencyCode() == currency.CurrencyCode())
			{
				currency = *this;
				break;
			}
		}
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open())
		{
			string Line;
			for (clsCurrency Currency : CurrencyData)
			{
				Line = _ConvertObjectDataToLine(Currency);
				MyFile << Line << endl;
			}
			MyFile.close();
		}
	}
public :
	clsCurrency(enMode Mode,string Country, string CurrencyCode, string CurrencyName
		, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool ISEmpty()
	{
		return (_Mode == enMode::emptyMode);
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}
	string CurrencyCode()
	{
		return _CurrencyCode;
	}
	float Rate()
	{
		return _Rate;
	}
	string Country()
	{
		return _Country;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCurrencyCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperLettersCase(CurrencyCode);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{

				clsCurrency Currency = _ConvertLineDataToObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
				
			}
			MyFile.close();
			return _GetEmptyObject();
			
		}
	}



	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperLettersCase(Country);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{

				clsCurrency Currency = _ConvertLineDataToObject(Line);
				if (clsString::UpperLettersCase(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}

			}
			MyFile.close();
			return _GetEmptyObject();

		}
	}

	static bool IsCurrencyExists(string CurrencyCode)
	{
		clsCurrency Currency = FindByCurrencyCode(CurrencyCode);
		return (!Currency.ISEmpty());
	}

	static vector<clsCurrency>  GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}



	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.Rate());

	}


};


#pragma once

#include "clsCurrency.h"
#include "clsScreen.h"
#include <iomanip>

class clsFindCurrency :  protected clsScreen
{

private:
    static void PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << "\n--------------------------------------\n";
        cout << "Country           :  " << Currency.Country() << endl;
        cout << "CurrencyCode      : " << Currency.CurrencyCode() << endl;
        cout << "CurrencyName      : " << Currency.CurrencyName() << endl;
        cout << "Rate ($)          : " << Currency.Rate() << endl;
        cout << "\n--------------------------------------\n";
    }

public :
    static void ShowFindCurrency()
    {
        _DrawScreenHeader("\tFind Currency Screen ");

        int choice;
        cout << "\nFind By Code[1] or Country[2]  : ";
        cin >> choice;
        if (choice==1)
        {
            string CurrencyCode;
            cout << "\nEnter CurrencyCode : \n";
            cin >> CurrencyCode;

            clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
            if (Currency.ISEmpty())
            {
                cout << "\nCurrency Not Found \n";
            }
            else
            {
                PrintCurrencyRecordLine(Currency);
            }
        }
        else if (choice == 2)
        {
            string Country;
            cout << "\nEnter Country : \n";
            cin >> Country;
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            if (Currency.ISEmpty())
            {
                cout << "\nCurrency Not Found \n";
            }
            else
            {
                PrintCurrencyRecordLine(Currency);
            }
        }
    }
};


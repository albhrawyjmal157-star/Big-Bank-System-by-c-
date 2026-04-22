#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputVaildate.h"
#include <iomanip>
class clsUpdateRate :protected clsScreen
{
private :
    static void PrintCurrencyRecordLine(clsCurrency Currency)
    {

        cout << "\n--------------------------------------\n";
        cout << "Country           :  " << Currency.Country() << endl;
        cout << "CurrencyCode      : " << Currency.CurrencyCode() << endl;
        cout << "CurrencyName      : " << Currency.CurrencyName() << endl;
        cout << "Rate ($)          : " << Currency.Rate() << endl;
        cout << "\n--------------------------------------\n";

    }
public:
	static void ShowUpdateCurrencyScreen()
	{
		_DrawScreenHeader("\tUpdate Currency Screen");
        string Currencycode;
        cout << "\nEnter Currency Code : \n";
        cin >> Currencycode;
       
        char Answer = 'n';
        clsCurrency Currency = clsCurrency::FindByCurrencyCode(Currencycode);
        PrintCurrencyRecordLine(Currency);
        cout << "\nDo You Want Update Rate : (y,n)";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            
            if (Currency.ISEmpty())
            {
                cout << "\nCurrency Not Found \n";
            }
            else
            {
                
                cout << "\nEnter New Curenncy \n";
                float NewRate = (float)clsInputVailddate::ReadDoubleNumber();
                Currency.UpdateRate(NewRate);
                cout << "\nCurrency Updated Successfully\n";
                PrintCurrencyRecordLine(Currency);
            }
        }
        
	}
};


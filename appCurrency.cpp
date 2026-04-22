#include <iostream>
#include "clsCurrency.h"

using namespace std;


static void _PrintCurrency(clsCurrency Currency)
{
    cout << "\nCurrency Card:\n";
    cout << "_____________________________\n";
    cout << "\nCountry    : " << Currency.Country();
    cout << "\nCode       : " << Currency.CurrencyCode();
    cout << "\nName       : " << Currency.CurrencyName();
    cout << "\nRate(1$) = : " << Currency.Rate();

    cout << "\n_____________________________\n";

}

int main()
{
    clsCurrency Curency1 = clsCurrency::FindByCurrencyCode("joD");
    if (Curency1.ISEmpty())
    {
        cout << "\nCurrency Not Found \n";
    }
    else
    {
        _PrintCurrency(Curency1);
    }

    clsCurrency Curency2 = clsCurrency::FindByCountry("Egypt");
    if (Curency1.ISEmpty())
    {
        cout << "\nCurrency Not Found \n";
    }
    else
    {
        _PrintCurrency(Curency2);
    }

    Curency1.UpdateRate(0.7);
    _PrintCurrency(Curency1);
}
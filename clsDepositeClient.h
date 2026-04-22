#pragma once
#include <iostream>
#include <limits>
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsInputVailddate
{
public:

    static bool IsNumberBetween(int Number, int From, int To)
    {
        return (Number >= From && Number <= To);
    }

    static bool IsNumberBetween(short Number, short From, short To)
    {
        return (Number >= From && Number <= To);
    }

    static bool IsNumberBetween(float Number, float From, float To)
    {
        return (Number >= From && Number <= To);
    }

    static bool IsNumberBetween(double Number, double From, double To)
    {
        return (Number >= From && Number <= To);
    }

    static bool IsDate1BeforeDate2(clsDate D1, clsDate D2)
    {
        if (D1.GetYear() < D2.GetYear()) return true;

        if (D1.GetYear() == D2.GetYear() && D1.GetMonth() < D2.GetMonth())
            return true;

        if (D1.GetYear() == D2.GetYear() &&
            D1.GetMonth() == D2.GetMonth() &&
            D1.GetDay() < D2.GetDay())
            return true;

        return false;
    }

    static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
    {
        if (IsDate1BeforeDate2(To, From))
        {
            clsUtil::Swap(From, To);
        }

        return (!IsDate1BeforeDate2(Date, From) &&
            !IsDate1BeforeDate2(To, Date));
    }

    static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
    {
        int Number;

        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }

        return Number;
    }

    static double ReadDoubleNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
    {
        double Number;

        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }

        return Number;
    }

    static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
    {
        float Number;

        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }

        return Number;
    }

    static int ReadIntBetween(int From, int To,
        string ErrorMessage = "Out of Range: Enter Again ")
    {
        if (From > To)
        {
            clsUtil::Swap(From, To);
        }

        int Number = ReadIntNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }

        return Number;
    }

    static double ReadDoubleBetween(double From, double To,
        string ErrorMessage = "Out of Range: Enter Again ")
    {
        if (From > To)
        {
            clsUtil::Swap(From, To);
        }

        double Number = ReadDoubleNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadDoubleNumber();
        }

        return Number;
    }

    static float ReadFloatBetween(float From, float To,
        string ErrorMessage = "Out of Range: Enter Again ")
    {
        if (From > To)
        {
            swap(From, To);
        }

        float Number = ReadFloatNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadFloatNumber();
        }

        return Number;
    }

    static string ReadString()
    {
        string s;
        getline(cin >> ws, s);
        return s;
    }

    static bool IsVaildDate(clsDate Date)
    {
        return clsDate::IsValidDate(Date);
    }
};
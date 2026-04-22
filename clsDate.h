#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <ctime>  // ضروري لـ time_t و tm

using namespace std;

class clsDate
{
private:
    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;

public:
    // ===== Constructors =====
    clsDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
    }

    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(string sDate)
    {
        vector<string> vDate;
        size_t pos = 0;
        string token;
        string delimiter = "/";
        while ((pos = sDate.find(delimiter)) != string::npos) {
            token = sDate.substr(0, pos);
            vDate.push_back(token);
            sDate.erase(0, pos + delimiter.length());
        }
        vDate.push_back(sDate);

        if (vDate.size() == 3) {
            _Day = stoi(vDate[0]);
            _Month = stoi(vDate[1]);
            _Year = stoi(vDate[2]);
        }
    }

    clsDate(short DateOrderInYear, short Year)
    {
        clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
        _Day = Date1._Day;
        _Month = Date1._Month;
        _Year = Date1._Year;
    }

    // ===== Getters & Setters =====
    void SetDay(short Day) { _Day = Day; }
    short GetDay() { return _Day; }

    void SetMonth(short Month) { _Month = Month; }
    short GetMonth() { return _Month; }

    void SetYear(short Year) { _Year = Year; }
    short GetYear() { return _Year; }

    // ===== Print =====
    void Print()
    {
        cout << DateToString() << endl;
    }

    // ===== Static Helpers =====
    static clsDate GetSystemDate()
    {
        return clsDate();
    }

    static bool isLeapYear(short Year)
    {
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    bool isLeapYear()
    {
        return isLeapYear(_Year);
    }

    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12) return 0;
        int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
    }

    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }

    static bool IsValidDate(clsDate Date)
    {
        if (Date._Month < 1 || Date._Month > 12) return false;
        if (Date._Day < 1 || Date._Day > NumberOfDaysInAMonth(Date._Month, Date._Year)) return false;
        return true;
    }

    bool IsValid()
    {
        return IsValidDate(*this);
    }


    static string DateToString(clsDate Date)
    {
        return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
    }

    string DateToString()
    {
        return DateToString(*this);
    }

    // ===== Date Comparisons =====
    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1._Year < Date2._Year) ? true :
            ((Date1._Year == Date2._Year) ?
                ((Date1._Month < Date2._Month) ? true :
                    ((Date1._Month == Date2._Month) ? Date1._Day < Date2._Day : false))
                : false);
    }

    static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1._Day == Date2._Day &&
            Date1._Month == Date2._Month &&
            Date1._Year == Date2._Year);
    }

    // ===== Add One Day =====
    static clsDate AddOneDay(clsDate Date)
    {
        if (Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year))
        {
            Date._Day = 1;
            if (Date._Month == 12)
            {
                Date._Month = 1;
                Date._Year++;
            }
            else
            {
                Date._Month++;
            }
        }
        else
        {
            Date._Day++;
        }
        return Date;
    }
    static string GetDateAndTimeString()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        string DateAndTime = to_string(now->tm_wday) +
            "/" + to_string(now->tm_mon + 1) +
            "/" + to_string(now->tm_year + 1900)+
        " - "+ to_string(now->tm_hour) +
            ":" + to_string(now->tm_min) +
            ":" + to_string(now->tm_sec);
        return DateAndTime;
    }

    void AddOneDay()
    {
        *this = AddOneDay(*this);
    }

    // ===== Difference in Days =====
    static int GetDifferenceInDays(clsDate Date1, clsDate Date2)
    {
        int Days = 0;
        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Date1 = AddOneDay(Date1);
            Days++;
        }
        while (IsDate1BeforeDate2(Date2, Date1))
        {
            Date2 = AddOneDay(Date2);
            Days--;
        }
        return Days;
    }

    int GetDifferenceInDays(clsDate Date2)
    {
        return GetDifferenceInDays(*this, Date2);
    }

    // ===== Get Date From Day Order in Year =====
    static clsDate GetDateFromDayOrderInYear(short DayOrder, short Year)
    {
        short month = 1;
        while (DayOrder > NumberOfDaysInAMonth(month, Year))
        {
            DayOrder -= NumberOfDaysInAMonth(month, Year);
            month++;
        }
        short day = DayOrder;
        return clsDate(day, month, Year);
    }
};
#pragma once
#pragma warning(disable : 4996)
#include <ctime>
#include <iostream>
#include "clsUser.h"
#include "Global.h"

using namespace std;


class clsScreen
{

    protected:
        static void _DrawScreenHeader(string Title, string SubTitle = "")
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  " << Title;
           
            if (SubTitle != "")
            {
                cout << "\n\t\t\t\t\t  " << SubTitle;
            }
            
            cout << "\n\n\t\t\t\t\tUser : " << CurrentUser.GetUserName();
            time_t t = time(0);
            tm* now = localtime(&t);
            int year = now->tm_year + 1900;
            int month = now->tm_mon + 1;
            int days = now->tm_mday;
            cout << "\n\t\t\t\t\tData : " << days << "/" << month << "/" << year;
            cout << "\n\t\t\t\t\t______________________________________\n\n";
        }

        static bool CheckAccessRigths(clsUser::enPermission Permission)
        {
            if (!CurrentUser.CheckAccessPermission(Permission))
            {
                cout << "\t\t\t\t\t------------------------------------";
                cout << "\n\n\t\t\t\t\t  Access Demied! Contact Your Admin ";
                cout << "\t\t\t\t\t\t------------------------------------";
                return false;
            }
            else
            {
                return true;
            }
        }

};


#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputVaildate.h"
#include <iomanip>
#include "clsShowListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;


class clsManageUserScreen : protected clsScreen
{
private:
    enum _enOpation{eShowClientsList=1,AddNewClient=2,DeleteClient=3
        ,UpdateClient=4,FindClient=5,MainMenu=6};

   static  void _ShowClientListScreen()
    {
        //cout << "ShowClientListScreen" << endl;
       clsShowListScreen::ShowUsersList();
    }

    static void _ShowAddNewClientScreen()
    {
        //cout <<"ShowAddNewClientScreen" << endl;
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }
    static void _ShowDeleteClientScreen()
    {
        //cout << "ShowDeleteClientScreen" << endl;
        clsDeleteUserScreen::DeleteUser();
    }

    static void _ShowUpdateClientScreen()
    {
        //cout << "ShowUpdateClientScreen" << endl;
        clsUpdateUserScreen::ShowUpdataUserScreen();
    }
    static void _ShowFindClientScreen()
    {
        //cout << "ShowFindClientScreen" << endl;
        clsFindUserScreen::ShowFindUserScreen();
    }
    static void _OperateProcessingOfChoiceUser(_enOpation opation)
    {
        switch (opation)
        {
        case _enOpation::eShowClientsList:
        {
            system("cls");
            _ShowClientListScreen();
            _GoToManageUsersScreen();
            break;
        }
        case _enOpation::AddNewClient:
        {
            system("cls");
            _ShowAddNewClientScreen();
            _GoToManageUsersScreen();
            break;
        }
        case _enOpation::DeleteClient:
        {
            system("cls");
            _ShowDeleteClientScreen();
            _GoToManageUsersScreen();
            break;
        }
        case _enOpation::UpdateClient:
        {
            system("cls");
            _ShowUpdateClientScreen();
            _GoToManageUsersScreen();
            break;
        }
        case _enOpation::FindClient:
        {
            system("cls");
            _ShowFindClientScreen();
            _GoToManageUsersScreen();
            break;
        }
        case _enOpation::MainMenu:
        {

        }
        }
        
    }
    static void _GoToManageUsersScreen()
    {
        cout << "\nPress Any Botton To Continue ";
        system("pause > 0");
        system("cls");
        ShowManageScreen();
    }

	static void _MainMenuOfManageUser()
	{
        system("cls");
        _DrawScreenHeader("\tManage Users Screen");
        cout << setw(37) << left << "" << "===========================================\n\n";
        cout << setw(37) << left << "" << " \t\tManagement Users \n\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show User List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu .\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << "\n\t\t\t\t\tChoose what do you want to do? [1 to 6]?";
	}
public:
    static void ShowManageScreen()
    {
        if (!CheckAccessRigths(clsUser::enPermission::pManagesUsers))
        {
            return;
        }

        _MainMenuOfManageUser();
        int choice = clsInputVaildate::ReadIntBetween(1, 6);
        _OperateProcessingOfChoiceUser((_enOpation)choice);
    }

};


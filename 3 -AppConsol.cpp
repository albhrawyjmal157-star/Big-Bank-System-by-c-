#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputVaildate.h"
#include "clsMainScreen.h"
#include "clsLoginUserScreen.h"


using namespace std;



int main()
{
	while (true)
	{

		//clsMainScreen::ShowMainMenue();
		if (!clsLoginUserScreen::ShowLoginScreen())
		{
			break;
		}

		
	}
	return 0;
}
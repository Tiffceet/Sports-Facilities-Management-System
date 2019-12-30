#include "stdcxx.h"
#include "booking.h"
#include "fusage.h"
#include "userinfo.h"
#include "staff.h"
#include "facility.h"
int mainMenu();
int main(void)
{
	// initalise env variables
	init();
	while (mainMenu()) // if user input is invalid, menu() returns 0
	{
		system("cls"); // clear current console screen
		continue;
	}
	system("pause");
	return 0;
}

int mainMenu()
{
	char choiceText[][100] = { "Staff", "Facilities", "Users", "Booking Facilities", "Facilities Usage", "Exit" };
	int choice = globalMainMenu("<!> CONSOLE <!>", 6, choiceText);
	// menu selection
	switch (choice)
	{
	case 1:
		staffMain();
		break;
	case 2:
		// facilityMenu();
		facInfoMain();
		break;
	case 3:
		userinfoMain();
		break;
	case 4:
		bookingMain();
		break;
	case 5:
		fusagemain();
		break;
	case 6:
		exit(0);
		break;
	default:
		return 1;
	}
	return 1;
}
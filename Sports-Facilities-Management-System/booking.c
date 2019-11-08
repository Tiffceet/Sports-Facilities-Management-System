#include "booking.h"
#include "stdcxx.h"
int bookingMenu() 
{
	printf("==============\n");
	printf("Booking Module\n");
	printf("==============\n");
	printf("1. Book\n");
	printf("2. Search records\n");
	printf("3. Modify records\n");
	printf("4. Display all bookings\n");
	printf("\nMenu Choice: ");
	char choice[10];
	if (getUserMenuChoice(choice, 9))
	{
		return 1;
	}
	switch (choice[0])
	{
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	default:
		return 1;
	}
	return 0;

}

void bookingMain()
{
	while (bookingMenu())
	{

		continue;
	}
}

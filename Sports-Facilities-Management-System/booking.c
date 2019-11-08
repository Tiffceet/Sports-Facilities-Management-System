#include "booking.h"
#include "stdcxx.h"

void bookingSeachRecords()
{

}

void bookingBook()
{

}

void bookingModifyRecords()
{

}

void bookingDisplayAll()
{
	FILE *f;
	f = fopen(bookingFilePath, 'r');
	if (!f)
	{
		printf("Missing booking.txt.\nIts all developers' fault. Contact the developers.\n");
		fclose(f);
		return;
	}
	fclose(f);
}

int bookingMenu()
{
	printf("==============\n");
	printf("Booking Module\n");
	printf("==============\n");
	printf("1. Book\n");
	printf("2. Search records\n");
	printf("3. Modify records\n");
	printf("4. Display all bookings\n");
	printf("5. Return to console\n");
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
	case '5':
		return 0;
	default:
		return 1;
	}
	return 1;

}

void bookingMakeSureFileExist()
{
	FILE *f = fopen(bookingFilePath, "r");
	if (!f)
	{
		fclose(f);
		f = fopen(bookingFilePath, "w");
		fclose(f);
	}
}

void bookingMain()
{
	// define filepath
	sprintf(bookingFilePath, "%s\\%s", APPDATA_PATH, "booking.txt");
	bookingMakeSureFileExist();
	// while menu() doesnt return 0 = continue running
	while (bookingMenu())
	{
		continue;
	}
}

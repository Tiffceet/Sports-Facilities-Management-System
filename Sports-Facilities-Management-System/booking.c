#include "booking.h"
#include "stdcxx.h"
typedef struct
{
	char bookingID[10];
	Date currentDate;
	Date bookingDate;
	Time bookingTime;
	char usrID[20];
	char facilityID[20];
} BookingData;
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
	FILE *f = fopen(bookingFilePath, "r");
	if (!chkFileExist(f))
	{
		printf("No records found.\n");
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
	getUserMenuChoice(choice, 9, "Menu Choice: ");
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

void bookingMain()
{
	// define filepath
	sprintf(bookingFilePath, "%s\\%s", APPDATA_PATH, "booking.txt");
	// while menu() doesnt return 0 = continue running
	while (bookingMenu())
	{
		continue;
	}
}

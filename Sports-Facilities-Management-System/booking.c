#include "booking.h"
#include "stdcxx.h"
typedef struct
{
	char bookingID[10];
	Date currentDate;
	Time currentTime;
	Date bookingDate;
	int timeSlotsBooked[6];
	char usrID[20];
	char staffID[20];
	char facilityID[20];
} BookingData;

void bookingMain()
{
	// define filepath
	sprintf(bookingFilePath, "%s\\%s", APPDATA_PATH, "booking.txt");
	// initialise error code for input validation use
	err = 0;
	// while menu() doesnt return 0 = continue running
	while (bookingMenu())
	{
		continue;
	}
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
		bookingBook();
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

void printBookingInfo()
{
	printf("=====================================================================================================================\n");
	printf("|                                                   Booking Info                                                    |\n");
	printf("=====================================================================================================================\n");
	printf("| 1. Please refrain from monopolising facility by making booking for a whole day                                    |\n");
	printf("| 2. Booking for multiple time slots is allowed                                                                     |\n");
	printf("| 3. Timeslots as follows:                                                                                          |\n");
	printf("|      - Weekdays (Mon - Fri) < 7am-9am, 9am-11am, 1pm-3pm, 3pm-5pm, 5pm-7pm, 7pm-9pm >                             |\n");
	printf("|      - Weekends (Sat & Sun) < 7am-9am, 9am-11am, 1pm-3pm, 3pm-5pm                   >                             |\n");
	printf("| 4. Please proceed to payment counter after booking                                                                |\n");
	printf("|                                                                                                                   |\n");
	printf("=====================================================================================================================\n");
	printf("=====================================================================================================================\n");
}

void bookingBook()
{
	BookingData data[100];
	// initialise slotsBooked
	for (int a = 0; a < 100; a++)
	{
		for (int b = 0; b < 6; b++) {
			data[a].timeSlotsBooked[b] = 0;
		}
	}
	// find latestBooking ID + count of items in file
	char latestBookingID[10];
	latestBookingID[0] = '\0';
	FILE *f = fopen(bookingFilePath, "r");
	int idx = 0; // keep track of how many records are there
	// if file exist, get latest bookingID
	if (chkFileExist(f))
	{
		while (fscanf(f, "%[^,],%d/%d/%d,%d:%d:%d,%d/%d/%d,%d,%d,%d,%d,%d,%d,%[^,],%[^,],%[^\n]\n",
			data[idx].bookingID,
			&data[idx].currentDate.d,
			&data[idx].currentDate.m,
			&data[idx].currentDate.y,
			&data[idx].currentTime.h,
			&data[idx].currentTime.m,
			&data[idx].currentTime.s,
			&data[idx].bookingDate.d,
			&data[idx].bookingDate.m,
			&data[idx].bookingDate.y,
			&data[idx].timeSlotsBooked[0],
			&data[idx].timeSlotsBooked[1],
			&data[idx].timeSlotsBooked[2],
			&data[idx].timeSlotsBooked[3],
			&data[idx].timeSlotsBooked[4],
			&data[idx].timeSlotsBooked[5],
			data[idx].usrID,
			data[idx].staffID,
			data[idx].facilityID
		) != EOF) {
			strcpy(latestBookingID, data[idx].bookingID);
			idx++;
		}
	}
	else 
	{
		f = fopen(bookingFilePath, "w");
	}
	incrementBookingID(latestBookingID); // increment bookingID
	printBookingInfo();
	// Ask user to select facility
	printf("Select one of the following facilities: \n");
	/*
	Insert code to get all facilities
	Need to count how many facilities are there?
	*/
	printf("\nEnter the facility ID you wish to book: ");
	char userPickedfacilityID[100];
	s_input(userPickedfacilityID, 99);
	/*
	Insert code to check for facilities availablity
	*/
	// If available, ask user for date
	Date userPickedDate;
	askUserForBookingDate(&userPickedDate);

	int timeSlotsAvailable[6] = { 1,1,1,1,1,1 };
	checkForTimeslotsAvailablity(&timeSlotsAvailable, &data, idx, &userPickedDate, userPickedfacilityID);

	int atLeastOneSlotisAvailable = 0;
	printf("Timeslots: \n");
	printf("\t1. 7am-9am");
	if (timeSlotsAvailable[0]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	printf("\t2. 9am-11am");
	if (timeSlotsAvailable[1]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	printf("\t3. 1pm-3pm");
	if (timeSlotsAvailable[2]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	printf("\t4. 3pm-5pm");
	if (timeSlotsAvailable[3]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	printf("\t5. 5pm-7pm");
	if (timeSlotsAvailable[4]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	printf("\t6. 7pm-9pm");
	if (timeSlotsAvailable[5]) printf(" <Available>\n"); else printf(" <Not Available>\n");

	

	fclose(f);
}

void bookingSeachRecords()
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

// ========================================
// Utilities Functions go below this point
// ========================================
// make sure to initialise first byte of oldBookID to '\0'
void incrementBookingID(char *oldBookID)
{
	// if oldBookID is not initialised, set it to initial value
	if (strlen(oldBookID) == 0)
	{
		strcpy(oldBookID, "B000001");
		return;
	}

	// set pointers for start, end and variable pointer
	char *st = oldBookID;
	char *end = strchr(oldBookID, '\0') - 1;
	char *ptr = end;
	// move the variable pointer to the left until number that is not 9 is found or it had reached the start of string
	while (*ptr == '9' && ptr != st)
	{
		ptr--;
	}
	*ptr = *ptr + 1; // +1 to its value
	ptr++; // move it once to the right
	while (ptr <= end) // fill all values in RHS to 0 until end is reached
	{
		*ptr = '0';
		ptr++;
	}
}

void askUserForBookingDate(Date *userPickedDate)
{
	int r; // r to check scanf() result
	do {
		if (err)
		{
			printf("Invalid Date, try again.\n");
		}
		err = 1;
		printf("Booking Date ? <dd/mm/yyyy>");
		rewind(stdin);
		r = scanf("%d/%d/%d", &userPickedDate->d, &userPickedDate->m, &userPickedDate->y);
		rewind(stdin);
	} while (r != 3 || !validateDate(userPickedDate->d, userPickedDate->m, userPickedDate->y));
	err = 0; // always reset error code after use
}

// Run through struct array to check what time slots is available
// Set timeslot to 0 if the timeslot is not free
// timeslot array need to be size 6 (6 timeslots stated)
void checkForTimeslotsAvailablity(int *timeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID)
{
	for (int a = 0; a < dataSize; a++)
	{
		if (strcmp(data[a].facilityID, facilityID) == 0
			&& compareDate(data[a].bookingDate.d, data[a].bookingDate.m, data[a].bookingDate.y, bookingDate->d, bookingDate->m, bookingDate->y) == 0)
		{
			for (int b = 0; b < 6; b++)
			{
				if (data[a].timeSlotsBooked[b]) // if this slot is booked
				{
					timeslot[b] = 0;
				}
			}
		}
	}
}
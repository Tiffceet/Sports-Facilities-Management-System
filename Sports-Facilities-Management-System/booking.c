#include "booking.h"
#include "stdcxx.h"

// Unable to move initialisation to booking.h ? 
// initialise timeslots
const char TIMESLOTS[6][15] = { "7am - 9am", "9am - 11am", "1pm - 3pm", "3pm - 5pm", "5pm - 7pm", "7pm - 9pm" };
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
		bookingBook(); // add do while loop to ask user if want to book mores
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		bookingDisplayAll();
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
	printf(" =====================================================================================================================\n");
	printf(" |                                                   Booking Info                                                    |\n");
	printf(" =====================================================================================================================\n");
	printf(" | 1. Please refrain from monopolising facility by making booking for a whole day                                    |\n");
	printf(" | 2. Booking for multiple time slots is allowed                                                                     |\n");
	printf(" | 3. Timeslots as follows:                                                                                          |\n");
	printf(" |      - Weekdays (Mon - Fri) < 7am-9am, 9am-11am, 1pm-3pm, 3pm-5pm, 5pm-7pm, 7pm-9pm >                             |\n");
	printf(" |      - Weekends (Sat & Sun) < 7am-9am, 9am-11am, 1pm-3pm, 3pm-5pm                   >                             |\n");
	printf(" | 4. Please proceed to payment counter after booking                                                                |\n");
	printf(" |                                                                                                                   |\n");
	printf(" =====================================================================================================================\n");
	printf(" =====================================================================================================================\n\n");
}

void bookingBook()
{
	// Variables to be used
	BookingData data[100];
	char userPickedfacilityID[100];
	Date userPickedDate; // Booking Date
	int userPickedtimeslot;
	int isSet[] = { 0, 0, 0 }; // to keep track of what details have been given and what have not	

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
	// if file doesnt exist, open in write mode
	if (chkFileExist(f))
	{
		while (fscanf(f, "%[^,]%*[^\n]\n", &latestBookingID) != EOF);
		fclose(f); // if file exist, means its pointer is not closed -> refer to chkFileExist()
	}

	int count = readBookingDataIntoStructArray(&data[0], 100); // read file into struct array + get entries count

	incrementBookingID(latestBookingID); // increment bookingID
	printBookingInfo();

	// Sub Menu
	char choice[10];
	do{
		char facilityStatus[100], bookingDateStatus[100], timeslotStatus[100];
		if (isSet[0]) strcpy(facilityStatus, userPickedfacilityID); else strcpy(facilityStatus, "<!> Not Set <!>");
		if (isSet[1]) sprintf(bookingDateStatus, "%02d/%02d/%04d", userPickedDate.d, userPickedDate.m, userPickedDate.y); else strcpy(bookingDateStatus, "<!> Not Set <!>");
		if (isSet[2]) strcpy(timeslotStatus,TIMESLOTS[userPickedtimeslot]); else strcpy(timeslotStatus, "<!> Not Set <!>");
		printf(" <----------------------------------------------------->\n");
		printf(" ->                  Booking Details                  <-\n");
		printf(" <----------------------------------------------------->\n");
		printf(" | Facility     : %-36.36s |\n", facilityStatus);
		printf(" | Booking Date : %-36.36s |\n", bookingDateStatus);
		printf(" | Timeslot     : %-36.36s |\n", timeslotStatus);
		printf(" <----------------------------------------------------->\n\n");
		printf(" Select: \n");
		printf(" \t[1] Change Facility\n");
		printf(" \t[2] Change Booking Date\n");
		printf(" \t[3] Change Timeslot\n");
		printf(" \t[4] Comfirm Booking\n");
		printf(" \t[5] Cancel Booking\n\n");
		printf(" Choice ? ");
		getUserMenuChoice(choice, 9, " Invalid Choice, try again.\n Choice ? ");
		switch (choice[0])
		{
		case '1':
			bipChangeFacility(userPickedfacilityID);
			isSet[0] = 1;
			isSet[2] = 0;
			break;
		case '2':\
			bipChangeBookingDate(&userPickedDate);
			isSet[1] = 1;
			isSet[2] = 0;
			break;
		case '3':
			if (!isSet[0])
			{
				printf("\n<!> ERR: No Facility have been chosen. <!>\n");
				system("pause");
				break;
			}
			if (!isSet[1])
			{
				printf("\n<!> ERR: Booking Date have not been determined. <!>\n");
				system("pause");
				break;
			}
			isSet[2] = bipChangeTimeslot(&userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID);
			break;
		case '4':
			if (!isSet[0])
			{
				printf("\n<!> ERR: No Facility have been chosen. <!>\n");
				system("pause");
				break;
			}
			if (!isSet[1])
			{
				printf("\n<!> ERR: Booking Date have not been determined. <!>\n");
				system("pause");
				break;
			}
			if (!isSet[2])
			{
				printf("\n<!> ERR: Timeslot have not been selected. <!>\n");
				system("pause");
				break;
			}
			// NEED TO FKING ADD COMFIRMATIONA AND WHOLE LOT OF SHIT
			
			printf("Please read the booking details again for confirmation. (Y=Comfirm) ? ");
			char bookingComfirmChoice[10];
			getUserMenuChoice(bookingComfirmChoice, 9, "Please read the booking details again for confirmation. (Y=Comfirm) ? ");
			if (tolower(bookingComfirmChoice[0]) != 'y')
			{
				break;
			}

			// Gather all info
			strcpy(data[count].bookingID, latestBookingID);
			getSystemDate(&data[count].currentDate);
			getSystemTime(&data[count].currentTime);
			data[count].bookingDate.d = userPickedDate.d;
			data[count].bookingDate.m = userPickedDate.m;
			data[count].bookingDate.y = userPickedDate.y;
			data[count].timeSlotsBooked[userPickedtimeslot] = 1;
			strcpy(data[count].usrID, "U0001");
			strcpy(data[count].staffID, "S0001");
			strcpy(data[count].facilityID, userPickedfacilityID);
			writeBookingDataIntoFile(&data[0], count + 1);
			return;
		case '5':
			return;
		default:
			printf("\n<!> ERR: Please select number between 1 - 5 <!>\n\n");
			system("pause");
		}
	} while (1);
	// End of Sub Menu	
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
		printf("\n<!> ERR: No records found. <!>\n");
		system("pause");
		return;
	}
	fclose(f);
	BookingData data[100];
	int count = readBookingDataIntoStructArray(&data[0], 100);
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "|                                               Booking Transactions                                                 |");
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "| DateofTransaction BookingID BookingDate TimeslotBooked FacilityBooked                 Booked by    Registered by   |");
	printf("%s\n", "|--------------------------------------------------------------------------------------------------------------------|");
	// Sample
	/*printf("| %02d/%02d/%-04d %02d:%02d  %-8.7s  %02d/%02d/%-05d %-14.14s %-30.30s %-12.12s %-15.15s |\n",
		2,2,2014,20,30,
		"B000001",
		4,4,2014,
		TIMESLOTS[1],
		"Badminton Court",
		"User",
		"Staff");*/
	for (int a = 0; a < count; a++)
	{
		printf("| %02d/%02d/%-04d %02d:%02d  %-8.7s  %02d/%02d/%-05d %-14.14s %-30.30s %-12.12s %-15.15s |\n",
			data[a].currentDate.d, data[a].currentDate.m, data[a].currentDate.y, data[a].currentTime.h, data[a].currentTime.m,
			data[a].bookingID,
			data[a].bookingDate.d, data[a].bookingDate.m, data[a].bookingDate.y,
			TIMESLOTS[getTimeslotBooked(data[a].timeSlotsBooked)],
			data[a].facilityID,
			data[a].usrID,
			data[a].staffID);
	}
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "======================================================================================================================");
	printf("\n%d record(s) found. \n", count);
	system("pause");
}

// ============================================================================================
// Utilities & Sub Functions go below this point
// ============================================================================================
// make sure to initialise first byte of oldBookID to '\0'

// Return amount of data entries found
// Do fclose() before calling this function
int readBookingDataIntoStructArray(BookingData *data, int size)
{
	FILE *f = fopen(bookingFilePath, "r");
	if (!chkFileExist(f))
	{
		return 0;
	}
	int count = 0;
	while (fscanf(f, "%[^,],%d/%d/%d,%d:%d:%d,%d/%d/%d,%d,%d,%d,%d,%d,%d,%[^,],%[^,],%[^\n]\n",
		data[count].bookingID,
		&data[count].currentDate.d,
		&data[count].currentDate.m,
		&data[count].currentDate.y,
		&data[count].currentTime.h,
		&data[count].currentTime.m,
		&data[count].currentTime.s,
		&data[count].bookingDate.d,
		&data[count].bookingDate.m,
		&data[count].bookingDate.y,
		&data[count].timeSlotsBooked[0],
		&data[count].timeSlotsBooked[1],
		&data[count].timeSlotsBooked[2],
		&data[count].timeSlotsBooked[3],
		&data[count].timeSlotsBooked[4],
		&data[count].timeSlotsBooked[5],
		data[count].usrID,
		data[count].staffID,
		data[count].facilityID
	) != EOF) {
		count++;
	}
	fclose(f);
	return count;
}

void writeBookingDataIntoFile(BookingData *data, int dataCount)
{
	FILE *f = fopen(bookingFilePath, "w");
	for (int a = 0; a < dataCount; a++)
	{
		fprintf(f, "%s,%d/%d/%d,%d:%d:%d,%d/%d/%d,%d,%d,%d,%d,%d,%d,%s,%s,%s\n",
			data[a].bookingID,
			data[a].currentDate.d,
			data[a].currentDate.m,
			data[a].currentDate.y,
			data[a].currentTime.h,
			data[a].currentTime.m,
			data[a].currentTime.s,
			data[a].bookingDate.d,
			data[a].bookingDate.m,
			data[a].bookingDate.y,
			data[a].timeSlotsBooked[0],
			data[a].timeSlotsBooked[1],
			data[a].timeSlotsBooked[2],
			data[a].timeSlotsBooked[3],
			data[a].timeSlotsBooked[4],
			data[a].timeSlotsBooked[5],
			data[a].usrID,
			data[a].staffID,
			data[a].facilityID
			);
	}
	fclose(f);
}

// Starts with B000001
// To prevent invalid string, please set oldBookID[0] = '\0' before passing it to this function
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

// Run through struct array to check what time slots is available
// Set timeslot to 0 if the timeslot is not free
// timeslot array need to be size 6 (6 timeslots stated)
// Return True if there are timeslots available
int checkForTimeslotsAvailablity(int *timeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID)
{
	// make sure timeslot is properly initialised
	timeslot[0] = 1; timeslot[1] = 1; timeslot[2] = 1; timeslot[3] = 1; timeslot[4] = 1; timeslot[5] = 1;
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
	for (int a = 0; a < 6; a++)
	{
		if (timeslot[a]) // if any of the timeslot is available
		{
			return 1;
		}
	}
	return 0;
}

// Return the first idx that timeslot is 1
int getTimeslotBooked(int *timeslot)
{
	for (int a = 0; a < 6; a++)
	{
		if (timeslot[a]) 
		{
			return a;
		}
	}
	return -1;
}
// ============================================================================================
// ============================================================================================

// ============================================================================================
// Functions for BIP (Book-In-Progress)
// ============================================================================================

// Return 1 if facility change successfully
int bipChangeFacility(char *userPickedfacilityID)
{
	// Ask user to select facility
	printf("Select one of the following facilities: \n");
	/*
	Insert code to get all facilities
	Need to count how many facilities are there?
	*/
	printf("\nEnter the facility ID you wish to book: ");
	s_input(userPickedfacilityID, 99);
	/*
	Insert code to check for facilities availablity
	*/
	return 1;
}

// Return 1 if bookingDate changed successfully
int bipChangeBookingDate(Date *bookingDate)
{
	// If available, ask user for date
	Date currentDate;
	getSystemDate(&currentDate);
	int dateErr = 0;
	int r; // r to check scanf() result
	do {
		if (dateErr)
		{
			printf("Invalid Date, try again.\nDo note that booking on today is not allowed.\n");
		}
		dateErr = 1;
		printf("Booking Date ? <dd/mm/yyyy> ");
		rewind(stdin);
		r = scanf("%d/%d/%d", &bookingDate->d, &bookingDate->m, &bookingDate->y);
		rewind(stdin);
	} while (r != 3 ||
		!validateDate(bookingDate->d, bookingDate->m, bookingDate->y) ||
		compareDate(bookingDate->d, bookingDate->m, bookingDate->y, currentDate.d, currentDate.m, currentDate.y) != 1
		);
	err = 0;
	return 1;
}

// return 1 if timeslot is changed successfully
int bipChangeTimeslot(int *userPickedtimeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID)
{	
	int timeslotAvailable[6] = { 1,1,1,1,1,1 }; // to check for timeslot availablity
	if(!checkForTimeslotsAvailablity(timeslotAvailable, data, dataSize, bookingDate, facilityID)){
		printf("Sorry, but there are no free timeslots on that day for that facility, please try other facility / date\n");
		return 0;
	}
	printf("Timeslots: \n");
	printf("\t1. 7am-9am ");
	if (timeslotAvailable[0]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	printf("\t2. 9am-11am");
	if (timeslotAvailable[1]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	printf("\t3. 1pm-3pm ");
	if (timeslotAvailable[2]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	printf("\t4. 3pm-5pm ");
	if (timeslotAvailable[3]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	printf("\t5. 5pm-7pm ");
	if (timeslotAvailable[4]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	printf("\t6. 7pm-9pm ");
	if (timeslotAvailable[5]) printf(" <Available>\n"); else printf(" <Not Available>\n");

	// NOTE TO MYSELF: LOL I HAVE THIS WEIRD SHIT CRITERIA WHERE IF ITS WEEKENDS THEN NO BOOKING FOR USER REEEEE
	char userPickedtimeslotSTR[10]; // for string input
	do {
		if (err)
		{
			printf("Timeslot you have chosen is not available.\nPlease pick another timeslot.\n\n");
		}
		do {
			if (err)
			{
				printf("Please select timeslot from 1 - 6\n");
			}
			err = 1;
			printf("Please, pick a timeslot(1-6): ");
			getUserMenuChoice(userPickedtimeslotSTR, 9, "Invalid selection.\nPlease, pick a timeslot(1-6): ");

		} while (userPickedtimeslotSTR[0] < '1' || userPickedtimeslotSTR[0] > '6');
		err = 1;
		*userPickedtimeslot = strtol(userPickedtimeslotSTR, NULL, 10) - 1;
	} while (!timeslotAvailable[*userPickedtimeslot]); // while that timeslot is booked
	err = 0;
	return 1;
}
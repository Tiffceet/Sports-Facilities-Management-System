#include "booking.h"
#include "stdcxx.h"
#include "facility.h"
#include "fusage.h"
#include "staff.h"
#include "userinfo.h"

// Unable to move initialisation to booking.h ? 
// initialise timeslots
const char TIMESLOTS[6][15] = { "7am - 9am ", "9am - 11am", "1pm - 3pm ", "3pm - 5pm ", "5pm - 7pm ", "7pm - 9pm " };
void bookingMain()
{
	readDataFromOtherModules();

	// initialise error code for input validation use
	err = 0;
	sessionStaffID[0] = '\0';
	// prompt staff login
	if (!_staffLogin(sessionStaffID, 99))
	{
		return;
	}
	// while menu() doesnt return 0 = continue running
	while (bookingMenu())
	{
		continue;
	}
}

int bookingMenu()
{
	char choiceText[][100] = { "Book", "Search bookings", "Modify bookings", "Display all bookings", "Log Out (Return to console)" };
	int choice = globalMainMenu("Booking Module", 5, choiceText);
	if (choice > 0 && choice < 6)
	{
		mode = 'u'; // set userMode
	}
	if (choice < 0 && choice > -6)
	{
		mode = 's'; // set staffMode
	}
	char ch[10];
	switch (choice) // calling math.abs might be a better workaround
	{
	case 1:
	case -1:
		bookingBook();
		break;
	case 2:
	case -2:
		bookingSearchRecords(0, NULL, NULL, 1, NULL, NULL, NULL); // null because i dont want raw records only
		break;
	case 3:
	case -3:
		bookingModifyRecords();
		break;
	case 4:
	case -4:
		bookingDisplayAll();
		break;
	case 5:
	case -5:
		sessionStaffID[0] = '\0';
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
	printf(" |      < 7am-9am, 9am-11am, 1pm-3pm, 3pm-5pm, 5pm-7pm, 7pm-9pm >                                                    |\n");
	printf(" | 4. Only registered users are allowed to make booking                                                              |\n");
	printf(" | 5. Every booking needs to be handled by 1 staff                                                                   |\n");
	printf(" =====================================================================================================================\n");
	printf(" =====================================================================================================================\n\n");
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

	char loginUserID[100] = "null"; // initialise so when booking is done in staff mode, it wont write corrupted data into file
	if (mode == 'u') {
		printf("Only registered user are allowed to make booking.\n");
		if (!_usrLogin(loginUserID, 99))
		{
			return;
		}
	}
	else if (mode == 's')
	{
		if (!_staffPWReauth())
		{
			return;
		}
	}

	char userPickedfacilityID[100];
	Date userPickedDate; // Booking Date
	int userPickedtimeslot;
	// find latestBooking ID + count of items in file
	char latestBookingID[10];
	latestBookingID[0] = '\0';
	int count = readBookingDataIntoStructArray(&data[0], 100); // read file into struct array + get entries count
	if (count != 0) // if file exist
	{
		strcpy(latestBookingID, data[count - 1].bookingID);
	}

	incrementBookingID(latestBookingID); // increment bookingID

	// Sub Menu goes here
	printBookingInfo();
	char statusText[3][100]; // to be used to show booking details after first iteration

	char choice[10];
	char choiceToContinueNextBooking[10] = "\0";
	do {
		if (tolower(choiceToContinueNextBooking[0]) == 'y')
		{
			incrementBookingID(latestBookingID); // increment bookingID
		}
		int firstIteration = 1;
		do {
			// Main Logic
			if (firstIteration)
			{
				bipChangeFacility(userPickedfacilityID);
				bipChangeBookingDate(&userPickedDate);
				bipChangeTimeslot(0, &userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID, "");
				firstIteration = 0;
			}
			else
			{
				printf(" Select: \n");
				printf(" \t[1] Change Facility\n");
				printf(" \t[2] Change Booking Date + Timeslot\n");
				printf(" \t[3] Change Timeslot only\n");
				printf("\n Your Choice ? ");
				do {
					getUserMenuChoice(choice, 9, "Your Choice ? ");
				} while (choice[0] < '1' || choice[0] > '3');
				switch (choice[0])
				{
				case '1':
					bipChangeFacility(userPickedfacilityID);
					// temporary variable for checking timeslot availablity
					int tmpTS[6] = { 0,0,0,0,0,0 };
					int tmpR = checkOverallTimeslotsAvailablity(&tmpTS[0], &data[0], count, &userPickedDate, getFacilityByID(userPickedfacilityID)->name);
					if (!tmpR) // if no timeslot anymore
					{
						printf("There are no available timeslots on booking date.\n Please re-select date + timeslot.\n");
						bipChangeBookingDate(&userPickedDate);
						bipChangeTimeslot(1, &userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID, "");
					}
					else if (!tmpTS[userPickedtimeslot]) // if the timeslot picked is full
					{
						printf("The timeslot you picked is unavailable.\n Please re-select date + timeslot.\n");
						bipChangeBookingDate(&userPickedDate);
						bipChangeTimeslot(1, &userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID, "");
					}
					printf("Is the booking date %02d/%02d/%04d correct ? (y=yes) ", userPickedDate.d, userPickedDate.m, userPickedDate.y);
					getUserMenuChoice(choice, 9, "Is the booking date %02d/%02d/%04d correct ? (y=yes) ");
					if (tolower(choice[0]) != 'y')
					{
						bipChangeBookingDate(&userPickedDate);
						bipChangeTimeslot(1, &userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID, "");
					}
					break;
				case '2':
					bipChangeBookingDate(&userPickedDate);
					bipChangeTimeslot(1, &userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID, "");
					break;
				case '3':
					bipChangeTimeslot(1, &userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID, "");
					break;
				}
			}

			// printing of display
			sprintf(statusText[0], "(%s) %s",userPickedfacilityID, getFacilityByID(userPickedfacilityID)->name);
			sprintf(statusText[1], "%02d/%02d/%04d", userPickedDate.d, userPickedDate.m, userPickedDate.y);
			strcpy(statusText[2], TIMESLOTS[userPickedtimeslot]);

			printf(" <----------------------------------------------------->\n");
			printf(" ->                  Booking Details                  <-\n");
			printf(" <----------------------------------------------------->\n");
			printf(" | Facility     : %-36.36s |\n", statusText[0]);
			printf(" | Booking Date : %-36.36s |\n", statusText[1]);
			printf(" | Timeslot     : %-36.36s |\n", statusText[2]);
			printf(" <----------------------------------------------------->\n\n");

			printf(" Do you want to change booking details ? (y=yes) ");
			getUserMenuChoice(choice, 9, " Do you want to change booking details ? (y=yes) ");
		} while (tolower(choice[0]) == 'y');
		printf("Comfirm booking ? (y=yes) ");
		getUserMenuChoice(choice, 9, "Comfirm booking ? (y=yes) ");
		if (tolower(choice[0]) == 'y')
		{
			// Gather all info
			strcpy(data[count].bookingID, latestBookingID);
			getSystemDate(&data[count].currentDate);
			getSystemTime(&data[count].currentTime);
			data[count].bookingDate.d = userPickedDate.d;
			data[count].bookingDate.m = userPickedDate.m;
			data[count].bookingDate.y = userPickedDate.y;
			data[count].timeSlotsBooked[userPickedtimeslot] = 1;
			strcpy(data[count].usrID, loginUserID);
			// strcpy(data[count].staffID, "S0001");
			strcpy(data[count].staffID, sessionStaffID);
			strcpy(data[count].facilityID, userPickedfacilityID);
			// Important line here
			writeBookingDataIntoFile(&data[0], ++count);

			printf("Booking have been handled by %s.\nThank you, %s for booking %s at %02d/%02d/%02d %s.\n",
				// data[count - 1].staffID,
				getStaffDataByID(data[count - 1].staffID)->stfName,
				// data[count - 1].usrID,
				getUserDataByID(data[count - 1].usrID)->name,
				// data[count - 1].facilityID,
				getFacilityByID(data[count - 1].facilityID)->name,
				data[count - 1].bookingDate.d,
				data[count - 1].bookingDate.m,
				data[count - 1].bookingDate.y,
				TIMESLOTS[getTimeslotBooked(data[count - 1].timeSlotsBooked)]
			);
			system("pause");
			break;
		}

		printf("Would you like to continue a new booking ? (y=yes) ");
		getUserMenuChoice(choiceToContinueNextBooking, 9, "Would you like to continue a new booking ? (y=yes) ");
	} while (tolower(choiceToContinueNextBooking[0]) == 'y');
}

// NOTE: showRawRecordsOnly is a flag if want to allow user to pick record to show more details
// NOTE: requireUserLogin is a flag to tell the function should it run login on user, will read from passedUID for last user log on
// If showRawRecordsOnly is 1, then it will not ask user to pick record to show more details
// Will write filteredRecords into pointer array and filteredRecordsCount if showRawRecordsOnly is true (just in case someday the filteredRecords can be further used
// writing to filteredRecords BASED on data passed on, not a new data array
void bookingSearchRecords(int showRawRecordsOnly, BookingData **filteredRecords, int *filteredRecordsCount, int requireUserLogin, char passedUID[], BookingData *passedData, int passedDataCount)
{
	// Variables
	Date dotFrom = { 0,0,0 }, dotTo = { 0,0,0 }, bookFrom = { 0,0,0 }, bookTo = { 0,0,0 };
	int timeslot[6] = { 0,0,0,0,0,0 }; // for TimeslotBooked
	BookingData data[100];
	BookingData *filteredData[100];
	Facility *facFilter[100];
	Staff *staffFilter[100];
	userData *userFilter[100];
	int sCount = 0, uCount = 0, fCount = 0;
	int filteredDataCount;
	int count = readBookingDataIntoStructArray(&data[0], 100);

	char userID[100];
	userID[0] = '\0';
	// logins
	if(requireUserLogin){
		if (mode == 'u') // user mode
		{
			if (!_usrLogin(userID, 100))
			{
				return;
			}
		}
		else if (mode == 's') // staff mode
		{
			if (!_staffPWReauth())
			{
				return;
			}
		}
	}
	else
	{
		strcpy(userID, passedUID); // copy last log on user id to the current user id if user login is not required
	}

	// inputs variable
	char choice[10];
	int userPickedDataToViewIDX = -1;

	// Variables for sub menu
	int isSet[6] = { 0,0,0,0,0,0 };
	if (mode == 'u') // if it is on user mode, there should be exactly one entry in user filter
	{
		isSet[5] = 1;
		userFilter[0] = getUserDataByID(userID);
		uCount = 1;
	}

	do {
		char statusText[6][100] = { "","","" ,"" ,"" ,"" };
		userPickedDataToViewIDX = -1;
		if (isSet[0]) sprintf(statusText[0], "%02d/%02d/%04d - %02d/%02d/%04d", dotFrom.d, dotFrom.m, dotFrom.y, dotTo.d, dotTo.m, dotTo.y);
		if (isSet[1]) sprintf(statusText[1], "%02d/%02d/%04d - %02d/%02d/%04d", bookFrom.d, bookFrom.m, bookFrom.y, bookTo.d, bookTo.m, bookTo.y);
		if (isSet[2])
		{
			for (int a = 0; a < 6; a++)
			{
				if (timeslot[a])
				{
					if (getTimeslotArrayCount(timeslot) < 2) {
						sprintf(statusText[2], "%s", TIMESLOTS[a]);
					}
					else
					{
						sprintf(statusText[2], "%s, %s", statusText[2], TIMESLOTS[a]);
					}
				}
			}
		}
		if (isSet[3])
		{
			for (int a = 0; a < fCount; a++)
			{
				if (a == 0) {
					sprintf(statusText[3], "(%s) %s", facFilter[a]->id, facFilter[a]->name);
				}
				else
				{
					sprintf(statusText[3], "%s, (%s) %s", statusText[3], facFilter[a]->id, facFilter[a]->name);
				}
			}
		}
		if (isSet[4]) {
			for (int a = 0; a < sCount; a++)
			{
				if (a == 0) {
					sprintf(statusText[4], "%s", staffFilter[a]->stfName);
				}
				else
				{
					sprintf(statusText[4], "%s, %s", statusText[4], staffFilter[a]->stfName);
				}
			}
		}
		if (isSet[5])
		{
			for (int a = 0; a < uCount; a++)
			{
				if (a == 0) {
					sprintf(statusText[5], "%s", userFilter[a]->name);
				}
				else
				{
					sprintf(statusText[5], "%s, %s", statusText[5], userFilter[a]->name);
				}
			}
		}
		printf("\n[ Search Criteria ]\n");
		printf("[1] Date of Transactions : %s\n", statusText[0]);
		printf("[2] Booking Date         : %s\n", statusText[1]);
		printf("[3] TimeslotBooked       : %s\n", statusText[2]);
		printf("[4] FacilityBooked       : %s\n", statusText[3]);
		printf("[5] Staff involved       : %s\n", statusText[4]);
		printf("[6] User Involved        : %s\n", statusText[5]);
		printf("[7] Exit to Menu\n");
		printf("\nEnter 'X' to search based on the criteria given.\n\nSet search criteria (1-6) (7 to exit)? ");
		getUserMenuChoice(choice, 9, "Set search criteria (1-6) (7 to exit)? ");
		switch (choice[0])
		{
		case '1':
			isSet[0] = dispfilterDOT(&isSet[0], &dotFrom, &dotTo);
			break;
		case '2':
			isSet[1] = dispfilterBookingDate(&bookFrom, &bookTo);
			break;
		case '3':
			isSet[2] = dispfilterTimeslotBooked(&timeslot[0]);
			break;
		case '4':
			isSet[3] = dispFilterFacInvolved(facFilter, &fCount);
			break;
		case '5':
			isSet[4] = dispFilterStaffInvovled(staffFilter, &sCount);
			break;
		case '6':
			if (mode == 's')
			{
				isSet[5] = dispFilterUserInvolved(userFilter, &uCount);
			}
			else
			{
				printf("User are not authorised to search bookings of other user.\n");
				system("pause");
			}
			break;
		case '7':
			return;
		case 'x':
		case 'X':
			

			// check if caller function wants to showRawDataOnly
			if (showRawRecordsOnly)
			{
				filteredDataCount = generateFilteredSearchResult(filteredData, passedData, passedDataCount, &isSet[0], &dotFrom, &dotTo, &bookFrom, &bookTo, &timeslot[0], staffFilter, sCount, userFilter, uCount, facFilter, fCount);
				// write it to filteredRecords as output parameter just incase the result is used somewhere
				for (int a = 0; a < filteredDataCount; a++)
				{
					filteredRecords[a] = filteredData[a];
				}
				*filteredRecordsCount = filteredDataCount;
				return;
			}
			else
			{
				// this needs to be seperated because filteredData should based on different set of data if showRawRecordsOnly is true
				filteredDataCount = generateFilteredSearchResult(filteredData, &data[0], count, &isSet[0], &dotFrom, &dotTo, &bookFrom, &bookTo, &timeslot[0], staffFilter, sCount, userFilter, uCount, facFilter, fCount);
			}

			// extra check to make sure there are data to let user select
			if (filteredDataCount != 0) {
				do {
					printf("\nEnter '0' to return to search criteria selections.\nSelect (%d-%d) to view more details. ", 1, filteredDataCount);
				} while (!i_input(&userPickedDataToViewIDX) || (userPickedDataToViewIDX < 0 || userPickedDataToViewIDX > filteredDataCount));
				if (userPickedDataToViewIDX == 0)
				{
					break;
				}
				else
				{
					printBookingDetails(filteredData[userPickedDataToViewIDX - 1]->bookingID, &data[0], 100);
				}
			}
			break;
		}
	} while (tolower(choice[0]) != '7'); // while(1) works too because case'7': return;
}

// generate & print filtered result and ask user to pick specific data to view its details
// return numbers of filtered result found
int generateFilteredSearchResult(BookingData **filteredData, BookingData *data, int dataCount, int *isSet, Date *dotFrom, Date *dotTo, Date *bookFrom, Date *bookTo, int *timeslot, Staff **staffFilter, int sCount, userData **userFilter, int uCount, Facility **facFilter, int fCount)
{
	int count = 0; // to keep track of how many records were printed
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "|                                               Booking Transactions                                                 |");
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "| No. | DateofTransaction BookingID BookingDate TimeslotBooked FacilityBooked           Booked by    Registered by   |");
	printf("%s\n", "|--------------------------------------------------------------------------------------------------------------------|");
	for (int a = 0; a < dataCount; a++)
	{
		if (isSet[0]) // Date of transaction filter is set
		{
			// If date is not in range
			if (compareDate(data[a].currentDate.d, data[a].currentDate.m, data[a].currentDate.y, dotFrom->d, dotFrom->m, dotFrom->y) == -1
				|| compareDate(data[a].currentDate.d, data[a].currentDate.m, data[a].currentDate.y, dotTo->d, dotTo->m, dotTo->y) == 1)
			{
				continue;
			}
		}
		if (isSet[1]) // Booking Date filter is set
		{
			// If date is not in range
			if (compareDate(data[a].bookingDate.d, data[a].bookingDate.m, data[a].bookingDate.y, bookFrom->d, bookFrom->m, bookFrom->y) == -1
				|| compareDate(data[a].bookingDate.d, data[a].bookingDate.m, data[a].bookingDate.y, bookTo->d, bookTo->m, bookTo->y) == 1)
			{
				continue;
			}
		}
		if (isSet[2]) // If timeslot booked filter is set
		{
			if (!timeslot[getTimeslotBooked(data[a].timeSlotsBooked)]) // if that timeslot is not selected
			{
				continue;
			}
		}
		if (isSet[3]) // if facility filter is set
		{
			int found = 0;
			for (int b = 0; b < fCount; b++) {
				if (strcmp(data[a].facilityID, facFilter[b]->id) == 0)
				{
					found = 1;
					break;
				}
			}
			if (!found)
			{
				continue;
			}
		}
		if (isSet[4]) // if staff filter is set
		{
			int found = 0;
			for (int b = 0; b < sCount; b++) {
				if (strcmp(data[a].staffID, staffFilter[b]->stfID) == 0)
				{
					found = 1;
					break;
				}
			}
			if (!found)
			{
				continue;
			}
		}
		if (isSet[5]) // if user filter is set
		{
			int found = 0;
			for (int b = 0; b < uCount; b++)
			{
				if (strcmp(data[a].usrID, userFilter[b]->id) == 0)
				{
					found = 1;
					break;
				}
			}
			if (!found)
			{
				continue;
			}
		}

		printf("| %-3d | %02d/%02d/%-04d %02d:%02d  %-8.7s  %02d/%02d/%-05d %-14.14s %-5.5s-%-18.18s ",
			count + 1,
			data[a].currentDate.d, data[a].currentDate.m, data[a].currentDate.y, data[a].currentTime.h, data[a].currentTime.m,
			data[a].bookingID,
			data[a].bookingDate.d, data[a].bookingDate.m, data[a].bookingDate.y,
			TIMESLOTS[getTimeslotBooked(data[a].timeSlotsBooked)],
			data[a].facilityID,
			getFacilityByID(data[a].facilityID)->name);
		userData *usrData;
		if (usrData = getUserDataByID(data[a].usrID))
			printf("%-12.12s", usrData->name);
		else
			printf("%-12.12s", "-");
		printf(" %-15.15s |\n", getStaffDataByID(data[a].staffID)->stfName);
		filteredData[count] = &data[a];
		count++;
	}
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "======================================================================================================================");
	printf("\n%d record(s) found. \n", count);
	return count;
}

void bookingModifyRecords()
{
	BookingData data[100];
	BookingData *filteredData[100];
	int dataCount = readBookingDataIntoStructArray(data, 100);
	int filteredDataCount = 0;
	char choice[10];
	int userPickedIDX = -1;

	// logins
	char userID[100];
	userData *userFilter[2];
	userID[0] = '\0';
	if (mode == 'u') // user mode
	{
		if (!_usrLogin(userID, 100))
		{
			return;
		}
	}
	else if (mode == 's')
	{
		if (!_staffPWReauth())
		{
			return;
		}
	}
	
	printf("Would you like to filter the bookings before selecting records to modify (y=yes)? ");
	getUserMenuChoice(choice, 9, "Would you like to filter the bookings before selecting records to modify (y=yes)? ");
	if (tolower(choice[0]) == 'y')
	{
		// This function have generateFilteredSearchResult() call in it
		bookingSearchRecords(1, filteredData, &filteredDataCount, 0, userID, &data[0], dataCount); 
	}
	else
	{
		// just print all data without filters
		// i didnt use displayAll because i need the numbering infront so user can choose
		int isSet[6] = { 0,0,0,0,0,0 };
		if (mode == 'u')
		{
			userFilter[0] = getUserDataByID(userID);
			isSet[5] = 1;
		}
		filteredDataCount = generateFilteredSearchResult(filteredData, &data[0], dataCount, &isSet[0], NULL, NULL, NULL, NULL, NULL, NULL, NULL, userFilter, 1, NULL, NULL);
	}

	int firstIteration = 1;
	do {
		if (!firstIteration)
		{
			// Printing of filteredResult
			printf("%s\n", "======================================================================================================================");
			printf("%s\n", "|                                               Booking Transactions                                                 |");
			printf("%s\n", "======================================================================================================================");
			printf("%s\n", "| No. | DateofTransaction BookingID BookingDate TimeslotBooked FacilityBooked           Booked by    Registered by   |");
			printf("%s\n", "|--------------------------------------------------------------------------------------------------------------------|");
			for (int a = 0; a < filteredDataCount; a++) {
				printf("| %-3d | %02d/%02d/%-04d %02d:%02d  %-8.7s  %02d/%02d/%-05d %-14.14s %-5.5s-%-18.18s ",
					a + 1,
					filteredData[a]->currentDate.d, filteredData[a]->currentDate.m, filteredData[a]->currentDate.y, filteredData[a]->currentTime.h, filteredData[a]->currentTime.m,
					filteredData[a]->bookingID,
					filteredData[a]->bookingDate.d, filteredData[a]->bookingDate.m, filteredData[a]->bookingDate.y,
					TIMESLOTS[getTimeslotBooked(filteredData[a]->timeSlotsBooked)],
					filteredData[a]->facilityID,
					getFacilityByID(filteredData[a]->facilityID)->name);
				userData *uData;
				if (uData = getUserDataByID(filteredData[a]->usrID))
					printf("%-12.12s", uData->name);
				else
					printf("%-12.12s", "-");
				printf(" %-15.15s |\n", getStaffDataByID(filteredData[a]->staffID)->stfName);
			}
			printf("%s\n", "======================================================================================================================");
			printf("%s\n\n", "======================================================================================================================");
		}
		if (filteredDataCount > 0)
		{
			Date dt;
			getSystemDate(&dt);
			int r; // to keep track of i_input() return val
			do {
				printf("<!> Enter '0' to return to menu <!>\n");
				printf("Select records to modify (%d-%d) ", 1, filteredDataCount);
				r = i_input(&userPickedIDX);
				if (r)
				{
					if (userPickedIDX == 0)
					{
						return;
					}
					if (userPickedIDX > 0 && userPickedIDX <= filteredDataCount && compareDate(dt.d, dt.m, dt.y,
						filteredData[userPickedIDX - 1]->bookingDate.d,
						filteredData[userPickedIDX - 1]->bookingDate.m,
						filteredData[userPickedIDX - 1]->bookingDate.y) != -1) // if booking date is not later than current date, you are not allowed to modify
					{
						printf("You are not allowed to modify booking with booking date before today and today.\n");
						system("pause");
						r = 0;
					}
				}
			} while (!r
				|| userPickedIDX < 1 || userPickedIDX > filteredDataCount);
			modifySpecificBooking(filteredData[userPickedIDX - 1], &data[0], dataCount);
			printf("Do you wish to modify more bookings ? (y=yes) ");
			getUserMenuChoice(choice, 9, "Do you wish to modify more bookings ? (y=yes) ");
		}
		else
		{
			printf("No records was found...\n");
			system("pause");
			return;
		}
		firstIteration = 0;
	} while (tolower(choice[0]) == 'y');
}

// Modify specific booking
// return 1 if it modified successfully
int modifySpecificBooking(BookingData *bookingToModify, BookingData *data, int dataCount)
{
	char choice[10];
	// caching data for changes
	BookingData cache;
	strcpy(cache.bookingID, bookingToModify->bookingID);
	cache.bookingDate.d = bookingToModify->bookingDate.d;
	cache.bookingDate.m = bookingToModify->bookingDate.m;
	cache.bookingDate.y = bookingToModify->bookingDate.y;
	cache.currentDate.d = bookingToModify->currentDate.d;
	cache.currentDate.m = bookingToModify->currentDate.m;
	cache.currentDate.y = bookingToModify->currentDate.y;
	cache.currentTime.h = bookingToModify->currentTime.h;
	cache.currentTime.m = bookingToModify->currentTime.m;
	cache.currentTime.s = bookingToModify->currentTime.s;
	strcpy(cache.facilityID, bookingToModify->facilityID);
	strcpy(cache.staffID, bookingToModify->staffID);
	strcpy(cache.usrID, bookingToModify->usrID);
	for (int a = 0; a < 6; a++)
	{
		cache.timeSlotsBooked[a] = bookingToModify->timeSlotsBooked[a];
	}

	do {
		printf(" Select: \n");
		printf(" \t[1] Change Facility\n");
		printf(" \t[2] Change Booking Date + Timeslot\n");
		printf(" \t[3] Change Timeslot only\n");
		printf("\n Your Choice ? ");
		do {
			getUserMenuChoice(choice, 9, "Your Choice ? ");
		} while (choice[0] < '1' || choice[0] > '3');
		int userPickedtimeslot = getTimeslotBooked(bookingToModify->timeSlotsBooked); // because booking is stored in an array
		switch (choice[0])
		{
		case '1':
			bipChangeFacility(cache.facilityID);
			// temporary variable for checking timeslot availablity
			int tmpTS[6] = { 0,0,0,0,0,0 };
			int tmpR = checkForTimeslotsAvailablity(&tmpTS[0], &data[0], 100, &cache.bookingDate, cache.facilityID, cache.bookingID);
			if (!tmpR) // if no timeslot anymore
			{
				printf("There are no available timeslots on booking date.\n Please re-select date + timeslot.\n");
				bipChangeBookingDate(&cache.bookingDate);
				bipChangeTimeslot(1, &userPickedtimeslot, &data[0], dataCount, &cache.bookingDate, cache.facilityID, cache.bookingID);
			}
			else if (!tmpTS[userPickedtimeslot]) // if the timeslot picked is full
			{
				printf("The timeslot you picked is unavailable.\n Please re-select date + timeslot.\n");
				bipChangeBookingDate(&cache.bookingDate);
				bipChangeTimeslot(1, &userPickedtimeslot, &data[0], dataCount, &cache.bookingDate, cache.facilityID, cache.bookingID);
			}
			printf("Is the booking date %02d/%02d/%04d correct ? (y=yes) ", cache.bookingDate.d, cache.bookingDate.m, cache.bookingDate.y);
			getUserMenuChoice(choice, 9, "Is the booking date %02d/%02d/%04d correct ? (y=yes) ");
			if (tolower(choice[0]) != 'y')
			{
				bipChangeBookingDate(&cache.bookingDate);
				bipChangeTimeslot(1, &userPickedtimeslot, &data[0], dataCount, &cache.bookingDate, cache.facilityID, cache.bookingID);
			}
			break;
		case '2':
			bipChangeBookingDate(&cache.bookingDate);
			bipChangeTimeslot(1, &userPickedtimeslot, &data[0], dataCount, &cache.bookingDate, cache.facilityID, cache.bookingID);
			printf("\n\n%s\n\n", bookingToModify->bookingID);
			break;
		case '3':
			bipChangeTimeslot(1, &userPickedtimeslot, &data[0], dataCount, &cache.bookingDate, cache.facilityID, cache.bookingID);
			break;
		}
		printf(" Do you want to change more booking details ? (y=yes) ");
		getUserMenuChoice(choice, 9, " Do you want to change more booking details ? (y=yes) ");
		// since bipChangetimeslot doesnt directly modify array, i need to do it again
		for (int a = 0; a < 6; a++)
		{
			if (userPickedtimeslot != a)
				cache.timeSlotsBooked[a] = 0;
			else
				cache.timeSlotsBooked[a] = 1;
		}
	} while (tolower(choice[0]) == 'y');
	printf(" <----------------------------------------------------->\n");
	printf(" ->                 OLD Booking Details                <-\n");
	printf(" <----------------------------------------------------->\n");
	printf(" | Facility     : (%-5.5s) %-28.28s |\n", bookingToModify->facilityID, getFacilityByID(bookingToModify->facilityID)->name);
	printf(" | Booking Date : %02d/%02d/%04d%26s |\n", bookingToModify->bookingDate.d, bookingToModify->bookingDate.m, bookingToModify->bookingDate.y, "");
	printf(" | Timeslot     : %-36.36s |\n", TIMESLOTS[getTimeslotBooked(bookingToModify->timeSlotsBooked)]);
	printf(" <----------------------------------------------------->\n\n");
	printf(" <----------------------------------------------------->\n");
	printf(" ->                 NEW Booking Details                <-\n");
	printf(" <----------------------------------------------------->\n");
	printf(" | Facility     : (%-5.5s) %-28.28s |\n", cache.facilityID, getFacilityByID(cache.facilityID)->name);
	printf(" | Booking Date : %02d/%02d/%04d%26s |\n", cache.bookingDate.d, cache.bookingDate.m, cache.bookingDate.y, "");
	printf(" | Timeslot     : %-36.36s |\n", TIMESLOTS[getTimeslotBooked(cache.timeSlotsBooked)]);
	printf(" <----------------------------------------------------->\n\n");
	printf("Comfirm booking modification ? (y=yes) ");
	getUserMenuChoice(choice, 9, "Comfirm booking modification ? (y=yes) ");
	if (tolower(choice[0]) == 'y')
	{
		strcpy(bookingToModify->bookingID, cache.bookingID);
		bookingToModify->bookingDate.d = cache.bookingDate.d;
		bookingToModify->bookingDate.m = cache.bookingDate.m;
		bookingToModify->bookingDate.y = cache.bookingDate.y;
		bookingToModify->currentDate.d = cache.currentDate.d;
		bookingToModify->currentDate.m = cache.currentDate.m;
		bookingToModify->currentDate.y = cache.currentDate.y;
		bookingToModify->currentTime.h = cache.currentTime.h;
		bookingToModify->currentTime.m = cache.currentTime.m;
		bookingToModify->currentTime.s = cache.currentTime.s;
		strcpy(bookingToModify->facilityID, cache.facilityID);
		strcpy(bookingToModify->staffID, cache.staffID);
		strcpy(bookingToModify->usrID, cache.usrID);
		for (int a = 0; a < 6; a++)
		{
			bookingToModify->timeSlotsBooked[a] = cache.timeSlotsBooked[a];
		}
		writeBookingDataIntoFile(&data[0], dataCount);
		return 1;
	}
	return 0;
}


void bookingDisplayAll()
{
	BookingData data[100];
	BookingData *dataToPrint[100];
	char userID[100];
	int count = readBookingDataIntoStructArray(&data[0], 100);
	int dataToPrintCount = 0;
	if (count == 0)
	{
		printf("\n<!> ERR: No records found. <!>\n");
		system("pause");
		return;
	}
	if (mode == 's')
	{
		if (!_staffPWReauth())
		{
			return;
		}
		for (int a = 0; a < count; a++)
		{
			dataToPrint[a] = &data[a];
			dataToPrintCount++;
		}
	}
	else if (mode == 'u')
	{
		if (!_usrLogin(userID, 100))
		{
			return;
		}
		for (int a = 0; a < count; a++)
		{
			if (strcmp(data[a].usrID, userID) == 0)
			{
				dataToPrint[dataToPrintCount++] = &data[a];
			}
		}
	}
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "|                                               Booking Transactions                                                 |");
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "| DateofTransaction BookingID BookingDate TimeslotBooked FacilityBooked                 Booked by    Registered by   |");
	printf("%s\n", "|--------------------------------------------------------------------------------------------------------------------|");
	for (int a = 0; a < dataToPrintCount; a++)
	{
		printf("| %02d/%02d/%-04d %02d:%02d  %-8.7s  %02d/%02d/%-05d %-14.14s %-5.5s-%-24.24s ",
			dataToPrint[a]->currentDate.d, dataToPrint[a]->currentDate.m, dataToPrint[a]->currentDate.y, dataToPrint[a]->currentTime.h, dataToPrint[a]->currentTime.m,
			dataToPrint[a]->bookingID,
			dataToPrint[a]->bookingDate.d, dataToPrint[a]->bookingDate.m, dataToPrint[a]->bookingDate.y,
			TIMESLOTS[getTimeslotBooked(dataToPrint[a]->timeSlotsBooked)],
			// data[a].facilityID,
			dataToPrint[a]->facilityID,
			getFacilityByID(dataToPrint[a]->facilityID)->name);
		userData *usrData;
		if (usrData = getUserDataByID(dataToPrint[a]->usrID)) // if userID is null then print '-', this happens when staff make booking
			printf("%-12.12s", usrData->name);
		else
			printf("%-12.12s", "-");
			
		printf(" %-15.15s |\n", getStaffDataByID(dataToPrint[a]->staffID)->stfName);
	}
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "======================================================================================================================");
	printf("\n%d record(s) found. \n", dataToPrintCount);

	char filterChoice[10];
	printf("\nDo you wish to add filters ? (Y = yes, other to return to menu) ");
	getUserMenuChoice(filterChoice, 9, "Do you wish to add filters ? (Y = yes, other to return to menu) ");
	// Overwrite filteredData into data to simplify bookingDisplayFilter() call
	if (tolower(filterChoice[0]) == 'y')
	{
		if (mode == 's')
			bookingDisplayFilters(data, count, NULL);
		else if (mode == 'u')
			bookingDisplayFilters(data, count, userID);
	}
}

// userID is given if system is running in user mode
void bookingDisplayFilters(BookingData *data, int dataCount, char userID[])
{
	BookingData *filteredData[100];
	int filteredDataCount;
	char retryChoice[10]; // to ask user if user wants to keep on filtering after printing of data

	// Filters to be used
	Date dotFrom, dotTo, bookFrom, bookTo;
	int timeslot[6] = { 0,0,0,0,0,0 }; // for TimeslotBooked

	Facility *facFilter[100];
	Staff *staffFilter[100];
	userData *userFilter[100];
	int fCount = 0, sCount = 0, uCount = 0; // to keep track of how many entries need to be selected
	int isSet[] = { 0,0,0,0,0,0 }; // to keep track of what filters are set

	if (mode == 'u') // if it is on user mode, there should be exactly one entry in user filter
	{
		isSet[5] = 1;
		userFilter[0] = getUserDataByID(userID);
		uCount = 1;
	}

	char filterChoice[10];
	int recordsCount = 0; // to keep track of how many records is printed
	do {
		recordsCount = 0;
		do {
			recordsCount = 0;
			char statusText[6][100] = { "", "", "" , "" , "" , "" };
			if (isSet[0]) sprintf(statusText[0], "%02d/%02d/%04d - %02d/%02d/%04d", dotFrom.d, dotFrom.m, dotFrom.y, dotTo.d, dotTo.m, dotTo.y);
			if (isSet[1]) sprintf(statusText[1], "%02d/%02d/%04d - %02d/%02d/%04d", bookFrom.d, bookFrom.m, bookFrom.y, bookTo.d, bookTo.m, bookTo.y);
			if (isSet[2])
			{
				for (int a = 0; a < 6; a++)
				{
					if (timeslot[a])
					{
						if (getTimeslotArrayCount(timeslot) < 2) {
							sprintf(statusText[2], "%s", TIMESLOTS[a]);
						}
						else
						{
							sprintf(statusText[2], "%s, %s", statusText[2], TIMESLOTS[a]);
						}
					}
				}
			}
			if (isSet[3])
			{
				for (int a = 0; a < fCount; a++)
				{
					if (a == 0) {
						sprintf(statusText[3], "(%s) %s", facFilter[a]->id, facFilter[a]->name);
					}
					else
					{
						sprintf(statusText[3], "%s, (%s) %s", statusText[3], facFilter[a]->id, facFilter[a]->name);
					}
				}
			}
			if (isSet[4]) {
				for (int a = 0; a < sCount; a++)
				{
					if (a == 0) {
						sprintf(statusText[4], "%s", staffFilter[a]->stfName);
					}
					else
					{
						sprintf(statusText[4], "%s, %s", statusText[4], staffFilter[a]->stfName);
					}
				}
			}
			if (isSet[5])
			{
				//for ()
				//{
				//	// if its not the last idx
				//	if(a+1 != uCount) sprintf(statusText[5], "%s, %s", getUserDataByID(userID[a])->name); else sprintf(statusText[5], "%s", getUserDataByID(userID[a])->name);
				//}
				for (int a = 0; a < uCount; a++)
				{
					if (a == 0) {
						sprintf(statusText[5], "%s", userFilter[a]->name);
					}
					else
					{
						sprintf(statusText[5], "%s, %s", statusText[5], userFilter[a]->name);
					}
				}
			}
			printf("\n[ Filters ]\n");
			printf("[1] Date of Transactions : %s\n", statusText[0]);
			printf("[2] Booking Date         : %s\n", statusText[1]);
			printf("[3] TimeslotBooked       : %s\n", statusText[2]);
			printf("[4] FacilityBooked       : %s\n", statusText[3]);
			printf("[5] Staff involved       : %s\n", statusText[4]);
			printf("[6] User Involved        : %s\n", statusText[5]);
			printf("[7] Exit to Menu\n");
			printf("\nEnter 'X' to apply filters\n\nAdd/Change Filter (1-6) (7 to exit)? ");
			getUserMenuChoice(filterChoice, 9, "Add/Change Filter (1-6) (7 to exit)? ");
			switch (filterChoice[0])
			{
			case '1':
				isSet[0] = dispfilterDOT(&isSet[0], &dotFrom, &dotTo);
				break;
			case '2':
				isSet[1] = dispfilterBookingDate(&bookFrom, &bookTo);
				break;
			case '3':
				isSet[2] = dispfilterTimeslotBooked(&timeslot[0]);
				break;
			case '4':
				isSet[3] = dispFilterFacInvolved(facFilter, &fCount);
				break;
			case '5':
				isSet[4] = dispFilterStaffInvovled(staffFilter, &sCount);
				break;
			case '6':
				if (mode == 's')
				{
					isSet[5] = dispFilterUserInvolved(userFilter, &uCount);
				}
				else
				{
					printf("User are not authorised to search bookings of other user.\n");
					system("pause");
				}
				break;
			case '7':
				return;
			case 'X':
			case 'x':
				filteredDataCount = generateFilteredSearchResult(filteredData, data, dataCount, &isSet[0], &dotFrom, &dotTo, &bookFrom, &bookTo, &timeslot[0], staffFilter, sCount, userFilter, uCount, facFilter, fCount);
				system("pause");
				break;
			default:
				break;
			}
		} while (tolower(filterChoice[0]) != 'x');
		printf("Do you wish to return to menu ? (y=yes) ");
		getUserMenuChoice(retryChoice, 9, "Do you wish to return to menu ? (y=yes) ");
	} while (tolower(retryChoice[0]) != 'y');
}

// return 1 if filter for date of transaction is set successfully
int dispfilterDOT(int *isSet, Date *dotFrom, Date *dotTo)
{
	char dateSTR[30];
	int r; // keep track of scanf() result
	do
	{

		printf("\n<INFO> Enter 'X' to unset filter <INFO>\n\n");
		printf("Please make sure date entered is valid.\nDate of Transactions\n\tSTARTING FROM ? (dd/mm/yyyy) : ");
		s_input(dateSTR, 29);
		if (strcmp(trimwhitespace(dateSTR), "X") == 0 || dateSTR[0] == 'x')
		{
			isSet[0] = 0;
			return 0;
		}
		r = sscanf(dateSTR, "%d/%d/%d", &dotFrom->d, &dotFrom->m, &dotFrom->y);
	} while (r != 3 || !validateDate(dotFrom->d, dotFrom->m, dotFrom->y));
	do
	{
		printf("Enter date thats after Starting Date\n");
		printf("\tENDS AT ? (dd/mm/yyyy): ");
		s_input(dateSTR, 29);
		r = sscanf(dateSTR, "%d/%d/%d", &dotTo->d, &dotTo->m, &dotTo->y);
	} while (r != 3 || !validateDate(dotTo->d, dotTo->m, dotTo->y) ||
		compareDate(dotFrom->d, dotFrom->m, dotFrom->y, dotTo->d, dotTo->m, dotTo->y) == 1);
	return 1;
}

// return 1 if filter for booking date is successfully set
int dispfilterBookingDate(Date *bookingDateFrom, Date *bookingDateTo)
{
	char dateSTR[30];
	int r; // keep track of scanf() result
	do
	{
		printf("\n<INFO> Enter 'X' to unset filter <INFO>\n\n");
		printf("Please make sure date entered is valid.\nBooking Date\n\tSTARTING FROM ? (dd/mm/yyyy) : ");
		s_input(dateSTR, 29);
		if (strcmp(trimwhitespace(dateSTR), "X") == 0 || dateSTR[0] == 'x')
		{
			return 0;
		}
		r = sscanf(dateSTR, "%d/%d/%d", &bookingDateFrom->d, &bookingDateFrom->m, &bookingDateFrom->y);
	} while (r != 3 || !validateDate(bookingDateFrom->d, bookingDateFrom->m, bookingDateFrom->y));
	do
	{
		printf("Enter date thats after Starting Date\n");
		printf("\tENDS AT ? (dd/mm/yyyy): ");
		s_input(dateSTR, 29);
		r = sscanf(dateSTR, "%d/%d/%d", &bookingDateTo->d, &bookingDateTo->m, &bookingDateTo->y);
	} while (r != 3 || !validateDate(bookingDateTo->d, bookingDateTo->m, bookingDateTo->y) ||
		compareDate(bookingDateFrom->d, bookingDateFrom->m, bookingDateFrom->y, bookingDateTo->d, bookingDateTo->m, bookingDateTo->y) == 1);
	return 1;
}

// return 1 if timeslotBooked filter is updated successfully
int dispfilterTimeslotBooked(int *timeslot)
{
	char rawInput[10];
	char choice[10];
	int tsPicked, firstTime = 1; // firstTime to check if its the first iteration in loop, tsPicked to get IDX of timeslot picked by user
	do {
		do {
			if (firstTime) {
				printf("Timeslot:\n");
				for (int a = 0; a < 6; a++) {
					printf("\t[%d] %s ", a + 1, TIMESLOTS[a]);
					if (timeslot[a]) printf("<selected>\n"); else printf("<unselected>\n");
				}
				printf("\n<INFO> Enter 'X' to unset all filter <INFO>\n");
				printf("\n<INFO> Choose timeslot that is already selected will unselect it. <INFO>\n\n");
			}
			printf("Pick timeslot (1-6): ");
			getUserMenuChoice(rawInput, 9, "Pick timeslot (1-6): ");
			if (tolower(rawInput[0]) == 'x')
			{
				timeslot[0] = 0; timeslot[1] = 0; timeslot[2] = 0; timeslot[3] = 0; timeslot[4] = 0; timeslot[5] = 0;
				return 0;
			}
		} while (rawInput[0] < '1' || rawInput[0] > '6');
		tsPicked = strtol(rawInput, NULL, 10) - 1;
		timeslot[tsPicked] = !timeslot[tsPicked];
		printf("Timeslot:\n");
		for (int a = 0; a < 6; a++) {
			printf("\t[%d] %s ", a + 1, TIMESLOTS[a]);
			if (timeslot[a]) printf("<selected>\n"); else printf("<unselected>\n");
		}
		printf("Add more timeslot for filtering (y=yes) ? ");
		getUserMenuChoice(choice, 9, "Add more timeslot for filtering (y=yes) ? ");
		firstTime = 0;
	} while (tolower(choice[0]) == 'y');
	if (getTimeslotBooked(timeslot) == -1) // if none of the timeslots is selected
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

// return 1 if user filter is updated sucessfully
int dispFilterUserInvolved(userData **userIDsfilter, int *uCount)
{
	if (usrDataCount == 0)
	{
		printf("There was no users in the system.\n");
		system("pause");
		return 0;
	}
	char usrName[100];
	int elementRemoved = 0; // keep track if user input wants to remove from filter
	int usrFound = 0; // keep track of user given username is found

	do {
		elementRemoved = 0;
		usrFound = 0;

		printf("\nUsers in filter:\n");
		for (int a = 0; a < *uCount; a++)
		{
			printf("\t%d. %s\n", a + 1, userIDsfilter[a]->name);
		}
		printf("\n");

		printf("--> Enter 'X' to comfirm user filters\n");
		printf("--> Enter 'XXX' to unset user filters\n---> Enter the same username to unset them\n");
		printf("--> Enter username to add into filter\n>>> ");
		s_input(usrName, 99);
		// if user wants to cancel
		if (strcmp(trimwhitespace(usrName), "X") == 0 || strcmp(trimwhitespace(usrName), "x") == 0)
		{
			if (*uCount < 1)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
		if (strcmp(trimwhitespace(usrName), "XXX") == 0)
		{
			*uCount = 0;
			return 0;
		}

		for (int a = 0; a < usrDataCount; a++)
		{
			if (strcmp(usrData[a].name, usrName) == 0)
			{
				// checks if this user was in filter list or not
				for (int b = 0; b < *uCount; b++)
				{
					if (strcmp(usrData[a].id, userIDsfilter[b]->id) == 0)
					{
						// remove an element in array -> bad idea
						for (int c = b; c < *uCount - 1; c++)
						{
							userIDsfilter[c] = userIDsfilter[c + 1];
						}

						elementRemoved = 1;
						usrFound = 1;
						*uCount = *uCount - 1;
						break;
					}
				}
				if (elementRemoved == 0) { // if no element is being removed
					// printf("User found.\n");
					userIDsfilter[*uCount] = &usrData[a];
					*uCount = *uCount + 1;
					usrFound = 1;
				}
				break;
			}
		}
		if (!usrFound) {
			printf("User of name \"%s\" was not found.\n", usrName);
			system("pause");
		}
	} while (1);
}

// return 1 if filter is updated successfully
int dispFilterStaffInvovled(Staff **staffIDFilter, int *sCount)
{
	if (staffDataCount == 0)
	{
		printf("There are no staffs in the system...\n");
		system("pause");
		return 0;
	}
	char staffName[100];
	int elementRemoved = 0;
	int staffFound = 0;
	do {
		elementRemoved = 0;
		staffFound = 0;

		printf("Staffs in filter: \n");
		for (int a = 0; a < *sCount; a++)
		{
			printf("\t%d. %s\n", a + 1, staffIDFilter[a]->stfName);
		}

		printf("<!> Enter XXX to unset all staff filters <!>\n");
		printf("<!> Enter X to apply selected filters <!>\n");
		printf("Enter staff name to include in the filter: \n>>> ");
		s_input(staffName, 99);
		if (strcmp(trimwhitespace(staffName), "XXX") == 0)
		{
			*sCount = 0;
			return 0;
		}
		if (strcmp(trimwhitespace(staffName), "X") == 0)
		{
			if (*sCount > 0)
				return 1;
			else
				return 0;
		}
		for (int a = 0; a < staffDataCount; a++)
		{
			if (strcmp(staffData[a].stfName, staffName) == 0)
			{
				staffFound = 1;
				for (int b = 0; b < *sCount; b++) // check if it exist in filter
				{
					if (strcmp(staffData[a].stfID, staffIDFilter[b]->stfID) == 0)
					{
						for (int c = b; c < *sCount - 1; c++)
						{
							staffIDFilter[c] = staffIDFilter[c + 1];
						}
						elementRemoved = 1;
						*sCount = *sCount - 1;
						break;
					}
				}
				if (!elementRemoved)
				{
					staffIDFilter[*sCount] = &staffData[a];
					*sCount = *sCount + 1;
				}
				break;
			}
		}
	} while (1);
}

// return 1 if filter is updated successfully
int dispFilterFacInvolved(Facility **facFilter, int *fCount)
{
	if (facilityDataCount == 0)
	{
		printf("There are no facility in the system...\n");
		system("pause");
		return 0;
	}

	printf("Facility Filter:\n");
	for (int a = 0; a < *fCount; a++)
	{
		printf("%d. %s - %s\n", a + 1, facFilter[a]->id, facFilter[a]->name);
	}

	char userSearchFacility[200];
	do {
		printf("<!> Enter 'XXX' to unset filter <!>\n");
		printf("Enter Facility Name to include in filter: ");
		s_input(userSearchFacility, 199);

		if (strcmp(userSearchFacility, "XXX") == 0 || strcmp(userSearchFacility, "xxx") == 0)
		{
			*fCount = 0;
			return 0;
		}

		int facCount = getFacilityCount(userSearchFacility);
		if (facCount < 1) // if less than 1 match (no match)
		{
			printf("Facility of name \"%s\" is not found.\n", userSearchFacility);
			system("pause");
			continue;
		}
		for (int a = 0; a < facilityDataCount; a++)
		{
			if (strcmp(userSearchFacility, facData[a].name) == 0)
			{

				if (facCount > 1)
				{
					printf("There are more than 1 %s.\n\n", facData[a].name);
					Facility *facList[100];
					int tmp = 0;
					for (int b = 0; b < facilityDataCount; b++)
					{
						if (strcmp(facData[b].name, userSearchFacility) == 0)
						{
							printf("\t%s - %s\n", facData[b].id, facData[b].name);
							facList[tmp++] = &facData[b];
						}
					}
					do {
						printf("\nEnter 'a' to include all in filter, Enter facility ID to only choose one of them\n");
						printf("Do you wish to include all in filter or only one of them ? ");
						char specificFacilityID[30];
						s_input(specificFacilityID, 29);
						strcpy(specificFacilityID, trimwhitespace(specificFacilityID)); // get trimmed input
						if (strcmp(specificFacilityID, "a") == 0)
						{
							for (int b = 0; b < tmp; b++)
							{
								facFilter[(*fCount)++] = facList[b];
							}
							return 1;
						}
						for (int b = 0; b < tmp; b++)
						{
							if (strcmp(specificFacilityID, facList[b]->id) == 0)
							{
								facFilter[(*fCount)++] = facList[b];
								return 1;
							}
						}
						// if user entered something thats not from the list
						printf("Invalid Facility ID\n");
						system("pause");
					} while (1);
				}
				else if (facCount == 1) // if theres only 1 match
				{
					facFilter[(*fCount)++] = &facData[a];
					return 1;
				}
			}
		}
	} while (1);
}

// print booking details based on bookingID
void printBookingDetails(char *bookingID, BookingData *data, int dataSize)
{
	BookingData *bData = NULL;
	for (int a = 0; a < dataSize; a++)
	{
		if (strcmp(data[a].bookingID, bookingID) == 0)
		{
			bData = &data[a];
			break;
		}
	}
	if (bData == NULL)
	{
		printf("Booking of ID \"%s\" was not found.\n", bookingID);
		system("pause");
		return;
	}
	Staff *stf = getStaffDataByID(bData->staffID);
	if (stf == NULL)
	{
		printf("Staff of ID \"%s\" was not found.\n", bData->staffID);
		system("pause");
		return;
	}
	userData *usr = getUserDataByID(bData->usrID);
	if (usr == NULL)
	{
		/*printf("User of ID \"%s\" was not found.\n", bData->usrID);
		system("pause");*/
		userData nullUser = { "null", "null",-1,-1,-1,-1,-1,-1,"null" ,"null" ,"null" };
		usr = &nullUser;
	}
	Facility *fac = getFacilityByID(bData->facilityID);
	if (fac == NULL)
	{
		printf("Facility of ID \"%s\" was not found.\n", bData->facilityID);
		system("pause");
		return;
	}

	// Split facility remarks into 3 lines
	char remarkLine[3][36] = { "","","" };
	for (int a = 0; a < 15; a++)
	{
		if (a == strlen(fac->remarks))
		{
			break;
		}
		remarkLine[0][a] = fac->remarks[a];
	}
	for (int a = 0; a < 34; a++)
	{
		if (a + 15 == strlen(fac->remarks))
		{
			break;
		}
		remarkLine[1][a] = fac->remarks[a + 15];
	}
	for (int a = 0; a < 34; a++)
	{
		if (a + 48 == strlen(fac->remarks))
		{
			break;
		}
		remarkLine[2][a] = fac->remarks[a + 48];
	}
	if(strlen(fac->remarks) == 0)
	{
		remarkLine[0][0] = '\0';
		remarkLine[1][0] = '\0';
		remarkLine[2][0] = '\0';
	}

	printf("%40s                Booking\n", "");
	printf("%40s---------------------------------------\n", "");
	printf("%40s| Booking ID       : %s          |\n", "", bData->bookingID);
	printf("%40s| Transaction Date : %02d/%02d/%04d %02d:%02d |\n", "", bData->currentDate.d, bData->currentDate.m, bData->currentDate.y, bData->currentTime.h, bData->currentTime.m);
	printf("%40s| Booking Date     : %02d/%02d/%04d       |\n", "", bData->bookingDate.d, bData->bookingDate.m, bData->bookingDate.y);
	printf("%40s| Timeslot Booked  : %s       |\n", "", TIMESLOTS[getTimeslotBooked(&bData->timeSlotsBooked[0])]);
	printf("%40s---------------------------------------\n", "");
	printf("                   User                                Faciltity                                Staff                 \n");
	printf("  -------------------------------------- -------------------------------------- --------------------------------------\n");
	printf("  | ID              : %-16.16s | | ID               : %-15.15s | | ID              : %-16.16s |\n", usr->id, fac->id, stf->stfID);
	printf("  | Name            : %-16.16s | | Name             : %-15.15s | | Name            : %-16.16s |\n", usr->name, fac->name, stf->stfName);
	printf("  | Date registered : %02d/%02d/%04d %02d:%02d | | Maintenance Date : %02d/%02d           | | Position        : %-16.16s |\n", usr->dateEnter.d, usr->dateEnter.m, usr->dateEnter.y, usr->timeEnter.h, usr->timeEnter.m, fac->maintenanceDate.d, fac->maintenanceDate.m, stf->stfPosi);
	printf("  | Gender          : %-16.16s | | Remarks          : %-15.15s | | Date Registered : %02d/%02d/%04d       |\n", usr->gender, remarkLine[0], stf->dateRegis.d, stf->dateRegis.m, stf->dateRegis.y);
	printf("  | Contact         : %-16.16s | | %-34.34s | |                                    |\n", usr->contact, remarkLine[1]);
	printf("  |                                    | | %-34.34s | |                                    |\n", remarkLine[2]);
	printf("  -------------------------------------- -------------------------------------- --------------------------------------\n");
	system("pause");
}

// ============================================================================================
// Utilities & Sub Functions go below this point
// ============================================================================================
// make sure to initialise first byte of oldBookID to '\0'

// Return amount of data entries found
// Do fclose() before calling this function
int readBookingDataIntoStructArray(BookingData *data2, int size)
{
	FILE *f = fopen(bookingFilePath, "r");
	if (!chkFileExist(f))
	{
		return 0;
	}
	int count = 0;
	while (fscanf(f, "%[^,],%d/%d/%d,%d:%d:%d,%d/%d/%d,%d,%d,%d,%d,%d,%d,%[^,],%[^,],%[^\n]\n",
		data2[count].bookingID,
		&data2[count].currentDate.d,
		&data2[count].currentDate.m,
		&data2[count].currentDate.y,
		&data2[count].currentTime.h,
		&data2[count].currentTime.m,
		&data2[count].currentTime.s,
		&data2[count].bookingDate.d,
		&data2[count].bookingDate.m,
		&data2[count].bookingDate.y,
		&data2[count].timeSlotsBooked[0],
		&data2[count].timeSlotsBooked[1],
		&data2[count].timeSlotsBooked[2],
		&data2[count].timeSlotsBooked[3],
		&data2[count].timeSlotsBooked[4],
		&data2[count].timeSlotsBooked[5],
		data2[count].usrID,
		data2[count].staffID,
		data2[count].facilityID
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

// NOTE: this function is only used to check specific facility ID
// Run through struct array to check what time slots is available
// Set timeslot to 0 if the timeslot is not free
// timeslot array need to be size 6 (6 timeslots stated)
// Return True if there are timeslots available
// exluding bookingID for modify() use
int checkForTimeslotsAvailablity(int *timeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID, char bookingIDToExclude[])
{
	// make sure timeslot is properly initialised
	timeslot[0] = 1; timeslot[1] = 1; timeslot[2] = 1; timeslot[3] = 1; timeslot[4] = 1; timeslot[5] = 1;
	for (int a = 0; a < dataSize; a++)
	{
		if (strcmp(data[a].bookingID, bookingIDToExclude) == 0)
		{
			continue;
		}
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

// same as checkForTimeslotsAvailablity() but for all facility with same name instead of ID
// inverting the searching process because there might be multiple facility of same name
int checkOverallTimeslotsAvailablity(int *timeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityName)
{
	// make sure timeslot is properly initialised
	timeslot[0] = 0; timeslot[1] = 0; timeslot[2] = 0; timeslot[3] = 0; timeslot[4] = 0; timeslot[5] = 0;
	Facility *facList[100];
	int tmp = 0;
	for (int a = 0; a < facilityDataCount; a++)
	{
		if (strcmp(facilityName, facData[a].name) == 0)
		{
			facList[tmp++] = &facData[a];
		}
	}
	int tmpTS[6];
	for (int a = 0; a < tmp; a++) {
		checkForTimeslotsAvailablity(&tmpTS[0], data, dataSize, bookingDate, facList[a]->id, "");
		for (int b = 0; b < 6; b++)
		{
			if (tmpTS[b])
			{
				timeslot[b] = 1;
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
// Return -1 if none of the timeslot is free
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

// get how many 1s are there in timeslot array
int getTimeslotArrayCount(int*timeslot)
{
	int count = 0;
	for (int a = 0; a < 6; a++)
	{
		if(timeslot[a])
			count++;
	}
	return count;
}
// ============================================================================================
// ============================================================================================

// ============================================================================================
// Functions for BIP (Book-In-Progress)
// ============================================================================================

// Return 1 if facility change successfully
int bipChangeFacility(char *userPickedfacilityID)
{
	/*char rawInput[100];
	char *trimmedInput;
	char *endPtr;*/
	int userChoice;
	Facility *facList[100]; // store temp list for displaying facilities
	// Ask user to select facility
	if (facilityDataCount == 0)
	{
		printf("There are no facilities registered in the system.\n");
		system("pause");
		return 0;
	}
	do {
		printf("Select one of the following facilities: \n");
		/*
		Insert code to get all facilities
		Need to count how many facilities are there?
		*/
		int idxNumbering = 1;
		int continueLoop = 0;

		for (int a = 0; a < facilityDataCount; a++)
		{
			for (int b = 0; b < a; b++)
			{
				if (strcmp(facData[a].name, facData[b].name) == 0)
				{
					continueLoop = 1;
				}
			}
			if (continueLoop)
			{
				continueLoop = 0;
				continue;
			}
			facList[idxNumbering - 1] = &facData[a];
			printf("\t%d. %s\n", idxNumbering++, facData[a].name);
		}
		printf("\nSelect Facility you wish to book(%d-%d): ", 1, idxNumbering - 1);
		if (i_input(&userChoice)) // if user entered integer
		{
			if (userChoice > 0 && userChoice <= idxNumbering - 1) // if user input is within range
				break;
		}
		printf("\n<!> ERR: Invalid Choice. <!>\n");
		system("pause");
	} while (1);
	strcpy(userPickedfacilityID, facList[userChoice - 1]->id);
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
// userPickedtimeslot is integer, not array
// this function doesnt directly modify timeslot array
// NOTE: userPickedTimeslot is being minus 1 at the end
// userAlreadyPickedTimeslot flag to know if user picked the timeslot before
int bipChangeTimeslot(int userAlreadyPickedTimeslot, int *userPickedtimeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID, char bookingIDToExclude[])
{
	int timeslotAvailable[6] = { 1,1,1,1,1,1 }; // to check for timeslot availablity
	if (!checkOverallTimeslotsAvailablity(timeslotAvailable, data, dataSize, bookingDate, getFacilityByID(facilityID)->name) && !userAlreadyPickedTimeslot) {
		printf("Sorry, but there are no free timeslots on that day for that facility, please try other facility / date\n");
		return 0;
	}
	if(userAlreadyPickedTimeslot)
		timeslotAvailable[*userPickedtimeslot] = 1;
	printf("Timeslots: \n");
	for (int a = 0; a < 6; a++)
	{
		printf("\t%d. %s ", a + 1, TIMESLOTS[a]);
		if (timeslotAvailable[a]) printf(" <Available>\n"); else printf(" <Not Available>\n");
	}

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
			getUserMenuChoice(userPickedtimeslotSTR, 9, "Please, pick a timeslot(1-6): ");

		} while (userPickedtimeslotSTR[0] < '1' || userPickedtimeslotSTR[0] > '6'); // this checks whether user enter valid input (if you are wondering why not i_input()
		err = 1;
		*userPickedtimeslot = strtol(userPickedtimeslotSTR, NULL, 10) - 1;
	} while (!timeslotAvailable[*userPickedtimeslot]); // while that timeslot is booked
	err = 0;
	// because there can be different free time slots for different facilty
	// refer to checkOverallTimeslotsAvailablity() call in this function
	findNextFreeFacID(getFacilityByID(facilityID)->name, facilityID, bookingDate, *userPickedtimeslot, bookingIDToExclude);
	return 1;
}

void readDataFromOtherModules()
{
	facilityDataCount = 0;
	staffDataCount = 0;
	usrDataCount = 0;
	FILE *f = fopen(UserInfoFilePath, "rb");
	if (chkFileExist(f))
	{
		while (fread(&usrData[usrDataCount], sizeof(userData), 1, f) != 0)
		{
			usrDataCount++;
		}
		fclose(f);
	}
	f = fopen(staffFilePath, "rb");
	if (chkFileExist(f))
	{
		while (fread(&staffData[staffDataCount], sizeof(Staff), 1, f) != 0)
		{
			staffDataCount++;
		}
		fclose(f);
	}
	f = fopen(facilityFilePath, "rb");
	if (chkFileExist(f))
	{
		while (fread(&facData[facilityDataCount], sizeof(Facility), 1, f) != 0)
		{
			facilityDataCount++;
		}
		fclose(f);
	}
}

// ============================================================================================
// ============================================================================================

// ============================================================================================
// Functions for obtaining data from other modules
// ============================================================================================

// Return pointer to staff data, null if not found or no data
Staff* getStaffDataByID(char *id)
{
	if (staffDataCount == 0)
	{
		return NULL;
	}
	for (int a = 0; a < staffDataCount; a++)
	{
		if (strcmp(staffData[a].stfID, id) == 0)
		{
			return &staffData[a];
		}
	}
	return NULL;
}

// return pointer to user data, null if not found or no data
userData* getUserDataByID(char *id)
{
	if (usrDataCount == 0)
	{
		return NULL;
	}
	for (int a = 0; a < usrDataCount; a++)
	{
		if (strcmp(usrData[a].id, id) == 0)
		{
			return &usrData[a];
		}
	}
	return NULL;
}

// return pointer to faciltiy data, null if not found or no data
Facility* getFacilityByID(char *id)
{
	if (facilityDataCount == 0)
	{
		return NULL;
	}
	for (int a = 0; a < facilityDataCount; a++)
	{
		if (strcmp(facData[a].id, id) == 0)
		{
			return &facData[a];
		}
	}
	return NULL;

}
// ============================================================================================
// ============================================================================================

// ============================================================================================
// Login functions
// ============================================================================================

// login User and store ID onto staffID
// if login was successful, it will return true
int _usrLogin(char *usrID, int size)
{
	char pw[100];
	userData *usr;
	if (usrDataCount == 0)
	{
		printf("There are currently no users in the system.\n");
		system("pause");
		return 0;
	}

	do
	{
		printf("===============\n");
		printf("| User Login |\n");
		printf("===============\n");
		printf("Enter 'XXX' to return to previous screen\n");
		printf("User ID -> ");
		s_input(usrID, size);
		if (strcmp(usrID, "XXX") == 0 || strcmp(usrID, "xxx") == 0)
		{
			return 0;
		}
		usr = getUserDataByID(usrID);
		if (usr == NULL)
		{
			printf("Such usrID do not exist.\n");
			system("pause");
			continue;
		}
		printf("Password -> ");
		collectCensoredInput(pw, 99);
		if (strcmp(pw, usr->password) == 0)
		{
			printf("User Login Successful.\n");
			return 1;
		}
		else {
			printf("Invalid password.\n");
		}
	} while (1);
}

// Reauthetication of staff
// Return 1 is everything works
// Return 0 if user wish to return to previous screen as always
int _staffPWReauth()
{
	if (strlen(sessionStaffID) < 0)
	{
		printf("_staffPWReauth() call before sessionStaffID definition.\n");
		system("pause");
		return 0;
	}
	printf("<!> ENTER 'XXX' to return to previous screen <!>\n");
	printf("Please re-enter staff password: ");
	char pw[300];
	collectCensoredInput(pw, 300);
	if (strcmp(pw, "XXX") == 0 || strcmp(pw, "xxx") == 0)
	{
		return 0;
	}
	if (strcmp(getStaffDataByID(sessionStaffID)->stfPassW, pw) != 0)
	{
		printf("Wrong password !\n");
		system("pause");
		return 0; // return immediately because its bad to allow user to continue inputs
	}
	return 1;
}

// ============================================================================================
// ============================================================================================

// ============================================================================================
// functions to deal with facility module
// ============================================================================================

// Find next FacilityID that is free to be booked
// if found, return 1, else 0
// Input: facility name, booking date, booking slot IDX, bookingIDToExclude
// NOTE: BookingIDToexlude is used in modify call
int findNextFreeFacID(char facName[], char *facID, Date *bookingDate, int bookingSlotIDX, char bookingIDToExclude[])
{
	if (facilityDataCount == 0)
	{
		printf("There are no facility in system.\n");
		system("pause");
		return 0;
	}
	BookingData data2[100];
	int dataCount = readBookingDataIntoStructArray(&data2[0], 100);
	for (int a = 0; a < facilityDataCount; a++)
	{
		int tmpTS[6]; // timeslot array
		if (strcmp(facData[a].name, facName) == 0)
		{
			checkForTimeslotsAvailablity(&tmpTS[0], &data2[0], dataCount, bookingDate, facData[a].id, bookingIDToExclude);
			if (tmpTS[bookingSlotIDX])
			{
				strcpy(facID, facData[a].id);
				return 1;
			}
		}
	}
	return 0;
}

// Get amount of facility of specific name
int getFacilityCount(char facilityName[])
{
	int c = 0;
	for (int a = 0; a < facilityDataCount; a++)
	{
		if (strcmp(facilityName, facData[a].name) == 0)
		{
			c++;
		}
	}
	return c;
}

// ============================================================================================
// ============================================================================================
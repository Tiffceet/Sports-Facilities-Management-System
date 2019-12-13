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
	FILE *f = fopen(UserInfoFilePath, "wb");
	userData usr = { "Ali", "U001", 2019,12,10, 9,46,0, "L", "010389552", "123456" };
	fwrite(&usr, sizeof(userData), 1, f);
	userData usr2 = { "Ahmad", "U002", 2019,12,10,9,46,0, "L", "010389552", "123456" };
	fwrite(&usr2, sizeof(userData), 1, f);
	userData usr3 = { "Felix", "U003", 2019,12,10, 9,46,0, "L", "010389552", "123456" };
	fwrite(&usr3, sizeof(userData), 1, f);
	userData usr4 = { "Gohan", "U004", 2019,12,10, 9,46,0, "L", "010389552", "123456" };
	fwrite(&usr4, sizeof(userData), 1, f);
	fclose(f);
	readDataFromOtherModules();
	/*BookingData data[100];
	readBookingDataIntoStructArray(&data[0], 99);*/
	// initialise error code for input validation use
	err = 0;
	
	//// prompt staff login
	//if (!_staffLogin(sessionStaffID, 99))
	//{
	//	return;
	//}
	strcpy(sessionStaffID , "S001");
	// while menu() doesnt return 0 = continue running
	while (bookingMenu())
	{
		continue;
	}
}

int bookingMenu()
{
	char choiceText[][100] = { "Book", "Search Records", "Modify records", "Display all bookings", "Log Out (Return to console)" };
	int choice = globalMainMenu("Booking Module", 5, choiceText);
	switch (choice)
	{
	case 1:
		bookingBook(); // add do while loop to ask user if want to book mores
		break;
	case 2:
		bookingSearchRecords();
		break;
	case 3:
		break;
	case 4:
		bookingDisplayAll();
		break;
	case 5:
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
	printf(" | 5. Every booking needs to be handled by 1 staff                                                                 |\n");
	printf(" =====================================================================================================================\n");
	printf(" =====================================================================================================================\n\n");
}

//void bookingBook()
//{
//	// Variables to be used
//	BookingData data[100];
//	char userPickedfacilityID[100];
//	Date userPickedDate; // Booking Date
//	int userPickedtimeslot;
//	int isSet[] = { 0, 0, 0 }; // to keep track of what details have been given and what have not	
//
//	// initialise slotsBooked
//	for (int a = 0; a < 100; a++)
//	{
//		for (int b = 0; b < 6; b++) {
//			data[a].timeSlotsBooked[b] = 0;
//		}
//	}
//	// find latestBooking ID + count of items in file
//	char latestBookingID[10];
//	latestBookingID[0] = '\0';
//	int count = readBookingDataIntoStructArray(&data[0], 100); // read file into struct array + get entries count
//	if (count != 0) // if file exist
//	{
//		strcpy(latestBookingID, data[count - 1].bookingID);
//	}
//	printf("%s\n", latestBookingID);
//	incrementBookingID(latestBookingID); // increment bookingID
//	printBookingInfo();
//
//	// Sub Menu
//	char choice[10];
//	char bookingComfirmChoice[10];
//	char choiceToContinueNextBooking[10] = "\0";
//	do {
//		if (tolower(choiceToContinueNextBooking[0]) == 'y')
//		{
//			isSet[2] = 0;
//			incrementBookingID(latestBookingID); // increment bookingID
//		}
//		do {
//			char facilityStatus[100], bookingDateStatus[100], timeslotStatus[100];
//			if (isSet[0]) strcpy(facilityStatus, getFacilityByID(userPickedfacilityID)->description); else strcpy(facilityStatus, "<!> Not Set <!>");
//			if (isSet[1]) sprintf(bookingDateStatus, "%02d/%02d/%04d", userPickedDate.d, userPickedDate.m, userPickedDate.y); else strcpy(bookingDateStatus, "<!> Not Set <!>");
//			if (isSet[2]) strcpy(timeslotStatus, TIMESLOTS[userPickedtimeslot]); else strcpy(timeslotStatus, "<!> Not Set <!>");
//			printf(" <----------------------------------------------------->\n");
//			printf(" ->                  Booking Details                  <-\n");
//			printf(" <----------------------------------------------------->\n");
//			printf(" | Facility     : %-36.36s |\n", facilityStatus);
//			printf(" | Booking Date : %-36.36s |\n", bookingDateStatus);
//			printf(" | Timeslot     : %-36.36s |\n", timeslotStatus);
//			printf(" <----------------------------------------------------->\n\n");
//			printf(" Select: \n");
//			printf(" \t[1] Set Facility\n");
//			printf(" \t[2] Set Booking Date\n");
//			printf(" \t[3] Set Timeslot\n");
//			printf(" \t[4] Comfirm Booking\n");
//			printf(" \t[5] Cancel Booking\n\n");
//			printf(" Choice ? ");
//			getUserMenuChoice(choice, 9, " Choice ? ");
//			switch (choice[0])
//			{
//			case '1':
//				bipChangeFacility(userPickedfacilityID);
//				isSet[0] = 1;
//				isSet[2] = 0;
//				break;
//			case '2':\
//				bipChangeBookingDate(&userPickedDate);
//				isSet[1] = 1;
//				isSet[2] = 0;
//				break;
//			case '3':
//				if (!isSet[0])
//				{
//					printf("\n<!> ERR: No Facility have been chosen. <!>\n");
//					system("pause");
//					break;
//				}
//				if (!isSet[1])
//				{
//					printf("\n<!> ERR: Booking Date have not been determined. <!>\n");
//					system("pause");
//					break;
//				}
//				isSet[2] = bipChangeTimeslot(&userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID);
//				break;
//			case '4':
//				if (!isSet[0])
//				{
//					printf("\n<!> ERR: No Facility have been chosen. <!>\n");
//					system("pause");
//					break;
//				}
//				if (!isSet[1])
//				{
//					printf("\n<!> ERR: Booking Date have not been determined. <!>\n");
//					system("pause");
//					break;
//				}
//				if (!isSet[2])
//				{
//					printf("\n<!> ERR: Timeslot have not been selected. <!>\n");
//					system("pause");
//					break;
//				}
//				// NEED TO FKING ADD COMFIRMATIONA AND WHOLE LOT OF SHIT
//				printf("<INFO> Every booking needs to be handled by 1 staff. <INFO>\n<INFO> Every booking needs 1 registered user <INFO>\n");
//				printf("Press any key to proceed with staff & user login...");
//				system("pause >nul");
//				printf("\n");
//				int loginStat = _staffLogin(data[count].staffID, 5);
//				if (loginStat == 0) // if user wants to return
//				{
//					break;
//				}
//
//				loginStat = _usrLogin(data[count].usrID, 14);
//				if (loginStat == 0)
//				{
//					break;
//				}
//
//				printf("Please read the booking details again for confirmation. (Y=Comfirm) ? ");
//				getUserMenuChoice(bookingComfirmChoice, 9, "Please read the booking details again for confirmation. (Y=Comfirm) ? ");
//				if (tolower(bookingComfirmChoice[0]) != 'y')
//				{
//					break;
//				}
//				
//
//				// Gather all info
//				strcpy(data[count].bookingID, latestBookingID);
//				getSystemDate(&data[count].currentDate);
//				getSystemTime(&data[count].currentTime);
//				data[count].bookingDate.d = userPickedDate.d;
//				data[count].bookingDate.m = userPickedDate.m;
//				data[count].bookingDate.y = userPickedDate.y;
//				data[count].timeSlotsBooked[userPickedtimeslot] = 1;
//				// strcpy(data[count].usrID, "U0001");
//				// strcpy(data[count].staffID, "S0001");
//				strcpy(data[count].facilityID, userPickedfacilityID);
//				// Important line here
//				writeBookingDataIntoFile(&data[0], ++count);
//				
//				printf("Booking have been handled by %s.\nThank you, %s for booking %s at %02d/%02d/%02d %s.\n",
//					// data[count - 1].staffID,
//					getStaffDataByID(data[count - 1].staffID)->stfName,
//					// data[count - 1].usrID,
//					getUserDataByID(data[count - 1].usrID)->name,
//					// data[count - 1].facilityID,
//					getFacilityByID(data[count - 1].facilityID)->description,
//					data[count - 1].bookingDate.d,
//					data[count - 1].bookingDate.m,
//					data[count - 1].bookingDate.y,
//					TIMESLOTS[getTimeslotBooked(data[count - 1].timeSlotsBooked)]
//				);
//				system("pause");
//				break;
//			case '5':
//				printf("\n<INFO> Booking is canceled <INFO>\n");
//				system("pause");
//				return;
//			default:
//				printf("\n<!> ERR: Please select number between 1 - 5 <!>\n\n");
//				system("pause");
//			}
//		} while (choice[0] != '4' || tolower(bookingComfirmChoice[0]) != 'y'); // if user didnt pick 'Comfirm Booking' OR 'y' during final booking comfirmation
//		printf("Would you like to continue a new booking ? (y=yes) ");
//		getUserMenuChoice(choiceToContinueNextBooking, 9, "Would you like to continue a new booking ? (y=yes) ");
//	} while (tolower(choiceToContinueNextBooking[0]) == 'y');
//	// End of Sub Menu	
//}

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

	char loginUserID[100];

	printf("Only registered user are allowed to make booking.\n");
	if (!_usrLogin(loginUserID, 99))
	{
		return;
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
	char statusText[3][100];

	char choice[10];
	char choiceToContinueNextBooking[10] = "\0";
	do {
		if (tolower(choiceToContinueNextBooking[0]) == 'y')
		{
			incrementBookingID(latestBookingID); // increment bookingID
		}
		int firstIteration = 1;
		do{
			// Main Logic
			if(firstIteration)
			{
				bipChangeFacility(userPickedfacilityID);
				bipChangeBookingDate(&userPickedDate);
				bipChangeTimeslot(&userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID);
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
					int tmpR = checkForTimeslotsAvailablity(&tmpTS[0], &data[0], 100, &userPickedDate, userPickedfacilityID);
					if (!tmpR) // if no timeslot anymore
					{
						printf("There are no available timeslots on booking date.\n Please re-select date + timeslot.\n");
						bipChangeBookingDate(&userPickedDate);
						bipChangeTimeslot(&userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID);
					}
					else if (!tmpTS[userPickedtimeslot]) // if the timeslot picked is full
					{
						printf("The timeslot you picked is unavailable.\n Please re-select date + timeslot.\n");
						bipChangeBookingDate(&userPickedDate);
						bipChangeTimeslot(&userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID);
					}
					printf("Is the booking date %02d/%02d/%04d correct ? (y=yes) ", userPickedDate.d, userPickedDate.m, userPickedDate.y);
					getUserMenuChoice(choice, 9, "Is the booking date %02d/%02d/%04d correct ? (y=yes) ");
					if (tolower(choice[0]) != 'y')
					{
						bipChangeBookingDate(&userPickedDate);
						bipChangeTimeslot(&userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID);
					}
					break;
				case '2':
					bipChangeBookingDate(&userPickedDate);
					bipChangeTimeslot(&userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID);
					break;
				case '3':
					bipChangeTimeslot(&userPickedtimeslot, &data[0], count, &userPickedDate, userPickedfacilityID);
					break;
				}
				
			}

			// printing of display
			strcpy(statusText[0], getFacilityByID(userPickedfacilityID)->description);
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
				getFacilityByID(data[count - 1].facilityID)->description,
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

void bookingSearchRecords()
{
	// Variables
	Date dotFrom = { 0,0,0 }, dotTo = { 0,0,0 }, bookFrom = { 0,0,0 }, bookTo = { 0,0,0 };
	int timeslot[6] = { 0,0,0,0,0,0 }; // for TimeslotBooked
	BookingData data[100];
	BookingData *filteredData[100];
	int filteredDataCount;
	int count = readBookingDataIntoStructArray(&data[0], 100);

	// inputs variable
	char choice[10];
	int userPickedDataToViewIDX = -1;

	// Variables for sub menu
	char statusText[6][100];
	int isSet[6] = { 0,0,0,0,0,0 };

	do {
		userPickedDataToViewIDX = -1;
		if (isSet[0]) sprintf(statusText[0], "%02d/%02d/%04d - %02d/%02d/%04d", dotFrom.d, dotFrom.m, dotFrom.y, dotTo.d, dotTo.m, dotTo.y); else strcpy(statusText[0], "Not Set");
		if (isSet[1]) sprintf(statusText[1], "%02d/%02d/%04d - %02d/%02d/%04d", bookFrom.d, bookFrom.m, bookFrom.y, bookTo.d, bookTo.m, bookTo.y); else strcpy(statusText[1], "Not Set");
		if (isSet[2])
		{
			int firstTime = 1;
			for (int a = 0; a < 6; a++)
			{
				if (timeslot[a])
				{
					if (firstTime) {
						sprintf(statusText[2], "%s", TIMESLOTS[a]);
						firstTime = 0;
					}
					else
					{
						sprintf(statusText[2], "%s, %s", statusText[2], TIMESLOTS[a]);
					}
				}
			}
		}
		else strcpy(statusText[2], "Not Set");
		if (isSet[3]) {}
		else strcpy(statusText[3], "Not Set");
		if (isSet[4]) {}
		else strcpy(statusText[4], "Not Set");
		if (isSet[5]) {}
		else strcpy(statusText[5], "Not Set");
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
			break;
		case '5':
			break;
		case '6':
			break;
		case '7':
			return;
		case 'x':
		case 'X':
			filteredDataCount = generateFilteredSearchResult(filteredData, &data[0], count, &isSet[0], &dotFrom, &dotTo, &bookFrom, &bookTo, &timeslot[0]);
			if(filteredDataCount != 0){
				do{
					printf("\nEnter '0' to return to search criteria selections.\nSelect (%d-%d) to view more details. ", 1, filteredDataCount);
				} while (!i_input(&userPickedDataToViewIDX) || (userPickedDataToViewIDX < 0 || userPickedDataToViewIDX > filteredDataCount));
				if (userPickedDataToViewIDX == 0)
				{
					break;
				}
				else
				{
					printBookingDetails(filteredData[userPickedDataToViewIDX-1]->bookingID, &data[0], 100);
				}
			}
			break;
		}
	} while (tolower(choice[0]) != '7'); // while(1) works too because case'7': return;
}

// generate & print filtered result and ask user to pick specific data to view its details
// return numbers of filtered result found
int generateFilteredSearchResult(BookingData **filteredData, BookingData *data, int dataCount, int *isSet, Date *dotFrom, Date *dotTo, Date *bookFrom, Date *bookTo, int *timeslot)
{
	int count = 0; // to keep track of how many records were printed
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "|                                               Booking Transactions                                                 |");
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "| No. | DateofTransaction BookingID BookingDate TimeslotBooked FacilityBooked           Booked by    Registered by   |");
	printf("%s\n", "|--------------------------------------------------------------------------------------------------------------------|");
	for (int a = 0; a < dataCount; a++)
	{
		if (isSet[0])
		{
			if (compareDate(data[a].currentDate.d, data[a].currentDate.m, data[a].currentDate.y, dotFrom->d, dotFrom->m, dotFrom->y) == -1
				|| compareDate(data[a].currentDate.d, data[a].currentDate.m, data[a].currentDate.y, dotTo->d, dotTo->m, dotTo->y) == 1)
			{
				continue;
			}
		}
		if (isSet[1])
		{
			if (compareDate(data[a].bookingDate.d, data[a].bookingDate.m, data[a].bookingDate.y, bookFrom->d, bookFrom->m, bookFrom->y) == -1
				|| compareDate(data[a].bookingDate.d, data[a].bookingDate.m, data[a].bookingDate.y, bookTo->d, bookTo->m, bookTo->y) == 1)
			{
				continue;
			}
		}
		if (isSet[2])
		{
			if (!timeslot[getTimeslotBooked(data[a].timeSlotsBooked)])
			{
				continue;
			}
		}
		printf("| %-3d | %02d/%02d/%-04d %02d:%02d  %-8.7s  %02d/%02d/%-05d %-14.14s %-24.24s %-12.12s %-15.15s |\n",
			count + 1,
			data[a].currentDate.d, data[a].currentDate.m, data[a].currentDate.y, data[a].currentTime.h, data[a].currentTime.m,
			data[a].bookingID,
			data[a].bookingDate.d, data[a].bookingDate.m, data[a].bookingDate.y,
			TIMESLOTS[getTimeslotBooked(data[a].timeSlotsBooked)],
			// data[a].facilityID,
			getFacilityByID(data[a].facilityID)->description,
			//data[a].usrID,
			getUserDataByID(data[a].usrID)->name,
			//data[a].staffID);
			getStaffDataByID(data[a].staffID)->stfName);
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

}

void bookingDisplayAll()
{
	BookingData data[100];
	int count = readBookingDataIntoStructArray(&data[0], 100);
	if (count == 0)
	{
		printf("\n<!> ERR: No records found. <!>\n");
		system("pause");
		return;
	}
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "|                                               Booking Transactions                                                 |");
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "| DateofTransaction BookingID BookingDate TimeslotBooked FacilityBooked                 Booked by    Registered by   |");
	printf("%s\n", "|--------------------------------------------------------------------------------------------------------------------|");
	for (int a = 0; a < count; a++)
	{
		printf("| %02d/%02d/%-04d %02d:%02d  %-8.7s  %02d/%02d/%-05d %-14.14s %-30.30s %-12.12s %-15.15s |\n",
			data[a].currentDate.d, data[a].currentDate.m, data[a].currentDate.y, data[a].currentTime.h, data[a].currentTime.m,
			data[a].bookingID,
			data[a].bookingDate.d, data[a].bookingDate.m, data[a].bookingDate.y,
			TIMESLOTS[getTimeslotBooked(data[a].timeSlotsBooked)],
			// data[a].facilityID,
			getFacilityByID(data[a].facilityID)->description,
			//data[a].usrID,
			getUserDataByID(data[a].usrID)->name,
			//data[a].staffID);
			getStaffDataByID(data[a].staffID)->stfName);
	}
	printf("%s\n", "======================================================================================================================");
	printf("%s\n", "======================================================================================================================");
	printf("\n%d record(s) found. \n", count);

	char filterChoice[10];
	printf("\nDo you wish to add filters ? (Y = yes, other to return to menu) ");
	getUserMenuChoice(filterChoice, 9, "Do you wish to add filters ? (Y = yes, other to return to menu) ");
	if (tolower(filterChoice[0]) == 'y')
	{
		bookingDisplayFilters(&data[0], count);
	}

}

void bookingDisplayFilters(BookingData *data, int dataCount)
{
	BookingData *filteredData[100];
	int filteredDataCount;
	char retryChoice[10]; // to ask user if user wants to keep on filtering after printing of data

	// Filters to be used
	Date dotFrom, dotTo, bookFrom, bookTo;
	int timeslot[6] = { 0,0,0,0,0,0 }; // for TimeslotBooked
	char facilityID[100][100];
	char staffID[100][100];
	char userID[100][100];
	int fCount = 0, sCount = 0, uCount = 0; // to keep track of how many entries need to be selected
	int isSet[] = { 0,0,0 ,0 ,0 ,0 }; // to keep track of what filters are set

	char filterChoice[10];
	int recordsCount = 0; // to keep track of how many records is printed
	do {
		recordsCount = 0;
		do {
			recordsCount = 0;
			char statusText[6][100] = { "", "", "" , "" , "" , "" };
			if (isSet[0]) sprintf(statusText[0], "%02d/%02d/%04d - %02d/%02d/%04d", dotFrom.d, dotFrom.m, dotFrom.y, dotTo.d, dotTo.m, dotTo.y); else strcpy(statusText[0], "Not Set");
			if (isSet[1]) sprintf(statusText[1], "%02d/%02d/%04d - %02d/%02d/%04d", bookFrom.d, bookFrom.m, bookFrom.y, bookTo.d, bookTo.m, bookTo.y); else strcpy(statusText[1], "Not Set");
			if (isSet[2])
			{
				for (int a = 0; a < 6; a++)
				{
					if (timeslot[a])
					{
						if (a == 0) {
							sprintf(statusText[2], "%s", TIMESLOTS[a]);
						}
						else
						{
							sprintf(statusText[2], "%s, %s", statusText[2], TIMESLOTS[a]);
						}
					}
				}
			}
			else strcpy(statusText[2], "Not Set");
			if (isSet[3]) break; else strcpy(statusText[3], "Not Set");
			if (isSet[4]) break; else strcpy(statusText[4], "Not Set");
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
						sprintf(statusText[5], "%s", getUserDataByID(userID[a])->name);
					}
					else
					{
						sprintf(statusText[5], "%s, %s", statusText[5], getUserDataByID(userID[a])->name);
					}
				}
			}
			else strcpy(statusText[5], "Not Set");
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
				break;
			case '5':
				break;
			case '6':
				isSet[5] = dispFilterUserInvolved(&userID[0], &uCount);
				break;
			case '7':
				return;
			case 'X':
			case 'x':
				filteredDataCount = generateFilteredSearchResult(filteredData, data, dataCount, &isSet[0], &dotFrom, &dotTo, &bookFrom, &bookTo, &timeslot[0]);
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
int dispFilterUserInvolved(char userIDsfilter[][100], int *uCount)
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

	do{
		elementRemoved = 0;
		usrFound = 0;

		printf("\nUsers in filter:\n");
		for (int a = 0; a < *uCount; a++)
		{
			printf("\t%d. %s\n", a + 1, getUserDataByID(userIDsfilter[a])->name);
		}
		printf("\n");
		
		printf("--> Enter 'X' to comfirm user filters\n");
		printf("--> Enter 'XXX' to unset user filters\n---> Enter the same username to unset them\n");
		printf("--> Enter username to add into filter\n>>> ");
		s_input(usrName, 99);
		// if user wants to cancel
		if (strcmp(trimwhitespace(usrName), "X") == 0 || strcmp(trimwhitespace(usrName), "x") == 0)
		{
			return 1;
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
					if (strcmp(usrData[a].id, userIDsfilter[b]) == 0)
					{
						// remove an element in array -> bad idea
						for (int c = b; c < *uCount - 1; c++)
						{
							strcpy(userIDsfilter[c], userIDsfilter[c + 1]);
						}
						elementRemoved = 1;
						usrFound = 1;
						*uCount = *uCount - 1;
						break;
					}
				}
				if (elementRemoved == 0) { // if no element is being removed
					printf("User found.\n");
					strcpy(userIDsfilter[*uCount], usrData[a].id);
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
int dispFilterStaffInvovled(char staffIDFilter[][100], int *sCount)
{
	if (staffDataCount == 0)
	{
		printf("There are no staffs in the system...\n");
		system("pause");
		return 0;
	}
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
		printf("User of ID \"%s\" was not found.\n", bData->usrID);
		system("pause");
		return;
	}
	Facility *fac = getFacilityByID(bData->facilityID);
	if (fac == NULL)
	{
		printf("Facility of ID \"%s\" was not found.\n", bData->facilityID);
		system("pause");
		return;
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
	printf("  | ID              : %-16.16s | | ID          : %-20.20s | | ID              : %-16.16s |\n", usr->id, fac->id, stf->stfID);
	printf("  | Name            : %-16.16s | | Type        : %-20.20s | | Name            : %-16.16s |\n", usr->name, fac->type, stf->stfName);
	printf("  | Date registered : %02d/%02d/%04d %02d:%02d | | Description : %-20.20s | | Position        : %-16.16s |\n", usr->dateEnter.d, usr->dateEnter.m, usr->dateEnter.y, usr->timeEnter.h, usr->timeEnter.m,fac->description, stf->stfPosi);
	printf("  | Gender          : %-16.16s | | Venue       : %-20.20s | | Date Registered : %02d/%02d/%04d       |\n", usr->gender, fac->venue, stf->dateRegis.d, stf->dateRegis.m, stf->dateRegis.y);
	printf("  | Contact         : %-16.16s | | Max User    : %-20d | |                                    |\n", usr->contact, fac->maxUser);
	printf("  |                                    | |                                    | |                                    |\n");
	printf("  -------------------------------------- -------------------------------------- --------------------------------------\n");
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
	/*char rawInput[100];
	char *trimmedInput;
	char *endPtr;*/
	int userChoice;
	// Ask user to select facility
	if (facilityDataCount == 0)
	{
		printf("There are no facilities registered in the system.\n");
		system("pause");
		return 0;
	}
	do{
		printf("Select one of the following facilities: \n");
		/*
		Insert code to get all facilities
		Need to count how many facilities are there?
		*/
		for (int a = 0; a < facilityDataCount; a++)
		{
			printf("\t%d. %s\n", a+1, facData[a].description);
		}
		printf("\nSelect Facility you wish to book: ");
		/*s_input(rawInput, 99);
		trimmedInput = trimwhitespace(rawInput);
		userChoice = strtol(trimmedInput, &endPtr, 10);
		if (*endPtr == '\0' && strlen(trimmedInput) != 0)
		{
			if (userChoice > 0 && userChoice <= facilityDataCount)
			{
				break;
			}
		}*/
		if (i_input(&userChoice)) // if user entered integer
		{
			if (userChoice > 0 && userChoice <= facilityDataCount) // if user input is within range
				break;
		}
		printf("\n<!> ERR: Invalid Choice. <!>\n");
		system("pause");
	} while (1);
	strcpy(userPickedfacilityID, facData[userChoice - 1].id);
	return 1;


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
	if (!checkForTimeslotsAvailablity(timeslotAvailable, data, dataSize, bookingDate, facilityID)) {
		printf("Sorry, but there are no free timeslots on that day for that facility, please try other facility / date\n");
		return 0;
	}
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

		} while (userPickedtimeslotSTR[0] < '1' || userPickedtimeslotSTR[0] > '6');
		err = 1;
		*userPickedtimeslot = strtol(userPickedtimeslotSTR, NULL, 10) - 1;
	} while (!timeslotAvailable[*userPickedtimeslot]); // while that timeslot is booked
	err = 0;
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
		if (strcmp(usrID, "XXX") == 0)
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
			printf("\nUser Login Successful.\n");
			return 1;
		}
		else {
			printf("\nInvalid password.\n");
		}
	} while (1);
}


// ============================================================================================
// ============================================================================================
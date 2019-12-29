#include "fusage.h"
#include "stdcxx.h"
#include "booking.h"
#include "facility.h"
#include "staff.h"
#include "userinfo.h"

char timeSlots[6][15] = { "7am - 9am ", "9am - 11am", "1pm - 3pm ", "3pm - 5pm ", "5pm - 7pm ", "7pm - 9pm " };
int totalRecord;
BookingData bData[100];

void fusagemain()
{
	if (staffLogin())
	{
		fUsageRecord();
		while (fUsageMenu())
		{
			continue;
		}
	}
}

void fUsageRecord()
{
	totalRecord = 0;
	FILE* f = fopen(fUsageFilePath, "r");
	if (!chkFileExist(f))
	{
		readBookingFileToFUsageFile();
		printf("There is currently no Facilities Usage Record in the system.\n");
		system("pause");
		return 0;
	}

	while (fscanf(f, "\n%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
		&fUsage[totalRecord].date.d, &fUsage[totalRecord].date.m, &fUsage[totalRecord].date.y,
		fUsage[totalRecord].time, fUsage[totalRecord].userID,
		fUsage[totalRecord].facilityID, fUsage[totalRecord].usageType) != EOF)
	{
		totalRecord++;
	}
	fclose(f);
	system("pause");
}

void fUsageAddRecord()
{
	FacilityUsage addFUsage;
	FacilityUsage storeTime[100];
	bDataCount = readBookingDataIntoStructArray(&bData[0], 100);

	char back[10];
	char cfrm[10], cfrm2[10];
	char choice[10], selection[10], ctn[10];
	char chgTime[30], chgUserID[6], chgFacilityID[6];
	int i;

	Date currentDate;
	getSystemDate(&currentDate);

	strcpy(addFUsage.usageType, "walked-in");

	FILE* f = fopen(fUsageFilePath, "a");
	if (f == NULL)
	{
		printf("There are currently no Facilities Usage Record in system !!!\n");
		system("pause");
		return 0;
	}
	do
	{
		printf("+====================================+\n");
		printf("|     Add Facility Usage Record      |\n");
		printf("+====================================+\n");
		printf("Enter '0' to EXIT (Other to Continue) >> ");
		getUserMenuChoice(back, 9, "Enter '0' to EXIT (Other to Continue) >> ");
		if (back[0] == '0')
		{
			return;
		}
		
		date(&addFUsage.date);

		slctTime(&addFUsage.time);
		i = strtol(addFUsage.time, NULL, 10) - 1;
		
		slctFacilityID(&addFUsage.facilityID);
		
		int tsIDX;
		for (int a = 0; a < bDataCount; a++)
		{
			if ((tsIDX = getTimeslotBooked(&bData[a].timeSlotsBooked)) != -1)
			{
				strcpy(storeTime[a].time, timeSlots[tsIDX]);
			}
		}
		for (int a = 0; a < bDataCount; a++)
		{
			while (addFUsage.date.d == bData[a].bookingDate.d && addFUsage.date.m == bData[a].bookingDate.m &&
				addFUsage.date.y == bData[a].bookingDate.y && strcmp(addFUsage.facilityID, bData[a].facilityID) == 0 &&
				strcmp(timeSlots[i], storeTime[a].time) == 0)
			{
				printf("\n\t\t<*! Process Failed !*>\n");
				printf("This Facility on this DATE and TIME has been TAKEN !!!\n");
				printf("Please try again.\n");
				date(&addFUsage.date);
				slctTime(&addFUsage.time);
				i = strtol(addFUsage.time, NULL, 10) - 1;
				slctFacilityID(&addFUsage.facilityID);
			}
		}
		slctUserID(&addFUsage.userID);

		system("cls");
		printf("+==============================+\n");
		printf("|    Facilities Usage added    |\n");
		printf("+==============================+\n");
		printf("Date        : %02d/%02d/%d\n", addFUsage.date.d, addFUsage.date.m, addFUsage.date.y);
		printf("Time        : %s\n", timeSlots[i]);
		printf("User ID     : %s (%s)\n", addFUsage.userID, getUserID(addFUsage.userID)->name);
		printf("Facility ID : %s (%s)\n", addFUsage.facilityID, getFacilityID(addFUsage.facilityID)->name);
		printf("Usage Type  : %s\n", addFUsage.usageType);

		printf("\nConfirm to add this record? (Y=Yes/N=No) : ");
		getUserMenuChoice(cfrm, 9,
			"Invalid Input !!!\nPlease select between (Y/N).\nConfirm to add this record? (Y=Yes/N=No) : ");
		while (toupper(cfrm[0]) != 'Y' && toupper(cfrm[0]) != 'N')
		{
			printf("Invalid Input !!!\nPlease select between (Y/N).\n");
			printf("Confirm to add this record? (Y=Yes/N=No) : ");
			getUserMenuChoice(cfrm, 9,
				"Invalid Input !!!\nPlease select between (Y/N).\nConfirm to add this record? (Y=Yes/N=No) : ");
		}
		if (toupper(cfrm[0]) == 'Y')
		{
			fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
				addFUsage.date.d, addFUsage.date.m, addFUsage.date.y, timeSlots[i],
				addFUsage.userID, addFUsage.facilityID, addFUsage.usageType);
			printf("<* Added successfully to Facility Usage Record *>\n");
		}
		if (toupper(cfrm[0]) == 'N')
		{
			printf("\nSelect        :\n");
			printf("              Change Details   >> C\n");
			printf("              Continue Process >> X\n");
			printf("choice (C/X) : ");
			getUserMenuChoice(choice, 9, "Invalid Input !!!\nPlease select between (C/X).\nchoice (C/X) : ");
			while (toupper(choice[0]) != 'C' && toupper(choice[0]) != 'X')
			{
				printf("Invalid Input !!!\nPlease select between (C/X).\n");
				printf("\nSelect        :\n");
				printf("              Change Details   >> C\n");
				printf("              Continue Process >> X\n");
				printf("choice (C/X) : ");
				getUserMenuChoice(choice, 9, "Invalid Input !!!\nPlease select between (C/X).\nchoice (C/X) : ");
			}
			if (toupper(choice[0]) == 'C')
			{
				printf("\n+=====================================+\n");
				printf("|          Details to Change          |\n");
				printf("+=====================================+\n");
				printf("| 1. Time                             |\n");
				printf("| 2. User ID                          |\n");
				printf("| 3. Facility ID                      |\n");
				printf("+=====================================+\n");
				printf("Enter Details to Change (1-3): ");
				getUserMenuChoice(selection, 9,
					"Invalid Input !!!\nPlease select between (1-3).\nEnter Details to change (1-3): ");
				while (selection[0] < '1' || selection[0] > '3')
				{
					printf("Invalid Input !!!\nPlease select between (1-3).\n");
					printf("Enter Details to Change (1-3): ");
					getUserMenuChoice(selection, 9,
						"Invalid Input !!!\nPlease select between (1-3).\nEnter Details to change (1-3): ");
				}
				switch (selection[0])
				{
				case'1':
					slctTime(&addFUsage.time);
					int b = strtol(addFUsage.time, NULL, 10) - 1;
					for (int a = 0; a < bDataCount; a++)
					{
						while (addFUsage.date.d == bData[a].bookingDate.d && addFUsage.date.m == bData[a].bookingDate.m &&
							addFUsage.date.y == bData[a].bookingDate.y && strcmp(addFUsage.facilityID, bData[a].facilityID) == 0 &&
							strcmp(timeSlots[b], storeTime[a].time) == 0)
						{
							printf("\n\t\t<*! Process Failed !*>\n");
							printf("This Facility on this DATE and TIME has been TAKEN !!!\n");
							printf("Please try again.\n");
							slctTime(&addFUsage.time);
							b = strtol(addFUsage.time, NULL, 10) - 1;
						}
					}
					printf("\n+============================+\n");
					printf("|    Detail Before Change    |\n");
					printf("+============================+\n");
					printf("Date        : %02d/%02d/%d\n", addFUsage.date.d, addFUsage.date.m, addFUsage.date.y);
					printf("Time        : %s\n", timeSlots[i]);
					printf("User ID     : %s (%s)\n", addFUsage.userID, getUserID(addFUsage.userID)->name);
					printf("Facility ID : %s (%s)\n", addFUsage.facilityID, getFacilityID(addFUsage.facilityID)->name);
					printf("Usage Type  : %s\n", addFUsage.usageType);

					printf("\n+============================+\n");
					printf("|    Detail After Change     |\n");
					printf("+============================+\n");
					printf("Date        : %02d/%02d/%d\n", addFUsage.date.d,
						addFUsage.date.m, addFUsage.date.y);
					printf("Time        : %s\n", timeSlots[b]);
					printf("User ID     : %s (%s)\n", addFUsage.userID, getUserID(addFUsage.userID)->name);
					printf("Facility ID : %s (%s)\n", addFUsage.facilityID, getFacilityID(addFUsage.facilityID)->name);
					printf("Usage Type  : %s\n", addFUsage.usageType);

					printf("\nConfirm to add this record? (Y=Yes/N=No) : ");
					getUserMenuChoice(cfrm2, 9,
						"Invalid Input !!!\nPlease select between (Y/N).\nConfirm to add this record? (Y=Yes/N=No) : ");
					while (toupper(cfrm2[0]) != 'Y' && toupper(cfrm2[0]) != 'N')
					{
						printf("Invalid Input !!!\nPlease select between (Y/N).\n");
						printf("Confirm to add this record? (Y=Yes/N=No) : ");
						getUserMenuChoice(cfrm2, 9,
							"Invalid Input !!!\nPlease select between (Y/N).\nConfirm to add this record? (Y=Yes/N=No) : ");
					}
					if (toupper(cfrm2[0]) == 'Y')
					{
						fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
							addFUsage.date.d, addFUsage.date.m, addFUsage.date.y,
							timeSlots[b], addFUsage.userID, addFUsage.facilityID, addFUsage.usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}
					break;
				case'2':
					slctUserID(&chgUserID);
					i = strtol(addFUsage.time, NULL, 10) - 1;
					printf("\n+============================+\n");
					printf("|    Detail Before Change    |\n");
					printf("+============================+\n");
					printf("Date        : %02d/%02d/%d\n", addFUsage.date.d, addFUsage.date.m, addFUsage.date.y);
					printf("Time        : %s\n", timeSlots[i]);
					printf("User ID     : %s (%s)\n", addFUsage.userID, getUserID(addFUsage.userID)->name);
					printf("Facility ID : %s (%s)\n", addFUsage.facilityID ,getFacilityID(addFUsage.facilityID)->name);
					printf("Usage Type  : %s\n", addFUsage.usageType);

					printf("\n+============================+\n");
					printf("|    Detail After Change     |\n");
					printf("+============================+\n");
					printf("Date        : %02d/%02d/%d\n", addFUsage.date.d,
						addFUsage.date.m, addFUsage.date.y);
					printf("Time        : %s\n", timeSlots[i]);
					printf("User ID     : %s (%s)\n", chgUserID, getUserID(chgUserID)->name);
					printf("Facility ID : %s (%s)\n", addFUsage.facilityID, getFacilityID(addFUsage.facilityID)->name);
					printf("Usage Type  : %s\n", addFUsage.usageType);

					printf("\nConfirm to add this record? (Y=Yes/N=No) : ");
					getUserMenuChoice(cfrm2, 9,
						"Invalid Input !!!\nPlease select between (Y/N).\nConfirm to add this record? (Y=Yes/N=No) : ");
					while (toupper(cfrm2[0]) != 'Y' && toupper(cfrm2[0]) != 'N')
					{
						printf("Invalid Input !!!\nPlease select between (Y/N).\n");
						printf("Confirm to add this record? (Y=Yes/N=No) : ");
						getUserMenuChoice(cfrm2, 9,
							"Invalid Input !!!\nPlease select between (Y/N).\nConfirm to add this record? (Y=Yes/N=No) : ");
					}
					if (toupper(cfrm2[0]) == 'Y')
					{
						fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
							addFUsage.date.d, addFUsage.date.m, addFUsage.date.y,
							timeSlots[i], chgUserID, addFUsage.facilityID, addFUsage.usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}
					break;
				case'3':
					slctFacilityID(&chgFacilityID);
					i = strtol(addFUsage.time, NULL, 10) - 1;
					for (int a = 0; a < bDataCount; a++)
					{
						while (addFUsage.date.d == bData[a].bookingDate.d && addFUsage.date.m == bData[a].bookingDate.m &&
							addFUsage.date.y == bData[a].bookingDate.y && strcmp(chgFacilityID, bData[a].facilityID) == 0 &&
							strcmp(timeSlots[i], storeTime[a].time) == 0)
						{
							printf("\n\t\t<*! Process Failed !*>\n");
							printf("This Facility on this DATE and TIME has been TAKEN !!!\n");
							printf("Please try again.\n");
							slctFacilityID(&chgFacilityID);
						}
					}
					printf("\n+============================+\n");
					printf("|    Detail Before Change    |\n");
					printf("+============================+\n");
					printf("Date        : %02d/%02d/%d\n", addFUsage.date.d, addFUsage.date.m, addFUsage.date.y);
					printf("Time        : %s\n", timeSlots[i]);
					printf("User ID     : %s (%s)\n", addFUsage.userID, getUserID(addFUsage.userID)->name);
					printf("Facility ID : %s (%s)\n", addFUsage.facilityID, getFacilityID(addFUsage.facilityID)->name);
					printf("Usage Type  : %s\n", addFUsage.usageType);

					printf("\n+============================+\n");
					printf("|    Detail After Change     |\n");
					printf("+============================+\n");
					printf("Date        : %02d/%02d/%d\n", addFUsage.date.d,
						addFUsage.date.m, addFUsage.date.y);
					printf("Time        : %s\n", timeSlots[i]);
					printf("User ID     : %s (%s)\n", addFUsage.userID, getUserID(addFUsage.userID)->name);
					printf("Facility ID : %s (%s)\n", chgFacilityID, getFacilityID(chgFacilityID)->name);
					printf("Usage Type  : %s\n", addFUsage.usageType);

					printf("\nConfirm to add this record? (Y=Yes/N=No) : ");
					getUserMenuChoice(cfrm2, 9,
						"Invalid Input !!!\nPlease select between (Y/N).\nConfirm to add this record? (Y=Yes/N=No) : ");
					while (toupper(cfrm2[0]) != 'Y' && toupper(cfrm2[0]) != 'N')
					{
						printf("Invalid Input !!!\nPlease select between (Y/N).\n");
						printf("Confirm to add this record? (Y=Yes/N=No) : ");
						getUserMenuChoice(cfrm2, 9,
							"Invalid Input !!!\nPlease select between (Y/N).\nConfirm to add this record? (Y=Yes/N=No) : ");
					}
					if (toupper(cfrm2[0]) == 'Y')
					{
						fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
							addFUsage.date.d, addFUsage.date.m, addFUsage.date.y,
							timeSlots[i], addFUsage.userID, chgFacilityID, addFUsage.usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}
					break;
				default:
					return;
				}
			}
		}
		printf("\nContinue to add record? (Y=Yes/N=No) : ");
		getUserMenuChoice(ctn, 9,
			"Invalid Input !!!\nPlease select between (Y/N).\nContinue to add record? (Y=Yes/N=No) : ");
		while (toupper(ctn[0]) != 'Y' && toupper(ctn[0]) != 'N')
		{
			printf("Invalid Input !!!\nPlease select between (Y/N).\n");
			printf("Continue to add record? (Y=Yes/N=No) : ");
			getUserMenuChoice(ctn, 9,
				"Invalid Input !!!\nPlease select between (Y/N).\nContinue to add record? (Y=Yes/N=No) : ");
		}
		system("cls");
	} while (toupper(ctn[0]) == 'Y');
	fclose(f);
}

void fUsageSearchRecord()
{
	FacilityUsage searchFUsage;
	Facility* fName;
	userData* uName[100];

	Date currentDate;
	getSystemDate(&currentDate);
	
	int day, month, year;
	char userID[50], time[30], facilityID[50], usageType[30];
	char choice[10];
	int r;
	int count = 0;
	int dateErr = 0;

	FILE* f = fopen(fUsageFilePath, "r");
	if (!chkFileExist(f))
	{
		printf("There are currently no Facilities Usage Record in system !!!\n");
		system("pause");
		return 0;
	}

	printf("+=======================================+\n");
	printf("|     Search Facility Usage Record      |\n");
	printf("+=======================================+\n");

	printf("Search By :\n");
	printf("+=====================+\n");
	printf("| 1. Date             |\n");
	printf("| 2. Time             |\n");
	printf("| 3. User ID          |\n");
	printf("| 4. Facility ID      |\n");
	printf("| 5. Usage Type       |\n");
	printf("+=====================+\n");
	printf("Enter '0' to EXIT.\n");
	printf("Enter detail to search (1-5) : ");
	getUserMenuChoice(choice, 9, "Invalid Input !!!\nEnter detail to search (1-5) : ");
	if (choice[0] == '0')
	{
		return;
	}
	while (choice[0] < '1' || choice[0] > '5')
	{
		printf("Invalid Input !!!\n");
		printf("Enter Details to Change (1-5): ");
		getUserMenuChoice(choice, 9, "Invalid Input !!!\nEnter Details to change (1-5): ");
	}
	switch (choice[0])
	{
	case'1':
		do {
			if (dateErr)
			{
				printf("Invalid Date, try again !!!\n");
			}
			dateErr = 1;
			printf("Enter Date < DD/MM/YYYY > : ");
			rewind(stdin);
			r = scanf("%d/%d/%d", &day, &month, &year);
			rewind(stdin);
		} while (r != 3 || !validateDate(day, month, year));
		err = 0;

		printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
		printf("====\t\t====\t\t=======\t\t===========\t==========\n");
		while (fscanf(f, "%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&searchFUsage.date.d, &searchFUsage.date.m, &searchFUsage.date.y,
			searchFUsage.time, searchFUsage.userID, searchFUsage.facilityID, searchFUsage.usageType) != EOF)
		{
			if (searchFUsage.date.d == day && searchFUsage.date.m == month && searchFUsage.date.y == year)
			{
				printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", searchFUsage.date.d, searchFUsage.date.m,
					searchFUsage.date.y, searchFUsage.time, searchFUsage.userID,
					searchFUsage.facilityID, searchFUsage.usageType);
				count++;
			}
		}
		if (count != 0)
		{
			printf("\n<*! Total %d record founded on this DATE !*>\n", count);
		}
		if (count == 0)
		{
			printf("<*! No record founded on this DATE !*>\n");
		}
		break;
	case'2':
		slctTime(&time);
		int a = strtol(time, NULL, 10) - 1;
		printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
		printf("====\t\t====\t\t=======\t\t===========\t==========\n");
		while (fscanf(f, "%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&searchFUsage.date.d, &searchFUsage.date.m, &searchFUsage.date.y,
			searchFUsage.time, searchFUsage.userID, searchFUsage.facilityID, searchFUsage.usageType) != EOF)
		{
			if (strcmp(searchFUsage.time, timeSlots[a]) == 0)
			{
				printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", searchFUsage.date.d, searchFUsage.date.m,
					searchFUsage.date.y, searchFUsage.time, searchFUsage.userID,
					searchFUsage.facilityID, searchFUsage.usageType);
				count++;
			}
		}
		if (count != 0)
		{
			printf("\n<*! Total %d record founded on this TIME !*>\n", count);
		}
		if (count == 0)
		{
			printf("<*! No record founded on this TIME !*>\n");
		}
		break;
	case'3':
		slctUserID(&userID);
		printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
		printf("====\t\t====\t\t=======\t\t===========\t==========\n");
		while (fscanf(f, "%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&searchFUsage.date.d, &searchFUsage.date.m, &searchFUsage.date.y,
			searchFUsage.time, searchFUsage.userID, searchFUsage.facilityID, searchFUsage.usageType) != EOF)
		{
			if (strcmp(searchFUsage.userID, userID) == 0)
			{
				count++;
				printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", searchFUsage.date.d, searchFUsage.date.m,
					searchFUsage.date.y, searchFUsage.time, searchFUsage.userID,
					searchFUsage.facilityID, searchFUsage.usageType);
			}
		}
		if (count == 0)
		{
			printf("No record founded on this User ID.\n");
		}
		if (count != 0)
		{
			printf("\n<*! Total %d record founded on this User ID !*>\n", count);
		}
		break;
	case'4':
		slctFacilityID(facilityID);
		printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
		printf("====\t\t====\t\t=======\t\t===========\t==========\n");
		while (fscanf(f, "%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&searchFUsage.date.d, &searchFUsage.date.m, &searchFUsage.date.y,
			searchFUsage.time, searchFUsage.userID, searchFUsage.facilityID, searchFUsage.usageType) != EOF)
		{
			if (strcmp(searchFUsage.facilityID, facilityID) == 0)
			{
				printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", searchFUsage.date.d, searchFUsage.date.m,
					searchFUsage.date.y, searchFUsage.time, searchFUsage.userID,
					searchFUsage.facilityID, searchFUsage.usageType);
				count++;
			}
		}
		if (count != 0)
		{
			printf("\n<*! Total %d record founded on this Facility ID !*>\n", count);
		}
		if (count == 0)
		{
			printf("<*! No record founded on this Facility ID !*>\n");
		}
		break;
	case'5':
		printf("Enter Usage Type (walked-in / booked) : ");
		rewind(stdin);
		scanf("%[^\n]", usageType);
		rewind(stdin);
		while (strcmp(usageType, "walked-in") != 0 && strcmp(usageType, "booked") != 0)
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter Usage Type (walked-in / booked) : ");
			rewind(stdin);
			scanf("%[^\n]", usageType);
			rewind(stdin);
		}
		printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
		printf("====\t\t====\t\t=======\t\t===========\t==========\n");
		while (fscanf(f, "%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&searchFUsage.date.d, &searchFUsage.date.m, &searchFUsage.date.y,
			searchFUsage.time, searchFUsage.userID, searchFUsage.facilityID, searchFUsage.usageType) != EOF)
		{
			if (strcmp(searchFUsage.usageType, usageType) == 0)
			{
				printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", searchFUsage.date.d, searchFUsage.date.m,
					searchFUsage.date.y, searchFUsage.time, searchFUsage.userID,
					searchFUsage.facilityID, searchFUsage.usageType);
				count++;
			}
		}
		if (count != 0)
		{
			printf("\n<*! Total %d record founded on this Facility UsageType !*>\n", count);
		}
		if (count == 0)
		{
			printf("<*! No record founded on this Facility UsageType !*>\n");
		}
		break;
	default:
		return;
	}

	fclose(f);
	system("pause");
}

void fUsageModify()
{
	int count = 0;
	FILE* f = fopen(fUsageFilePath, "r");
	if (!chkFileExist(f))
	{
		printf("There are currently no Facilities Usage Record in system !!!\n");
		system("pause");
		return 0;
	}
	while (fscanf(f, "\n%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
		&fUsage[count].date.d, &fUsage[count].date.m, &fUsage[count].date.y,
		fUsage[count].time, fUsage[count].userID,
		fUsage[count].facilityID, fUsage[count].usageType) != EOF)
	{
		count++;
	}
	fclose(f);

	FacilityUsage* modifyFUsage;
	FacilityUsage cacheData;

	Date currentDate;
	getSystemDate(&currentDate);

	char ctn;

	do
	{
		system("cls");
		printf("+=======================================+\n");
		printf("|     Modify Facility Usage Record      |\n");
		printf("+=======================================+\n");

		char back[10];
		int total = 0;
		int selection = 0, choice = 0;
		char cfrm;
		int i = 0;

		printf("No.\tDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
		printf("===\t====\t\t====\t\t=======\t\t===========\t==========\n");
		for (int a = 0; a < count; a++)
		{
			total++;
			printf("%-7d %02d/%02d/%-9d %-15s %-15s %-15s %s\n", total,
				fUsage[a].date.d, fUsage[a].date.m, fUsage[a].date.y,
				fUsage[a].time, fUsage[a].userID,
				fUsage[a].facilityID, fUsage[a].usageType);
		}
		printf("\nEnter '0' to EXIT (Other to Continue) >> ");
		getUserMenuChoice(back, 9, "Enter '0' to EXIT (Other to Continue) >> ");
		if (back[0] == '0')
		{
			return;
		}
		printf("Choose No. of record to modify (1 - %d) : ", total);
		rewind(stdin);
		scanf("%d", &selection);
		rewind(stdin);
		while (selection < 1 || selection > total)
		{
			printf("Invalid Input !!!\n");
			printf("Please select between (1 - %d) : ", total);
			rewind(stdin);
			scanf("%d", &selection);
			rewind(stdin);
		}
		modifyFUsage = &fUsage[selection - 1];

		cacheData.date.d = modifyFUsage->date.d;
		cacheData.date.m = modifyFUsage->date.m;
		cacheData.date.y = modifyFUsage->date.y;
		strcpy(cacheData.time, modifyFUsage->time);
		strcpy(cacheData.userID, modifyFUsage->userID);
		strcpy(cacheData.facilityID, modifyFUsage->facilityID);
		strcpy(cacheData.usageType, modifyFUsage->usageType);

		printf("\n+============================+\n");
		printf("|    Your selected Reocrd    |\n");
		printf("+============================+\n");
		printf("Date        : %02d/%02d/%d\n", cacheData.date.d,
			cacheData.date.m, cacheData.date.y);
		printf("Time        : %s\n", cacheData.time);
		printf("User ID     : %s\n", cacheData.userID);
		printf("Facility ID : %s\n", cacheData.facilityID);
		printf("Usage Type  : %s\n", cacheData.usageType);

		printf("\nChoose One to Modify :\n");
		printf("+==================+\n");
		printf("| 1. Time          |\n");
		printf("| 2. Facility ID   |\n");
		printf("+==================+\n");
		printf("Enter your choice (1 - 2) : ");
		rewind(stdin);
		scanf("%d", &choice);
		rewind(stdin);
		while (choice < 1 || choice > 2)
		{
			printf("Invalid Input !!!\n");
			printf("Please select between (1 - 2) : ");
			rewind(stdin);
			scanf("%d", &choice);
			rewind(stdin);
		}
		switch (choice)
		{
		case 1:
			slctTime(cacheData.time);
			i = strtol(cacheData.time, NULL, 10) - 1;
			break;
		case 2:
			slctFacilityID(cacheData.facilityID);
			break;
		default:
			break;
		}

		printf("\n+============================+\n");
		printf("|    Record before Modify    |\n");
		printf("+============================+\n");
		printf("Date        : %02d/%02d/%d\n", modifyFUsage->date.d,
			modifyFUsage->date.m, modifyFUsage->date.y);
		printf("Time        : %s\n", modifyFUsage->time);
		printf("User ID     : %s\n", modifyFUsage->userID);
		printf("Facility ID : %s\n", modifyFUsage->facilityID);
		printf("Usage Type  : %s\n", modifyFUsage->usageType);

		if (choice == 1)
		{
			printf("\n+============================+\n");
			printf("|    Record After Modify     |\n");
			printf("+============================+\n");
			printf("Date        : %02d/%02d/%d\n", cacheData.date.d,
				cacheData.date.m, cacheData.date.y);
			printf("Time        : %s\n", timeSlots[i]);
			printf("User ID     : %s\n", cacheData.userID);
			printf("Facility ID : %s\n", cacheData.facilityID);
			printf("Usage Type  : %s\n", cacheData.usageType);
		}
		else
		{
			printf("\n+============================+\n");
			printf("|    Record After Modify     |\n");
			printf("+============================+\n");
			printf("Date        : %02d/%02d/%d\n", cacheData.date.d,
				cacheData.date.m, cacheData.date.y);
			printf("Time        : %s\n", cacheData.time);
			printf("User ID     : %s\n", cacheData.userID);
			printf("Facility ID : %s\n", cacheData.facilityID);
			printf("Usage Type  : %s\n", cacheData.usageType);
		}
		printf("\nConfirm to modify this Record ? (Y=Yes/N=No) : ");
		rewind(stdin);
		scanf("%c", &cfrm);
		rewind(stdin);
		while (toupper(cfrm) != 'Y' && toupper(cfrm) != 'N')
		{
			printf("Invalid Input !!!\nPlease select between (Y/N)\n");
			printf("Confirm to modify this Record ? (Y=Yes/N=No) : ");
			rewind(stdin);
			scanf("%c", &cfrm);
			rewind(stdin);
		}
		if (toupper(cfrm) == 'Y')
		{
			if (choice == 1)
			{
				modifyFUsage->date.d = cacheData.date.d;
				modifyFUsage->date.m = cacheData.date.m;
				modifyFUsage->date.y = cacheData.date.y;
				strcpy(modifyFUsage->time, timeSlots[i]);
				strcpy(modifyFUsage->userID, cacheData.userID);
				strcpy(modifyFUsage->facilityID, cacheData.facilityID);
				strcpy(modifyFUsage->usageType, cacheData.usageType);
			}
			else
			{
				modifyFUsage->date.d = cacheData.date.d;
				modifyFUsage->date.m = cacheData.date.m;
				modifyFUsage->date.y = cacheData.date.y;
				strcpy(modifyFUsage->time, cacheData.time);
				strcpy(modifyFUsage->userID, cacheData.userID);
				strcpy(modifyFUsage->facilityID, cacheData.facilityID);
				strcpy(modifyFUsage->usageType, cacheData.usageType);
			}
		}
		printf("Continue to Modify Other Record ? (Y=Yes/N=No) : ");
		rewind(stdin);
		scanf("%c", &ctn);
		rewind(stdin);
		while (toupper(ctn) != 'Y' && toupper(ctn) != 'N')
		{
			printf("Invalid Input !!!\nPlease select between (Y/N).\n");
			printf("Continue to Modify Other Record ? (Y=Yes/N=No) : ");
			rewind(stdin);
			scanf("%c", &ctn);
			rewind(stdin);
		}
	} while (toupper(ctn) == 'Y');

	FILE* f2 = fopen(fUsageFilePath, "w");
	for (int a = 0; a < count; a++)
	{
		fprintf(f2, "%02d/%02d/%d|%s|%s|%s|%s\n",
			fUsage[a].date.d, fUsage[a].date.m, fUsage[a].date.y,
			fUsage[a].time, fUsage[a].userID,
			fUsage[a].facilityID, fUsage[a].usageType);
	}
	fclose(f2);
	
	system("pause");
}

void fUsageDisplay()
{
	FacilityUsage displayUsage;

	int countRcd = 0;
	FILE* f = fopen(fUsageFilePath, "r");
	if (!chkFileExist(f))
	{
		printf("There are currently no Facilities Usage Record in system !!!\n");
		system("pause");
		return 0;
	}
	printf("+========================================+\n");
	printf("|     Display Facility Usage Records     |\n");
	printf("+========================================+\n\n");
	printf("Date\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
	printf("====\t\t====\t\t=======\t\t===========\t==========\n");

	while (fscanf(f, "%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
		&displayUsage.date.d, &displayUsage.date.m, &displayUsage.date.y,
		displayUsage.time, displayUsage.userID, displayUsage.facilityID, displayUsage.usageType) != EOF)
	{
		printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n",
			displayUsage.date.d, displayUsage.date.m, displayUsage.date.y,
			displayUsage.time, displayUsage.userID, displayUsage.facilityID, displayUsage.usageType);
		countRcd++;
	}
	if (countRcd != 0)
	{
		printf("\n<*! Total %d Record founded in the FILE. !*>\n", countRcd);
	}
	fclose(f);
	system("pause");
}

int fUsageMenu()
{		
	char choiceText[][100] = { "Add Facilities Usage","Search Facilities Usage Record",
		"Modify Facilities Usage Record","Display all Facilities Usage Record","Return to console" };
	int choice = globalMainMenu("Facilities Usage Module", 5, choiceText);
	system("cls");
	switch (choice)
	{
	case 1:
		fUsageAddRecord();
		break;
	case 2:
		fUsageSearchRecord();
		break;
	case 3:
		fUsageModify();
		break;
	case 4:
		fUsageDisplay();
		break;
	case 5:
		sessionStaffID[0] = '\0';
		return 0;
	default:
		return 1;
	}
	return 1;
}

int staffLogin()
{
	if (!_staffLogin(sessionStaffID, 99))
	{
		return 0;
	}
	return 1;
}

int date(Date* date)
{
	// Date currentDate;
	// getSystemDate(&currentDate);
	getSystemDate(date);
	return 1;
	/*int r;
	int dateErr = 0; 
	do 
	{
		if (dateErr)
		{
			printf("Invalid Date, try again.\nOnly Allow to enter today's DATE.\n");
		}
		dateErr = 1;
		printf("Enter Date < DD/MM/YYYY > : ");
		rewind(stdin);
		r = scanf("%d/%d/%d", &date->d, &date->m, &date->y);
		rewind(stdin);
	} while (r != 3 || !validateDate(date->d, date->m,date->y) ||
		compareDate(date->d, date->m,date->y, currentDate.d, currentDate.m, currentDate.y) != 0);
	err = 0;
	return 1;*/
}

int slctTime(char* time)
{
	printf("Timeslots: \n");
	for (int a = 0; a < 6; a++)
	{
		printf("\t%d. %s \n", a + 1, timeSlots[a]);
	}
	printf("Please select timeslot from (1-6): ");
	getUserMenuChoice(time, 9, "Invalid Input !!!\nPlease, pick a timeslot (1-6): ");
	while (time[0] < '1' || time[0] > '6')
	{
		printf("Invalid Input !!!\n");
		printf("Please, pick a timeslot (1-6): ");
		getUserMenuChoice(time, 9, "Invalid Input !!!\nPlease, pick a timeslot (1-6): ");
	}
}

void slctFacilityID(char* facilityID)
{
	Facility* fID;
	fDataCount = 0;
	FILE* f2 = fopen(facilityFilePath, "rb");
	if (chkFileExist(f2))
	{
		while (fread(&fData[fDataCount], sizeof(Facility), 1, f2) != 0)
		{
			fDataCount++;
		}
	}
	fclose(f2);
	if (fDataCount == 0)
	{
		printf("\nThere is no Facility in the system.\n");
		system("pause");
		return;
	}
	printf("+====================================================+\n"
		"|       Facility Name       |       Facility ID      |\n"
		"+====================================================+\n");
	for (int i = 0; i < fDataCount; i++)
	{
		printf("|    %-20s   |           %-10s   |\n", fData[i].name, fData[i].id);
	}
	printf("+====================================================+\n");

	printf("Enter Facility ID : ");
	rewind(stdin);
	scanf("%[^\n]", facilityID);
	rewind(stdin);
	fID = getFacilityID(facilityID);
	while (fID ==NULL)
	{
		printf("This Facility ID does not EXIST !!!\nPlease try again.\n");
		printf("Enter Facility ID : ");
		rewind(stdin);
		scanf("%[^\n]", facilityID);
		rewind(stdin);
		fID = getFacilityID(facilityID);
	}
}

Facility* getFacilityID(char* ID)
{
	if (fDataCount == 0)
	{
		return NULL;
	}
	for (int i = 0; i < fDataCount; i++)
	{
		if (strcmp(fData[i].id, ID) == 0)
		{
			return &fData[i];
		}
	}
	return NULL;
}

void slctUserID(char* userID)
{
	userData* uID;
	uDataCount = 0;
	FILE* f2 = fopen(UserInfoFilePath, "rb");
	if (chkFileExist(f2))
	{
		while (fread(&uData[uDataCount], sizeof(userData), 1, f2) != 0)
		{
			uDataCount++;
		}
	}
	fclose(f2);

	printf("\nEnter User ID : ");
	rewind(stdin);
	scanf("%[^\n]", userID);
	rewind(stdin);
	uID = getUserID(userID);
	while (uID == NULL)
	{
		printf("This User ID does not EXIST !!!\nPlease try again.\n");
		printf("Enter User ID : ");
		rewind(stdin);
		scanf("%[^\n]", userID);
		rewind(stdin);
		uID = getUserID(userID);
	}
}

userData* getUserID(char* id)
{
	if (uDataCount == 0)
	{
		return NULL;
	}
	for (int i = 0; i < uDataCount; i++)
	{
		if (strcmp(uData[i].id, id) == 0)
		{
			return &uData[i];
		}
	}
	return NULL;
}

void readBookingFileToFUsageFile()
{
	FacilityUsage storeData;
	FILE* f2 = fopen(fUsageFilePath, "w");
	bDataCount = readBookingDataIntoStructArray(&bData[0], 100);

	for (int a = 0; a < bDataCount; a++)
	{
		storeData.date.d = bData[a].bookingDate.d;
		storeData.date.m = bData[a].bookingDate.m;
		storeData.date.y = bData[a].bookingDate.y;
		strcpy(storeData.userID, bData[a].usrID);
		strcpy(storeData.facilityID, bData[a].facilityID);
		strcpy(storeData.usageType, "booked");
		int tsIDX;
		if ((tsIDX = getTimeslotBooked(&bData[a].timeSlotsBooked)) != -1)
		{
			strcpy(storeData.time, timeSlots[tsIDX]);
		}
		fprintf(f2, "%02d/%02d/%d|%s|%s|%s|%s\n",
			storeData.date.d, storeData.date.m, storeData.date.y, storeData.time, storeData.userID,
			storeData.facilityID, storeData.usageType);
	}
	fclose(f2);
}

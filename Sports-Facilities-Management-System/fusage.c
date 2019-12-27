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
	/*if (_staffLogin(sessionStaffID, 100))
	{*/
		fUsageRecord();
		while (fUsageMenu())
		{
			continue;
		}
	/*}*/
}

void fUsageRecord()
{
	readBookingFileToFUsageFile();
	totalRecord = 0;
	FILE* f = fopen(fUsageFilePath, "r");
	if (!chkFileExist(f))
	{
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
	Date chgDate;
	FacilityUsage addFUsage;
	
	int back;
	char ctn, cfrm, ctnChg;
	char choice, selection[10], cfrm2;
	char chgTime[30], chgUserID[6], chgFacilityID[6], chgUsageType[20];
	int i;
	
	Date currentDate;
	getSystemDate(&currentDate);
	
	FILE* f = fopen(fUsageFilePath, "a");
	if (f == NULL)
	{
		printf("There are currently no Facilities Usage Record in system !!!\n");
		system("pause");
		return 0;
	}
	printf("+====================================+\n");
	printf("|     Add Facility Usage Record      |\n");
	printf("+====================================+\n");
	printf("Enter '0' to EXIT (Other to Continue) >> ");
	rewind(stdin);
	scanf("%d", &back);
	rewind(stdin);
	if (back == 0)
	{
		return;
	}
	do
	{
		date(&addFUsage.date);
		
		chkTime(&addFUsage.time);
		i = strtol(addFUsage.time, NULL, 10) - 1;
	
		slctFacilityID(&addFUsage.facilityID);
		//chkAvailableAdd(&addFUsage.date, &addFUsage.time, addFUsage.facilityID);
		slctUserID(&addFUsage.userID);

		printf("Enter Usage Type (walked-in / booked) : ");
		rewind(stdin);
		scanf("%[^\n]", addFUsage.usageType);
		while (strcmp(addFUsage.usageType, "walked-in") != 0 && strcmp(addFUsage.usageType, "booked") != 0)
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter Usage Type (walked-in / booked) : ");
			rewind(stdin);
			scanf("%[^\n]", addFUsage.usageType);
			rewind(stdin);
		}

		system("cls");
		printf("========================\n");
		printf("Facilities details added\n");
		printf("========================\n");
		printf("Date        : %02d/%02d/%d\n", addFUsage.date.d, addFUsage.date.m, addFUsage.date.y);
		printf("Time        : %s\n", timeSlots[i]);
		printf("User ID     : %s\n", addFUsage.userID);
		printf("Facility ID : %s\n", addFUsage.facilityID);
		printf("Usage Type  : %s\n", addFUsage.usageType);

		printf("\nConfirm to add this record? (Y=Yes/N=No) : ");
		rewind(stdin);
		scanf("%c", &cfrm);
		while (toupper(cfrm) != 'Y' && toupper(cfrm) != 'N')
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter Confirm to add this record? (Y=Yes/N=No) : ");
			rewind(stdin);
			scanf("%c", &cfrm);
			rewind(stdin);
		}
		if (toupper(cfrm) == 'Y')
		{
			fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
				addFUsage.date.d, addFUsage.date.m, addFUsage.date.y, timeSlots[i],
				addFUsage.userID, addFUsage.facilityID, addFUsage.usageType);
			printf("<* Added successfully to Facility Usage Record *>\n");
		}
		if (toupper(cfrm) == 'N')
		{
			printf("\nSelect        :\n");
			printf("              Change Details   >> C\n");
			printf("              Continue Process >> X\n");
			printf("choice  (C/X) : ");
			rewind(stdin);
			scanf("%c", &choice);
			while (toupper(choice) != 'C' && toupper(choice) != 'X')
			{
				printf("\nInvalid Input !!!\n");
				printf("Select       :\n");
				printf("             Change Details   >> C\n");
				printf("             Continue Process >> X\n");
				printf("choice (C/X) : ");
				rewind(stdin);
				scanf("%c", &choice);
				rewind(stdin);
			}
			if (toupper(choice) == 'C')
			{
				printf("\n+=====================================+\n");
				printf("|          Details to Change          |\n");
				printf("+=====================================+\n");
				printf("| 1. Date                             |\n");
				printf("| 2. Time                             |\n");
				printf("| 3. User ID                          |\n");
				printf("| 4. Facility ID                      |\n");
				printf("| 5. Usage Type                       |\n");
				printf("+=====================================+\n");
				printf("Enter Details to Change (1-5): ");
				getUserMenuChoice(selection, 9, "Invalid Input !!!\nEnter Details to change (1-5): ");
				while (selection[0] < '1' || selection[0] > '5')
				{
					printf("Invalid Input !!!\n");
					printf("Enter Details to Change (1-5): ");
					getUserMenuChoice(selection, 9, "Invalid Input !!!\nEnter Details to change (1-5): ");
				}
				switch (selection[0])
				{
				case'1':
					date(&chgDate);
					i = strtol(addFUsage.time, NULL, 10) - 1;
					printf("\n===================\n");
					printf("Detail After Change\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", chgDate.d,chgDate.m,chgDate.y);
					printf("Time        : %s\n", timeSlots[i]);
					printf("User ID     : %s\n", addFUsage.userID);
					printf("Facility ID : %s\n", addFUsage.facilityID);
					printf("Usage Type  : %s\n", addFUsage.usageType);

					printf("\nConfirm to add this record? (Y=Yes/N=No) : ");
					rewind(stdin);
					scanf("%c", &cfrm2);
					rewind(stdin);
					while (toupper(cfrm2) != 'Y' && toupper(cfrm2) != 'N')
					{
						printf("Invalid Input !!!\n");
						printf("Re-enter Confirm to add this record? (Y=Yes/N=No) : ");
						rewind(stdin);
						scanf("%c", &cfrm2);
						rewind(stdin);
					}
					if (toupper(cfrm2) == 'Y')
					{
						fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
							chgDate.d, chgDate.m, chgDate.y, timeSlots[i], addFUsage.userID,
							addFUsage.facilityID, addFUsage.usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}
					break;
				case'2':
					chkTime(&addFUsage.time);
					i = strtol(addFUsage.time, NULL, 10) - 1;
					printf("\n===================\n");
					printf("Detail After Change\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", addFUsage.date.d,
						addFUsage.date.m, addFUsage.date.y);
					printf("Time        : %s\n", timeSlots[i]);
					printf("User ID     : %s\n", addFUsage.userID);
					printf("Facility ID : %s\n", addFUsage.facilityID);
					printf("Usage Type  : %s\n", addFUsage.usageType);

					printf("\nConfirm to add this record? (Y=Yes/N=No) : ");
					rewind(stdin);
					scanf("%c", &cfrm2);
					rewind(stdin);
					while (toupper(cfrm2) != 'Y' && toupper(cfrm2) != 'N')
					{
						printf("Invalid Input !!!\n");
						printf("Re-enter Confirm to add this record? (Y=Yes/N=No) : ");
						rewind(stdin);
						scanf("%c", &cfrm2);
						rewind(stdin);
					}
					if (toupper(cfrm2) == 'Y')
					{
						fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
							addFUsage.date.d, addFUsage.date.m, addFUsage.date.y,
							timeSlots[i], addFUsage.userID, addFUsage.facilityID, addFUsage.usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}
					break;
				case'3':
					slctUserID(&chgUserID);
					i = strtol(addFUsage.time, NULL, 10) - 1;
					printf("\n===================\n");
					printf("Detail After Change\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", addFUsage.date.d,
						addFUsage.date.m, addFUsage.date.y);
					printf("Time        : %s\n", timeSlots[i]);
					printf("User ID     : %s\n", chgUserID);
					printf("Facility ID : %s\n", addFUsage.facilityID);
					printf("Usage Type  : %s\n", addFUsage.usageType);

					printf("\nConfirm to add this record? (Y=Yes/N=No) : ");
					rewind(stdin);
					scanf("%c", &cfrm2);
					rewind(stdin);
					while (toupper(cfrm2) != 'Y' && toupper(cfrm2) != 'N')
					{
						printf("Invalid Input !!!\n");
						printf("Re-enter Confirm to add this record? (Y=Yes/N=No) : ");
						rewind(stdin);
						scanf("%c", &cfrm2);
						rewind(stdin);
					}
					if (toupper(cfrm2) == 'Y')
					{
						fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
							addFUsage.date.d, addFUsage.date.m, addFUsage.date.y,
							timeSlots[i], chgUserID, addFUsage.facilityID, addFUsage.usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}
					break;
				case'4':
					slctFacilityID(&chgFacilityID);
					i = strtol(addFUsage.time, NULL, 10) - 1;
					printf("\n===================\n");
					printf("Detail After Change\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", addFUsage.date.d,
						addFUsage.date.m, addFUsage.date.y);
					printf("Time        : %s\n", timeSlots[i]);
					printf("User ID     : %s\n", addFUsage.userID);
					printf("Facility ID : %s\n", chgFacilityID);
					printf("Usage Type  : %s\n", addFUsage.usageType);

					printf("\nConfirm to add this record? (Y=Yes/N=No) : ");
					rewind(stdin);
					scanf("%c", &cfrm2);
					rewind(stdin);
					while (toupper(cfrm2) != 'Y' && toupper(cfrm2) != 'N')
					{
						printf("Invalid Input !!!\n");
						printf("Re-enter Confirm to add this record? (Y=Yes/N=No) : ");
						rewind(stdin);
						scanf("%c", &cfrm2);
						rewind(stdin);
					}
					if (toupper(cfrm2) == 'Y')
					{
						fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
							addFUsage.date.d, addFUsage.date.m, addFUsage.date.y,
							timeSlots[i], addFUsage.userID, chgFacilityID, addFUsage.usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}
					break;
				case'5':
					printf("Usage Type (walked-in / booked) : ");
					rewind(stdin);
					scanf("%[^\n]", chgUsageType);
					rewind(stdin);
					while (strcmp(chgUsageType, "walked-in") != 0 && strcmp(chgUsageType, "booked") != 0)
					{
						printf("Invalid Input !!!\n");
						printf("Re-enter Usage Type (walked-in / booked) : ");
						rewind(stdin);
						scanf("%[^\n]", chgUsageType);
						rewind(stdin);
					}
					i = strtol(addFUsage.time, NULL, 10) - 1;
					printf("\n===================\n");
					printf("Detail After Change\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", addFUsage.date.d,
						addFUsage.date.m, addFUsage.date.y);
					printf("Time        : %s\n", timeSlots[i]);
					printf("User ID     : %s\n", addFUsage.userID);
					printf("Facility ID : %s\n", addFUsage.facilityID);
					printf("Usage Type  : %s\n", chgUsageType);

					printf("\nConfirm to add this record? (Y=Yes/N=No) : ");
					rewind(stdin);
					scanf("%c", &cfrm2);
					rewind(stdin);
					while (toupper(cfrm2) != 'Y' && toupper(cfrm2) != 'N')
					{
						printf("Invalid Input !!!\n");
						printf("Re-enter Confirm to add this record? (Y=Yes/N=No) : ");
						rewind(stdin);
						scanf("%c", &cfrm2);
						rewind(stdin);
					}
					if (toupper(cfrm2) == 'Y')
					{
						fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
							addFUsage.date.d, addFUsage.date.m, addFUsage.date.y,
							timeSlots[i], addFUsage.userID, addFUsage.facilityID, chgUsageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}
					break;
				default:
					return;
				}
			}
		}
		printf("\nContinue to add record? (Y=YES / N=NO) : ");
		rewind(stdin);
		scanf("%c", &ctn);
		rewind(stdin);
		while (toupper(ctn) != 'Y' && toupper(ctn) != 'N')
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter continue to add record? (Y=YES / N=NO) : ");
			rewind(stdin);
			scanf("%c", &ctn);
			rewind(stdin);
		}
		system("cls");
	} while (toupper(ctn) == 'Y');
	fclose(f);
}

void fUsageSearchRecord()
{
	Date currentDate;
	getSystemDate(&currentDate);
	FacilityUsage searchFUsage;
	int day, month, year;
	char userID[30];
	char time[30];
	char facilityID[30];
	char usageType[30];
	char choice[10];
	int r, i;
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
	if (strcmp(choice, "0") == 0)
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
		} while (r != 3 || !validateDate(day, month, year) ||
			compareDate(day, month, year, fUsage->date.d, fUsage->date.m, fUsage->date.y) != 0);
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
		chkTime(time);
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
	FacilityUsage modifyFUsage;
	Date currentDate;
	getSystemDate(&currentDate);

	int selection;
	int choice;
	char cfrm;
	int r = 0;
	int count = 0;
	int i = 0;
	totalRecord = 0;

	FILE* f = fopen(fUsageFilePath, "r");
	if (f == NULL)
	{
		printf("There are currently no Facilities Usage Record in system !!!\n");
		system("pause");
		return 0;
	}

	printf("+=======================================+\n");
	printf("|     Modify Facility Usage Record      |\n");
	printf("+=======================================+\n");

	printf("No.\tDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
	printf("===\t====\t\t====\t\t=======\t\t===========\t==========\n");

	while (fscanf(f, "\n%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
		&fUsage[totalRecord].date.d, &fUsage[totalRecord].date.m, &fUsage[totalRecord].date.y,
		fUsage[totalRecord].time, fUsage[totalRecord].userID,
		fUsage[totalRecord].facilityID, fUsage[totalRecord].usageType) != EOF)
	{
		count++;
		printf("%-7d %02d/%02d/%-9d %-15s %-15s %-15s %s\n", count,
			fUsage[totalRecord].date.d, fUsage[totalRecord].date.m, fUsage[totalRecord].date.y,
			fUsage[totalRecord].time, fUsage[totalRecord].userID,
			fUsage[totalRecord].facilityID, fUsage[totalRecord].usageType);
	}
	
	modifyFUsage.date.d = fUsage[totalRecord].date.d;
	modifyFUsage.date.m = fUsage[totalRecord].date.m;
	modifyFUsage.date.y = fUsage[totalRecord].date.y;
	strcpy(modifyFUsage.userID, fUsage[totalRecord].userID);
	strcpy(modifyFUsage.facilityID, fUsage[totalRecord].facilityID);
	strcpy(modifyFUsage.time, fUsage[totalRecord].time);
	strcpy(modifyFUsage.usageType, fUsage[totalRecord].usageType);
	
	printf("\nEnter '0' to EXIT.\n");
	printf("Choose No. of record to modify (1 - %d) : ", count);
	rewind(stdin);
	scanf("%d", &selection);
	rewind(stdin);
	if (selection == 0)
	{
		return;
	}
	while (selection<1 || selection>count)
	{
		printf("Invalid Input !!!\n");
		printf("Please select between (1 - %d) : ", count);
		rewind(stdin);
		scanf("%d", &selection);
		rewind(stdin);
	}

	if (selection >= 1 || selection <= count)
	{
		printf("\nModify :\n");
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
			chkTime(modifyFUsage.time);
			i = strtol(modifyFUsage.time, NULL, 10) - 1;
			break;
		case 2:
			slctFacilityID(modifyFUsage.facilityID);
			break;
		default:
			break;
		}
	}

	printf("\n+============================+\n");
	printf("|    Record before Modify    |\n");
	printf("+============================+\n");
	printf("Date        : %02d/%02d/%d\n", fUsage[selection - 1].date.d,
		fUsage[selection - 1].date.m, fUsage[selection - 1].date.y);
	printf("Time        : %s\n", fUsage[selection - 1].time);
	printf("User ID     : %s\n", fUsage[selection - 1].userID);
	printf("Facility ID : %s\n", fUsage[selection - 1].facilityID);
	printf("Usage Type  : %s\n", fUsage[selection - 1].usageType);

	if (choice == 1 || choice == 3)
	{
		printf("\n+============================+\n");
		printf("|    Record After Modify     |\n");
		printf("+============================+\n");
		printf("Date        : %02d/%02d/%d\n", modifyFUsage.date.d,
			modifyFUsage.date.m, modifyFUsage.date.y);
		printf("Time        : %s\n", modifyFUsage.time);
		printf("User ID     : %s\n", modifyFUsage.userID);
		printf("Facility ID : %s\n", modifyFUsage.facilityID);
		printf("Usage Type  : %s\n", modifyFUsage.usageType);
	}
	if (choice == 2)
	{
		printf("\n+============================+\n");
		printf("|    Record After Modify     |\n");
		printf("+============================+\n");
		printf("Date        : %02d/%02d/%d\n", modifyFUsage.date.d,
			modifyFUsage.date.m, modifyFUsage.date.y);
		printf("Time        : %s\n", timeSlots[i]);
		printf("User ID     : %s\n", modifyFUsage.userID);
		printf("Facility ID : %s\n", modifyFUsage.facilityID);
		printf("Usage Type  : %s\n", modifyFUsage.usageType);
	}

	printf("Confirm to modify this Record ? (Y=Yes/N=No) : ");
	rewind(stdin);
	scanf("%c", &cfrm);
	rewind(stdin);
	while (toupper(cfrm) != 'Y' && toupper(cfrm) != 'N')
	{
		printf("Invalid Input !!!\nPlease try again.\n");
		printf("Confirm to modify Record ? (Y=Yes/N=No) : ");
		rewind(stdin);
		scanf("%c", &cfrm);
		rewind(stdin);
	}
	if (toupper(cfrm) == 'Y')
	{
		fUsage[totalRecord].date.d = modifyFUsage.date.d;
		fUsage[totalRecord].date.m = modifyFUsage.date.m;
		fUsage[totalRecord].date.y = modifyFUsage.date.y;
		strcpy(fUsage[totalRecord].userID, modifyFUsage.userID);
		strcpy(fUsage[totalRecord].facilityID, modifyFUsage.facilityID);
		strcpy(fUsage[totalRecord].time, modifyFUsage.time);
		strcpy(fUsage[totalRecord].usageType, modifyFUsage.usageType);
		fclose(f);

		FILE* f2 = fopen(fUsageFilePath, "w");
		if (choice == 2)
		{
			fprintf(f2, "%02d/%02d/%d|%s|%s|%s|%s\n",
				fUsage[totalRecord].date.d, fUsage[totalRecord].date.m, fUsage[totalRecord].date.y,
				timeSlots[i], fUsage[totalRecord].userID,
				fUsage[totalRecord].facilityID, fUsage[totalRecord].usageType);
		}
		if (choice == 1 || choice == 3)
		{
			fprintf(f2, "%02d/%02d/%d|%s|%s|%s|%s\n",
				fUsage[totalRecord].date.d, fUsage[totalRecord].date.m, fUsage[totalRecord].date.y,
				fUsage[totalRecord].time, fUsage[totalRecord].userID,
				fUsage[totalRecord].facilityID, fUsage[totalRecord].usageType);
		}
		fclose(f2);
	}

	
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

 int chkTime(char*time)
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

	 printf("+====================================================+\n"
		 "|       Facility Type       |       Facility ID      |\n"
		 "+====================================================+\n");
	 for (int i = 0; i < fDataCount; i++)
	 {
		 printf("%-20s%25s\n", fData[i].name, fData[i].id);
	 }
	 printf("+====================================================+\n");

	 printf("Enter Facility ID : ");
	 rewind(stdin);
	 scanf("%[^\n]", facilityID);
	 rewind(stdin);
	 fID = getFacilityID(facilityID);
	 while (fID == NULL)
	 {
		 printf("This Facility ID does not EXIST !!!\nPlease try again.\n");
		 printf("Enter Facility ID : ");
		 rewind(stdin);
		 scanf("%[^\n]", facilityID);
		 rewind(stdin);
		 fID = getFacilityID(facilityID);
	 }
 }

 Facility* getFacilityID(char* id)
 {
	 if (fDataCount == 0)
	 {
		 return NULL;
	 }
	 for (int i = 0; i < fDataCount; i++)
	 {
		 if (strcmp(fData[i].id, id) == 0)
		 {
			 return &fData[i];
		 }
	 }
	 return NULL;
 }

 void slctUserID(char* userID)
 {
	 userData *uID;
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

	 printf("Enter User ID : ");
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
	// code to get timeslot in string from booking.txt
	/*int bDataCount = readBookingDataIntoStructArray(&bData[0], 100);
	int tsIDX;
	if ((tsIDX = getTimeslotBooked(&bData[0].timeSlotsBooked[0])) != -1)
	{
		printf("%s\n", timeSlots[tsIDX]);
		system("pause");
	}*/
	system("pause");
 }

 /*void chkAvailableAdd(Date* date, int* time, char* facilityID)
 {
	 BookingData bData[100];
	 int totalReocrd = fUsageRecord();
	 FILE* f = fopen(bookingFilePath, "r");
	 
	 for (int i = 0; i < totalReocrd; i++)
	 {
		 while (fscanf(f, "%[^,],%d/%d/%d,%d:%d:%d,%d/%d/%d,%d,%d,%d,%d,%d,%d,%[^,],%[^,],%[^\n]\n",
			 bData[i].bookingID,
			 &bData[i].currentDate.d, &bData[i].currentDate.m, &bData[i].currentDate.y,
			 &bData[i].currentTime.h, &bData[i].currentTime.m, &bData[i].currentTime.s,
			 &bData[i].bookingDate.d, &bData[i].bookingDate.m, &bData[i].bookingDate.y,
			 &bData[i].timeSlotsBooked[0], &bData[i].timeSlotsBooked[1], &bData[i].timeSlotsBooked[2],
			 &bData[i].timeSlotsBooked[3], &bData[i].timeSlotsBooked[4], &bData[i].timeSlotsBooked[5],
			 bData[i].usrID, bData[i].staffID, bData[i].facilityID) != EOF)
		 {
			 if (date->d == bData[i].bookingDate.d && date->m == bData[i].bookingDate.m &&
				 date->y == bData[i].bookingDate.y && time == bData[i].timeSlotsBooked)
			 {
				 printf("This Facility ID on this DATE and TIME has been TAKEN !!!\n");
			 }
		 }
	 }
	 
	 fclose(f);
 }*/

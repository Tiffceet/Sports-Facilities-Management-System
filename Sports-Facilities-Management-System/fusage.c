#include "fusage.h"
#include "stdcxx.h"
#include "booking.h"
#include "facility.h"
#include "staff.h"
#include "userinfo.h"

char timeSlots[6][15] = { "7am - 9am ", "9am - 11am", "1pm - 3pm ", "3pm - 5pm ", "5pm - 7pm ", "7pm - 9pm " };

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

int fUsageRecord()
{
	FILE* f = fopen("facilityusage.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityusage.txt cannot open\n");
		system("pause");
		return 0;
	}
	int count = 0;

	while (fscanf(f, "\n%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
		&fUsage[count].date.d, &fUsage[count].date.m, &fUsage[count].date.y,
		fUsage[count].time, fUsage[count].userID, fUsage[count].facilityID, fUsage[count].usageType) != EOF)
	{
		count++;
	}

	fclose(f);
	return count;
}

void fUsageAddRecord()
{
	Date chgDate;
	FacilityUsage addFUsage;
	
	char ctn, cfrm, ctnChg;
	char choice, selection[10], cfrm2;
	char chgTime[30], chgUserID[6], chgFacilityID[6], chgUsageType[20];
	int i;
	
	Date currentDate;
	getSystemDate(&currentDate);
	
	FILE* f = fopen("facilityusage.txt", "a");
	if (f == NULL)
	{
		printf("Cannot open facilityusage.txt !!!\n");
		system("pause");
		return 0;
	}
	
	printf("+====================================+\n");
	printf("|     Add Facility Usage Record      |\n");
	printf("+====================================+\n");
	do
	{
		date(&addFUsage.date);
		
		chkTime(addFUsage.time);
		i = strtol(addFUsage.time, NULL, 10) - 1;
	
		slctFacilityID(addFUsage.facilityID);
		//chkAvailableAdd(&addFUsage.date, &addFUsage.time, addFUsage.facilityID);
		getUserID(addFUsage.userID);

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
					chkTime(addFUsage.time);
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
					getUserID(chgUserID);
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
					slctFacilityID(chgFacilityID);
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

	int totalRecord;
	totalRecord = fUsageRecord();
	char ctn;
	int day, month, year;
	char userID[30];
	char time[30];
	char facilityID[30];
	char usageType[30];
	char choice[10];
	int r, i;

	FILE* f = fopen("facilityusage.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityusage.txt cannot open\n");
		system("pause");
		return 0;
	}

	printf("+=======================================+\n");
	printf("|     Search Facility Usage Record      |\n");
	printf("+=======================================+\n");
	do {
		int dateErr = 0;

		printf("Search By :\n");
		printf("+=====================+\n");
		printf("| 1. Date             |\n");
		printf("| 2. Time             |\n");
		printf("| 3. User ID          |\n");
		printf("| 4. Facility ID      |\n");
		printf("| 5. Usage Type       |\n");
		printf("+=====================+\n");
		printf("Enter detail to search (1-5) : ");
		getUserMenuChoice(choice, 9, "Invalid Input !!!\nEnter detail to search (1-5) : ");
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
				compareDate(day, month, year, currentDate.d, currentDate.m, currentDate.y) != 1);
			err = 0;
			int count = 0;
			printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
			printf("====\t\t====\t\t=======\t\t===========\t==========\n");
			for (i = 0; i < totalRecord; i++)
			{
				if (fUsage[i].date.d == day && fUsage[i].date.m == month && fUsage[i].date.y == year)
				{
					printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", fUsage[i].date.d, fUsage[i].date.m,
						fUsage[i].date.y, fUsage[i].time, fUsage[i].userID,
						fUsage[i].facilityID, fUsage[i].usageType);
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
			count = 0;
			printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
			printf("====\t\t====\t\t=======\t\t===========\t==========\n");
			for (i = 0; i < totalRecord; i++)
			{
				if (strcmp(fUsage[i].time, timeSlots[a]) == 0)
				{
					printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", fUsage[i].date.d, fUsage[i].date.m,
						fUsage[i].date.y, fUsage[i].time, fUsage[i].userID,
						fUsage[i].facilityID, fUsage[i].usageType);
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
			printf("Enter User ID : ");
			rewind(stdin);
			scanf("%[^\n]", userID);
			rewind(stdin);
			while (strncmp(userID, "U", 1) != 0 || strlen(userID) != 4 ||
				!isdigit(userID[1]) || !isdigit(userID[2]) || !isdigit(userID[3]))
			{
				printf("Invalid Input !!!\n<!* Example : U001 *!>\n");
				printf("Enter User ID : ");
				rewind(stdin);
				scanf("%[^\n]", userID);
				rewind(stdin);
			}
			i = 0;
			if (strcmp(fUsage[i].userID, userID) != 0)
			{
				printf("This User ID does not EXISTS !!!\n");
			}
			for (i = 0; i < totalRecord; i++)
			{
				if (strcmp(fUsage[i].userID, userID) == 0)
				{
					printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
					printf("====\t\t====\t\t=======\t\t===========\t==========\n");
					printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", fUsage[i].date.d, fUsage[i].date.m,
						fUsage[i].date.y, fUsage[i].time, fUsage[i].userID,
						fUsage[i].facilityID, fUsage[i].usageType);
				}
			}
			break;
		case'4':
			slctFacilityID(facilityID);
			count = 0;
			printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
			printf("====\t\t====\t\t=======\t\t===========\t==========\n");
			for (i = 0; i < totalRecord; i++)
			{
				if (strcmp(fUsage[i].facilityID, facilityID) == 0)
				{
					printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", fUsage[i].date.d, fUsage[i].date.m,
						fUsage[i].date.y, fUsage[i].time, fUsage[i].userID,
						fUsage[i].facilityID, fUsage[i].usageType);
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
			count = 0;
			printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
			printf("====\t\t====\t\t=======\t\t===========\t==========\n");
			for (i = 0; i < totalRecord; i++)
			{
				if (strcmp(fUsage[i].usageType, usageType) == 0)
				{
					printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", fUsage[i].date.d, fUsage[i].date.m,
						fUsage[i].date.y, fUsage[i].time, fUsage[i].userID,
						fUsage[i].facilityID, fUsage[i].usageType);
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
		printf("\nContinue to search other record ? (Y=Yes/N=No) : ");
		rewind(stdin);
		scanf("%c", &ctn);
		rewind(stdin);
		while (toupper(ctn) != 'Y' && toupper(ctn) != 'N')
		{
			printf("Invalid Input !!!\nPlease enter between (Y/N).\n");
			printf("Continue to search other record ? (Y=Yes/N=No) : ");
			rewind(stdin);
			scanf("%c", &ctn);
			rewind(stdin);
		}
	} while (toupper(ctn) == 'Y');
	fclose(f);
	system("pause");
}

void fUsageModify()
{
	FacilityUsage modifyUsage;
	Date currentDate;
	getSystemDate(&currentDate);

	int totalRecord = fUsageRecord();
	char uID[6];
	char selection[10];
	char cfrm;
	int aftD, aftM, aftY;
	char aftTime[30], aftFacilityID[20];
	int dateErr = 0, r;

	FILE* f = fopen("facilityusage.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityusage.txt cannot open\n");
		system("pause");
		return 0;
	}
	printf("+=======================================+\n");
	printf("|     Modify Facility Usage Record      |\n");
	printf("+=======================================+\n");

	printf("Modify by enter User ID : ");
	rewind(stdin);
	scanf("%[^\n]", uID);
	rewind(stdin);
	while (strncmp(uID, "U", 1) != 0 || strlen(uID) != 4 ||
		!isdigit(uID[1]) || !isdigit(uID[2]) || !isdigit(uID[3]))
	{
		printf("Invalid Input !!!\n<!* Example : U001 *!>\n");
		printf("Enter User ID : ");
		rewind(stdin);
		scanf("%[^\n]", uID);
		rewind(stdin);
	}
	for (int i = 0; i < totalRecord; i++)
	{
		while (fscanf(f, "\n%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&fUsage[i].date.d, &fUsage[i].date.m, &fUsage[i].date.y,
			fUsage[i].time, fUsage[i].userID, fUsage[i].facilityID, fUsage[i].usageType) != EOF)
		{
			if (strcmp(uID, fUsage[i].userID) == 0)
			{
				printf("\nRecord Before Modify\n");
				printf("====================\n");
				printf("Date        : %02d/%02d/%d\n", fUsage[i].date.d,
					fUsage[i].date.m, fUsage[i].date.y);
				printf("Time        : %s\n", fUsage[i].time);
				printf("User ID     : %s\n", fUsage[i].userID);
				printf("Facility ID : %s\n", fUsage[i].facilityID);
				printf("Usage Type  : %s\n", fUsage[i].usageType);

				printf("\n+=====================================+\n");
				printf("|          Details to Modify          |\n");
				printf("+=====================================+\n");
				printf("| 1. Date                             |\n");
				printf("| 2. Time                             |\n");
				printf("| 3. FacilityID                       |\n");
				printf("+=====================================+\n");
				printf("Enter Details to Modify (1-3) : ");
				getUserMenuChoice(selection, 9, "Invalid Input !!!\nEnter detail to modify (1-3) : ");
				while (selection[0] < '1' || selection[0] > '3')
				{
					printf("Invalid Input !!!\n");
					printf("Enter Details to modify (1-3): ");
					getUserMenuChoice(selection, 9, "Invalid Input !!!\nEnter Details to modify (1-3): ");
				}

				switch (selection[0])
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
						r = scanf("%d/%d/%d", &aftD, &aftM, &aftY);
						rewind(stdin);
					} while (r != 3 || !validateDate(aftD, aftM, aftY) ||
						compareDate(aftD, aftM, aftY, currentDate.d, currentDate.m, currentDate.y) != 1);
					err = 0;
					printf("\nRecord After Modify\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", aftD, aftM, aftY);
					printf("Time        : %s\n", fUsage[i].time);
					printf("User ID     : %s\n", fUsage[i].userID);
					printf("Facility ID : %s\n", fUsage[i].facilityID);
					printf("Usage Type  : %s\n", fUsage[i].usageType);
					break;

				case'2':
					chkTime(aftTime);
					int b = strtol(aftTime, NULL, 10) - 1;
					printf("\nRecord After Modify\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", fUsage[i].date.d,
						fUsage[i].date.m, fUsage[i].date.y);
					printf("Time        : %s\n", timeSlots[b]);
					printf("User ID     : %s\n", fUsage[i].userID);
					printf("Facility ID : %s\n", fUsage[i].facilityID);
					printf("Usage Type  : %s\n", fUsage[i].usageType);
					break;

				case'3':
					slctFacilityID(aftFacilityID);
					printf("\nRecord After Modify\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", fUsage[i].date.d,
						fUsage[i].date.m, fUsage[i].date.y);
					printf("Time        : %s\n", fUsage[i].time);
					printf("User ID     : %s\n", fUsage[i].userID);
					printf("Facility ID : %s\n", aftFacilityID);
					printf("Usage Type  : %s\n", fUsage[i].usageType);
					break;

				default:
					return;
				}
			}
		}
	}
	fclose(f);
	system("pause");
}

void fUsageDelete()
{

}

void fUsageDisplay()
{
	FacilityUsage displayUsage;

	int countRcd = 0;
	FILE* f = fopen("facilityusage.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityusage.txt cannot open\n");
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
		"Modify Facilities Usage Record", "Delete Facilities Usage Record",
		"Display all Facilities Usage Record","Return to console" };
	int choice = globalMainMenu("Facilities Usage Module", 6, choiceText);
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
		fUsageDelete();
		break;
	case 5:
		fUsageDisplay();
		break;
	case 6:
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
	Date currentDate;
	getSystemDate(&currentDate);
	int r;
	int dateErr = 0; 
	do 
	{
		if (dateErr)
		{
			printf("Invalid Date, try again.\nDo note that booking on today is not allowed.\n");
		}
		dateErr = 1;
		printf("Enter Date < DD/MM/YYYY > : ");
		rewind(stdin);
		r = scanf("%d/%d/%d", &date->d, &date->m, &date->y);
		rewind(stdin);
	} while (r != 3 || !validateDate(date->d, date->m,date->y) ||
		compareDate(date->d, date->m,date->y, currentDate.d, currentDate.m, currentDate.y) != 1);
	err = 0;
	return 1;
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

 void slctFacilityID(char *facilityID)
 {
	 printf("+====================================================+\n");
	 printf("|       Facility Type       |       Facility ID      |\n"
			"+====================================================+\n"
			"|       Badminton Court     |          F001          |\n"
			"|       Soccer Field        |          F002          |\n"
			"|       Squash Court        |          F003          |\n"
			"|       Ping Pong Table     |          F004          |\n"
			"|       Facility 5          |          F005          |\n"
			"+====================================================+\n");
	 printf("Enter Facility ID : ");
	 rewind(stdin);
	 scanf("%[^\n]", facilityID);
	 rewind(stdin);
	 while (strcmp(facilityID, "F001") != 0 && strcmp(facilityID, "F002") != 0 && strcmp(facilityID, "F003") != 0 &&
		 strcmp(facilityID, "F004") != 0 && strcmp(facilityID, "F005") != 0)
	 {
		 printf("Invalid Input !!!\nPlease select between ( F001 - F005 )\n");
		 printf("Enter Facility ID : ");
		 rewind(stdin);
		 scanf("%[^\n]", facilityID);
		 rewind(stdin);
	 }
 }

 void getUserID(char* userID)
 {
	 int totalReocrd = fUsageRecord();
	 printf("\n");
	 FILE* f2 = fopen(UserInfoFilePath, "rb");
	 if (!chkFileExist(f2))
	 {
		 printf("Cannot open UserInfoFilePath !!!\n");
		 system("pause");
		 return 0;
	 }
	 printf("Enter User ID : ");
	 rewind(stdin);
	 scanf("%[^\n]", userID);
	 rewind(stdin);
	 while (strncmp(userID, "U", 1) != 0 || strlen(userID) != 4 ||
		 !isdigit(userID[1]) || !isdigit(userID[2]) || !isdigit(userID[3]))
	 {
		 printf("Invalid Input !!!\n<!* Example : U001 *!>\n");
		 printf("Enter User ID : ");
		 rewind(stdin);
		 scanf("%[^\n]", userID);
		 rewind(stdin);
	 }
	 for (int i = 0; i < totalReocrd; i++)
	 {
		 while (fread(&uData[i], sizeof(userData), 1, f2) != 0)
		 {
			 while (strcmp(userID, uData[i].id) == 0)
			 {
				 printf("This User ID has been TAKEN !!!\nPlease try again.\n");
				 printf("Enter User ID : ");
				 rewind(stdin);
				 scanf("%[^\n]", userID);
				 rewind(stdin);
				 while (strncmp(userID, "U", 1) != 0 || strlen(userID) != 4 ||
					 !isdigit(userID[1]) || !isdigit(userID[2]) || !isdigit(userID[3]))
				 {
					 printf("Invalid Input !!!\n<!* Example : U001 *!>\n");
					 printf("Enter User ID : ");
					 rewind(stdin);
					 scanf("%[^\n]", userID);
					 rewind(stdin);
				 }
			 }
		 }
	 }
	 fclose(f2);
 }
 /*void chkAvailableAdd(Date* date, int* time, char* facilityID)
 {
	 BookingData bData[100];
	 int totalReocrd = fUsageRecord();
	 FILE* f = fopen(bookingFilePath, "r");
	 if (!chkFileExist(f))
	 {
		 printf("Cannot open bookingFilePath !!!\n");
		 system("pause");
		 return 0;
	 }
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

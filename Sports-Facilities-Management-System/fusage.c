#include "fusage.h"
#include "stdcxx.h"

FacilityUsage fUsage[100];
int count;

void fusagemain()
{
	staffLogin();
	fUsageRecord();
	while (fUsageMenu())
	{
		continue;
	}
}

void staffLogin()
{
	system("cls");
	StaffValidation stfValid;
	printf("Staff Login\n");
	printf("===========\n");
	printf("Enter Staff ID : ");
	rewind(stdin);
	scanf("%s", stfValid.staffID);
	printf("Enter Password : ");
	rewind(stdin);
	scanf("%s", stfValid.password);
	rewind(stdin);
	/*while (strcmp(stfValid.staffID,) != 0 && strcmp(stfValid.password,) != 0)
	{
		printf("\nWrong ID or Password\n");
		printf("Enter Staff ID : ");
		rewind(stdin);
		scanf("%s", stfValid.staffID);
		printf("Enter Password : ");
		rewind(stdin);
		scanf("%s", stfValid.password);
	}*/
	system("cls");
}

void fUsageRecord()
{
	FILE* f = fopen("facilityusage.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityusage.txt cannot open\n");
		system("pause");
		return 0;
	}
	for (int i = 0; i < 100; i++)
	{
		while (fscanf(f, "\n%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&fUsage[i].date.d, &fUsage[i].date.m, &fUsage[i].date.y,
			fUsage[i].time, fUsage[i].userID, fUsage[i].facilityID, fUsage[i].usageType) != EOF)
		{
			count++;
		}
	}
	fclose(f);
}

void fUsageAddRecord()
{
	char ctn, cfrm, ctnChg;
	int chgD, chgM, chgY;
	char choice, selection[10], cfrm2;
	char chgTime[30], chgUserID[6], chgFacilityID[6], chgUsageType[20];
	int i;
	Date currentDate;
	getSystemDate(&currentDate);
	char TIMESLOTS[6][15] = { "7am - 9am ", "9am - 11am", "1pm - 3pm ", "3pm - 5pm ", "5pm - 7pm ", "7pm - 9pm " };

	FILE* f = fopen("facilityusage.txt", "a");
	if (f == NULL)
	{
		printf("File of facilityusage.txt cannot open\n");
		system("pause");
		return 0;
	}
	
	printf("==========================\n");
	printf("Add Facility Status Record\n");
	printf("==========================\n");
	do
	{
		printf("Enter Date < DD/MM/YYYY >                                   : ");
		int r = scanf("%d/%d/%d", &fUsage->date.d, &fUsage->date.m, &fUsage->date.y);
		while (r != 3 || !validateDate(fUsage->date.d, fUsage->date.m, fUsage->date.y) ||
			compareDate(fUsage->date.d, fUsage->date.m, fUsage->date.y, currentDate.d, currentDate.m, currentDate.y)
			!= 1)
		{
			printf("Invalid Date, try again.\nDo note that booking on today is not allowed.\n");
			printf("Enter Date < DD/MM/YYYY >                                   : ");
			r = scanf("%d/%d/%d", &fUsage->date.d, &fUsage->date.m, &fUsage->date.y);
		}
		printf("Timeslots: \n");
		for (int a = 0; a < 6; a++)
		{
			printf("\t%d. %s \n", a + 1, TIMESLOTS[a]);
		}
		printf("Please select timeslot from (1-6): ");
		getUserMenuChoice(fUsage->time, 9, "Please, pick a timeslot(1-6): ");
		while (fUsage->time[0] < '1' || fUsage->time[0] > '6')
		{
			printf("Invalid Input !!!\n");
			printf("Please, pick a timeslot (1-6): ");
			getUserMenuChoice(fUsage->time, 9, "Please, pick a timeslot(1-6): ");
		}
		i = strtol(fUsage->time, NULL, 10) - 1;
	
		printf("Enter User ID (5 characters) < Uxxxx >                      : ");
		rewind(stdin);
		scanf("%[^\n]", fUsage->userID);
		while (strncmp(fUsage->userID, "U", 1) != 0 || strlen(fUsage->userID) != 5)
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter User ID (5 characters) < Uxxxx >                   : ");
			rewind(stdin);
			scanf("%[^\n]", fUsage->userID);
			rewind(stdin);
		}
		printf("Enter Facility ID (5 characters) < Fxxxx >                  : ");
		rewind(stdin);
		scanf("%[^\n]", fUsage->facilityID);
		while (strncmp(fUsage->facilityID, "F", 1) || strlen(fUsage->facilityID) != 5)
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter Facility ID (5 characters) < Fxxxx >               : ");
			rewind(stdin);
			scanf("%[^\n]", fUsage->facilityID);
			rewind(stdin);
		}
		printf("Enter Usage Type (walked-in / booked)                       : ");
		rewind(stdin);
		scanf("%[^\n]", fUsage->usageType);
		while (strcmp(fUsage->usageType, "walked-in") != 0 && strcmp(fUsage->usageType, "booked") != 0)
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter Usage Type (walked-in / booked)                    : ");
			rewind(stdin);
			scanf("%[^\n]", fUsage->usageType);
			rewind(stdin);
		}

		system("cls");
		printf("========================\n");
		printf("Facilities details added\n");
		printf("========================\n");
		printf("Date        : %02d/%02d/%d\n", fUsage->date.d, fUsage->date.m, fUsage->date.y);
		printf("Time        : %s\n", TIMESLOTS[i]);
		printf("User ID     : %s\n", fUsage->userID);
		printf("Facility ID : %s\n", fUsage->facilityID);
		printf("Usage Type  : %s\n", fUsage->usageType);

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
				fUsage->date.d, fUsage->date.m, fUsage->date.y, TIMESLOTS[i],
				fUsage->userID, fUsage->facilityID, fUsage->usageType);
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
				getUserMenuChoice(selection, 9, "Enter Details to change (1-5): ");
				while (selection[0] < '1' || selection[0] > '5')
				{
					printf("Invalid Input !!!\n");
					printf("Enter Details to Change (1-5): ");
					getUserMenuChoice(selection, 9, "Enter Details to change (1-5): ");
				}
				switch (selection[0])
				{
				case'1':
					printf("Enter Date < DD/MM/YYYY > : ");
					int r = scanf("%d/%d/%d", &chgD, &chgM, &chgY);
					while (r != 3 || !validateDate(chgD, chgM, chgY) ||
						compareDate(chgD, chgM, chgY, currentDate.d, currentDate.m, currentDate.y)
						!= 1)
					{
						printf("Invalid Date, try again.\nDo note that booking on today is not allowed.\n");
						printf("Enter Date < DD/MM/YYYY > : ");
						r = scanf("%d/%d/%d", &chgD, &chgM, &chgY);
					}
					printf("\n===================\n");
					printf("Detail After Change\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", chgD, chgM, chgY);
					printf("Time        : %s\n", TIMESLOTS[i]);
					printf("User ID     : %s\n", fUsage->userID);
					printf("Facility ID : %s\n", fUsage->facilityID);
					printf("Usage Type  : %s\n", fUsage->usageType);

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
							chgD, chgM, chgY, TIMESLOTS[i], fUsage->userID,
							fUsage->facilityID, fUsage->usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}
					break;
				case'2':
					printf("Timeslots: \n");
					for (int a = 0; a < 6; a++)
					{
						printf("\t%d. %s \n", a + 1, TIMESLOTS[a]);
					}
					printf("Please select timeslot from (1-6): ");
					getUserMenuChoice(chgTime, 9, "Please, pick a timeslot(1-6): ");
					while (chgTime[0] < '1' || chgTime[0] > '6')
					{
						printf("Invalid Input !!!\n");
						printf("Please, pick a timeslot (1-6): ");
						getUserMenuChoice(chgTime, 9, "Please, pick a timeslot(1-6): ");
					}
					int b = strtol(chgTime, NULL, 10) - 1;
					printf("\n===================\n");
					printf("Detail After Change\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", fUsage->date.d,
						fUsage->date.m, fUsage->date.y);
					printf("Time        : %s\n", TIMESLOTS[b]);
					printf("User ID     : %s\n", fUsage->userID);
					printf("Facility ID : %s\n", fUsage->facilityID);
					printf("Usage Type  : %s\n", fUsage->usageType);

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
							fUsage->date.d, fUsage->date.m, fUsage->date.y,
							TIMESLOTS[b], fUsage->userID, fUsage->facilityID, fUsage->usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}
					break;
				case'3':
					printf("Enter User ID (5 characters) < Uxxxx > : ");
					rewind(stdin);
					scanf("%[^\n]", chgUserID);
					rewind(stdin);
					while (strncmp(chgUserID, "U", 1) != 0 || strlen(chgUserID) != 5)
					{
						printf("Invalid Input !!!\n");
						printf("Re-enter User ID (5 characters) < Uxxxx > : ");
						rewind(stdin);
						scanf("%[^\n]", chgUserID);
						rewind(stdin);
					}
					printf("\n===================\n");
					printf("Detail After Change\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", fUsage->date.d,
						fUsage->date.m, fUsage->date.y);
					printf("Time        : %s\n", TIMESLOTS[i]);
					printf("User ID     : %s\n", chgUserID);
					printf("Facility ID : %s\n", fUsage->facilityID);
					printf("Usage Type  : %s\n", fUsage->usageType);

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
							fUsage->date.d, fUsage->date.m, fUsage->date.y,
							TIMESLOTS[i], chgUserID, fUsage->facilityID, fUsage->usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}

					break;
				case'4':
					printf("Enter Facility ID (5 characters) < Fxxxx >                  : ");
					rewind(stdin);
					scanf("%[^\n]", chgFacilityID);
					rewind(stdin);
					while (strncmp(chgFacilityID, "F", 1) || strlen(chgFacilityID) != 5)
					{
						printf("Invalid Input !!!\n");
						printf("Re-enter Facility ID (5 characters) < Fxxxx >               : ");
						rewind(stdin);
						scanf("%[^\n]", chgFacilityID);
						rewind(stdin);
					}
					printf("\n===================\n");
					printf("Detail After Change\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", fUsage->date.d,
						fUsage->date.m, fUsage->date.y);
					printf("Time        : %s\n", TIMESLOTS[i]);
					printf("User ID     : %s\n", fUsage->userID);
					printf("Facility ID : %s\n", chgFacilityID);
					printf("Usage Type  : %s\n", fUsage->usageType);

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
							fUsage->date.d, fUsage->date.m, fUsage->date.y,
							TIMESLOTS[i], fUsage->userID, chgFacilityID, fUsage->usageType);
						printf("<* Added successfully to Facility Usage Record *>\n");
					}

					break;
				case'5':
					printf("Usage Type (walked-in / booked) : ");
					rewind(stdin);
					scanf("%[^\n]", chgUsageType);
					rewind(stdin);
					while (strcmp(fUsage->usageType, "walked-in") != 0 && strcmp(fUsage->usageType, "booked") != 0)
					{
						printf("Invalid Input !!!\n");
						printf("Re-enter Usage Type (walked-in / booked) : ");
						rewind(stdin);
						scanf("%[^\n]", chgUsageType);
						rewind(stdin);
					}
					printf("\n===================\n");
					printf("Detail After Change\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", fUsage->date.d,
						fUsage->date.m, fUsage->date.y);
					printf("Time        : %s\n", TIMESLOTS[i]);
					printf("User ID     : %s\n", fUsage->userID);
					printf("Facility ID : %s\n", fUsage->facilityID);
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
							fUsage->date.d, fUsage->date.m, fUsage->date.y,
							TIMESLOTS[i], fUsage->userID, fUsage->facilityID, chgUsageType);
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
	char TIMESLOTS[6][15] = { "7am - 9am ", "9am - 11am", "1pm - 3pm ", "3pm - 5pm ", "5pm - 7pm ", "7pm - 9pm " };
	int day, month, year;
	char userID[30];
	char time[30];
	char facilityID[30];
	char usageType[30];
	char choice[10];
	int b;

	FILE* f = fopen("facilityusage.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityusage.txt cannot open\n");
		system("pause");
		return 0;
	}

	printf("=============================\n");
	printf("Search Facility Status Record\n");
	printf("=============================\n");
	printf("Search By :\n");
	printf("+---------------------+\n");
	printf("| 1. Date             |\n");
	printf("| 2. Time             |\n");
	printf("| 3. User ID          |\n");
	printf("| 4. Facility ID      |\n");
	printf("| 5. Usage Type       |\n");
	printf("+---------------------+\n");
	printf("Enter detail to search (1-5) : ");
	getUserMenuChoice(choice, 9, "Enter detail to search (1-5) : ");
	while (choice[0] < '1' || choice[0] > '5')
	{
		printf("Invalid Input !!!\n");
		printf("Enter Details to Change (1-5): ");
		getUserMenuChoice(choice, 9, "Enter Details to change (1-5): ");
	}
	switch (choice[0])
	{
	case'1':
		printf("Search by Date < DD/MM/YYYY > : ");
		int r = scanf("%d/%d/%d", &day, &month, &year);
		while (r != 3 || !validateDate(day, month, year) ||
			compareDate(day, month, year, currentDate.d, currentDate.m, currentDate.y) != 1)
		{
			printf("Invalid Date, try again.\nDo note that booking on today is not allowed.\n");
			printf("Search by Date < DD/MM/YYYY > : ");
			r = scanf("%d/%d/%d", &day, &month, &year);
		}
		break;
	case'2':
		printf("Timeslots: \n");
		for (int a = 0; a < 6; a++)
		{
			printf("\t%d. %s \n", a + 1, TIMESLOTS[a]);
		}
		printf("Please select timeslot from (1-6) : ");
		getUserMenuChoice(time, 9, "Please, pick a timeslot(1-6) : ");
		while (time[0] < '1' || time[0] > '6')
		{
			printf("Invalid Input !!!\n");
			printf("Please, pick a timeslot (1-6): ");
			getUserMenuChoice(time, 9, "Please, pick a timeslot(1-6): ");
		}
		b = strtol(time, NULL, 10) - 1;
		break;
	case'3':
		printf("Enter User ID (5 characters) < Uxxxx > : ");
		rewind(stdin);
		scanf("%[^\n]", userID);
		while (strncmp(userID, "U", 1) != 0 || strlen(userID) != 5)
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter User ID (5 characters) < Uxxxx > : ");
			rewind(stdin);
			scanf("%[^\n]", userID);
			rewind(stdin);
		}
		break;
	case'4':
		printf("Enter Facility ID (5 characters) < Fxxxx > : ");
		rewind(stdin);
		scanf("%[^\n]", facilityID);
		while (strncmp(facilityID, "F", 1) || strlen(facilityID) != 5)
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter Facility ID (5 characters) < Fxxxx > : ");
			rewind(stdin);
			scanf("%[^\n]", facilityID);
			rewind(stdin);
		}
		break;
	case'5':
		printf("Enter Usage Type (walked-in / booked) : ");
		rewind(stdin);
		scanf("%[^\n]", usageType);
		while (strcmp(usageType, "walked-in") != 0 && strcmp(usageType, "booked") != 0)
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter Usage Type (walked-in / booked) : ");
			rewind(stdin);
			scanf("%[^\n]", usageType);
			rewind(stdin);
		}
		break;
	}
	printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
	printf("====\t\t====\t\t=======\t\t===========\t==========\n");
	for (int i = 0; i < count; i++)
	{
		while (fscanf(f, "\n%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&fUsage[i].date.d, &fUsage[i].date.m, &fUsage[i].date.y,
			fUsage[i].time, fUsage[i].userID, fUsage[i].facilityID, fUsage[i].usageType) != EOF)
		{
			if (fUsage[i].date.d == day && fUsage[i].date.m == month && fUsage[i].date.y == year)
			{
				printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", fUsage[i].date.d, fUsage[i].date.m,
					fUsage[i].date.y, fUsage[i].time, fUsage[i].userID, fUsage[i].facilityID, fUsage[i].usageType);
			}
		}
	}
	fclose(f);
	system("pause");
}

void fUsageModify()
{
	char uID[5];
	char selection[30];
	int aftD, aftM, aftY;
	char aftTime[30], aftUserID[30], aftFacilityID[20], aftUsageType[20];

	FILE* f = fopen("facilityusage.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityusage.txt cannot open\n");
		system("pause");
		return 0;
	}
	printf("=============================\n");
	printf("Modify Facility status Record\n");
	printf("=============================\n");
	
	printf("Enter User Id to Modify : ");
	rewind(stdin);
	scanf("%[^\n]", uID);
	rewind(stdin);
	for (int i = 0; i < count; i++)
	{
		while (fscanf(f, "\n%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&fUsage[i].date.d, &fUsage[i].date.m, &fUsage[i].date.y,
			fUsage[i].time, fUsage[i].userID, fUsage[i].facilityID, fUsage[i].usageType) != EOF)
		{
			if (strcmp(fUsage[i].userID, uID) == 0)
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
				printf("| >> Date <<                          |\n");
				printf("| >> Time <<                          |\n");
				printf("| >> FacilityID <<                    |\n");
				printf("+=====================================+\n");
				printf("Enter Details to Modify : ");
				rewind(stdin);
				scanf("%[^\n]", selection);
				rewind(stdin);
				while (strcmp(selection, "Date") != 0 && strcmp(selection, "Time") != 0 &&
					strcmp(selection, "FacilityID") != 0)
				{
					printf("Invalid Input !!!\n");
					printf("Re-enter Details to Modify (Date/Time/FacilityID) : ");
					rewind(stdin);
					scanf("%[^\n]", selection);
					rewind(stdin);
				}
				if (strcmp(selection, "Date") == 0)
				{
					printf("Date : ");
					scanf("%d/%d/%d", &aftD, &aftM, &aftY);
					printf("\nRecord After Modify\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", aftD, aftM, aftY);
					printf("Time        : %s\n", fUsage[i].time);
					printf("User ID     : %s\n", fUsage[i].userID);
					printf("Facility ID : %s\n", fUsage[i].facilityID);
					printf("Usage Type  : %s\n", fUsage[i].usageType);
					fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
						aftD, aftM, aftY, fUsage->time, fUsage->userID,
						fUsage->facilityID, fUsage->usageType);
				}
				if (strcmp(selection, "Time") == 0)
				{
					printf("Time : ");
					rewind(stdin);
					scanf("%[^\n]", aftTime);
					printf("\nRecord After Modify\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", fUsage[i].date.d,
						fUsage[i].date.m, fUsage[i].date.y);
					printf("Time        : %s\n", aftTime);
					printf("User ID     : %s\n", fUsage[i].userID);
					printf("Facility ID : %s\n", fUsage[i].facilityID);
					printf("Usage Type  : %s\n", fUsage[i].usageType);
					fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
						fUsage->date.d, fUsage->date.m, fUsage->date.y,
						aftTime, fUsage->userID, fUsage->facilityID, fUsage->usageType);
				}
				if (strcmp(selection, "FacilityID") == 0)
				{
					printf("Facility ID : ");
					rewind(stdin);
					scanf("%[^\n]", aftFacilityID);
					printf("\nRecord After Modify\n");
					printf("===================\n");
					printf("Date        : %02d/%02d/%d\n", fUsage[i].date.d,
						fUsage[i].date.m, fUsage[i].date.y);
					printf("Time        : %s\n", fUsage[i].time);
					printf("User ID     : %s\n", fUsage[i].userID);
					printf("Facility ID : %s\n", aftFacilityID);
					printf("Usage Type  : %s\n", fUsage[i].usageType);
					fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
						fUsage->date.d, fUsage->date.m, fUsage->date.y,
						fUsage->time, fUsage->userID, aftFacilityID, fUsage->usageType);
				}
				
			}
		}
	}
	fclose(f);
	system("pause");
}

void fUsageDisplay()
{
	FILE* f = fopen("facilityusage.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityusage.txt cannot open\n");
		system("pause");
		return 0;
	}
	printf("======================\n");
	printf("Facility Usage Records\n");
	printf("======================\n\n");
	printf("Date\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
	printf("====\t\t====\t\t=======\t\t===========\t==========\n");

	while (fscanf(f, "%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n", &fUsage->date.d, &fUsage->date.m,
		&fUsage->date.y, fUsage->time, fUsage->userID, fUsage->facilityID, fUsage->usageType) != EOF)
	{
		printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", fUsage->date.d, fUsage->date.m,
			fUsage->date.y, fUsage->time, fUsage->userID, fUsage->facilityID, fUsage->usageType);
	}

	fclose(f);
	system("pause");
}

int fUsageMenu()
{
	/*printf("=====================\n");
	printf("Facility Usage Module\n");
	printf("=====================\n");
	printf("1. Add Record\n");
	printf("2. Search Record\n");
	printf("3. Modify Record\n");
	printf("4. Return to Menu\n");*/
		
	char choiceText[][100] = { "Add Facilities Usage","Search Facilities Usage Record","Modify Facilities Usage Detail","Display all Facilities Usage","Return to console" };
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
		return 0;
	default:
		return 1;
	}
	return 1;
}
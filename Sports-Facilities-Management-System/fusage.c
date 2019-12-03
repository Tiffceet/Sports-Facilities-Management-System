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
	FILE* f = fopen("facilityinfo.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityinfo.txt cannot open\n");
		system("pause");
		return 0;
	}

	/*printf("======================\n");
	printf("Facility Status Record\n");
	printf("======================\n");*/
	
	/*printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
	printf("====\t\t====\t\t=======\t\t===========\t==========\n");*/
	for (int i = 0; i < 100; i++)
	{
		while (fscanf(f, "\n%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&fUsage[i].date.d, &fUsage[i].date.m, &fUsage[i].date.y,
			fUsage[i].time, fUsage[i].userID, fUsage[i].facilityID, fUsage[i].usageType) != EOF)
		{
			/*printf("%02d/%02d/%-9d %-15s %-15s %-15s %s\n", fUsage[i].date.d, fUsage[i].date.m,
				fUsage[i].date.y, fUsage[i].time, fUsage[i].userID, fUsage[i].facilityID, fUsage[i].usageType);*/
			count++;
		}
	}
	fclose(f);
}

void fUsageAddRecord()
{
	FILE* f = fopen("facilityinfo.txt", "a");
	if (!chkFileExist(f))
	{
		printf("File of facilityinfo.txt cannot open\n");
		system("pause");
		return 0;
	}
	char ctn;

	printf("==========================\n");
	printf("Add Facility Status Record\n");
	printf("==========================\n");

	do
	{
		printf("Enter Date < DD/MM/YYYY >                                            : ");
		scanf("%d/%d/%d", &fUsage->date.d, &fUsage->date.m, &fUsage->date.y);
		printf("Enter Time < 7am-9am, 9am-11am, 1pm-3pm, 3pm-5pm, 5pm-7pm, 7pm-9pm > : ");
		rewind(stdin);
		scanf("%[^\n]", fUsage->time);
		printf("Enter User ID < 4 characters >                                       : ");
		rewind(stdin);
		scanf("%[^\n]", fUsage->userID);
		printf("Enter Facility ID < 5 characters >                                   : ");
		rewind(stdin);
		scanf("%[^\n]", fUsage->facilityID);
		printf("Enter Usage Type < walked-in / booked >                              : ");
		rewind(stdin);
		scanf("%[^\n]", fUsage->usageType);
		rewind(stdin);

		printf("\nContinue to add record? (Y=YES / N=NO) : ");
		rewind(stdin);
		scanf("%c", &ctn);
		while (toupper(ctn) != 'Y' && toupper(ctn) != 'N')
		{
			printf("Invalid Input !!!\n");
			printf("Re-enter continue to add record? (Y=YES / N=NO) : ");
			rewind(stdin);
			scanf("%c", &ctn);
			rewind(stdin);
		}
		fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
			fUsage->date.d, fUsage->date.m, fUsage->date.y,
			fUsage->time, fUsage->userID, fUsage->facilityID, fUsage->usageType);
	} while (toupper(ctn) == 'Y');
	fclose(f);
	system("pause");
}

void fUsageSearchRecord()
{
	int day, month, year;

	FILE* f = fopen("facilityinfo.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityinfo.txt cannot open\n");
		system("pause");
		return 0;
	}

	printf("=============================\n");
	printf("Search Facility Status Record\n");
	printf("=============================\n");

	printf("Search Facility Usage status by enter date : ");
	scanf("%d/%d/%d", &day, &month, &year);
	printf("\nDate\t\tTime\t\tUser ID\t\tFacility ID\tUsage Type\n");
	printf("====\t\t====\t\t=======\t\t===========\t==========\n");
	for (int i = 0; i < count; i++)
	{
		while (fscanf(f, "\n%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
			&fUsage[i].date.d, &fUsage[i].date.m, &fUsage[i].date.y,
			fUsage[i].time, fUsage[i].userID, fUsage[i].facilityID, fUsage[i].usageType) != EOF)
		{
			if (fUsage[i].date.d == day &&
				fUsage[i].date.m == month &&
				fUsage[i].date.y == year)
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

	FILE* f = fopen("facilityinfo.txt", "a");
	if (!chkFileExist(f))
	{
		printf("File of facilityinfo.txt cannot open\n");
		system("pause");
		return 0;
	}
	printf("=============================\n");
	printf("Modify Facility status Record\n");
	printf("=============================\n");
	
	printf("Enter User Id to Modify : ");
	rewind(stdin);
	scanf("%[^\n]", uID);
	while (strcmp(fUsage->userID, uID) != 0)
	{
		printf("Invalid Input !!!\n");
		printf("Re-enter User ID to Modify : ");
		rewind(stdin);
		scanf("%[^\n]", uID);
		rewind(stdin);
	}
	for (int i = 0; i < count; i++)
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

			printf("Enter Details to Modify (Date/Time/FacilityID/UsageType) : ");
			rewind(stdin);
			scanf("%[^\n]", selection);
			rewind(stdin);
			while (strcmp(selection, "Date") != 0 && strcmp(selection, "Time") != 0 &&
				strcmp(selection, "FacilityID") != 0 && strcmp(selection, "UsageType") != 0)
			{
				printf("Invalid Input !!!\n");
				printf("Re-enter :\n");
				printf("Enter Details to Modify (Date/Time/FacilityID/UsageType) : ");
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
			if (strcmp(selection, "UsageType") == 0)
			{
				printf("Usage Type : ");
				rewind(stdin);
				scanf("%[^\n]", aftUsageType);
				printf("\nRecord After Modify\n");
				printf("===================\n");
				printf("Date        : %02d/%02d/%d\n", fUsage[i].date.d,
					fUsage[i].date.m, fUsage[i].date.y);
				printf("Time        : %s\n", fUsage[i].time);
				printf("User ID     : %s\n", fUsage[i].userID);
				printf("Facility ID : %s\n", fUsage[i].facilityID);
				printf("Usage Type  : %s\n", aftUsageType);
				fprintf(f, "%02d/%02d/%d|%s|%s|%s|%s\n",
					fUsage->date.d, fUsage->date.m, fUsage->date.y,
					fUsage->time, fUsage->userID, fUsage->facilityID, aftUsageType);
			}
		}
	}
	fclose(f);
	system("pause");
}

void fUsageDisplay()
{
	FILE* f = fopen("facilityinfo.txt", "r");
	if (!chkFileExist(f))
	{
		printf("File of facilityinfo.txt cannot open\n");
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
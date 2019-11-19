#include "fusage.h"
#include "stdcxx.h"

typedef struct
{
	int day, month, year;
}Date;
Date currentDate;
typedef struct
{
	Date currentDate;
	char time[30];
	char userID[30], facilityID[20];
	char usageType[20];
}FacilityUsage;
FacilityUsage fUsage;

typedef struct
{
	char staffID[30], password[30];
}StaffValidation;
StaffValidation stfValid;

void main()
{
	staffLogin();
	fUsageMenu();
	system("pause");
}

void staffLogin()
{
	printf("Enter Staff ID : ");
	rewind(stdin);
	scanf("%s", stfValid.staffID);
	printf("Enter Password : ");
	rewind(stdin);
	scanf("%s", stfValid.password);
	//while (strcmp(stfValid.staffID,) != 0 && strcmp(stfValid.password,) != 0)
	//{
	//	printf("\nWrong ID or Password\n");
	//	printf("Enter Staff ID : ");
	//	rewind(stdin);
	//	scanf("%s", stfValid.staffID);
	//	printf("Enter Password : ");
	//	rewind(stdin);
	//	scanf("%s", stfValid.password);
	//}
	system("cls");
}

void fUsageRecord()
{
	FILE* f = fopen("facilityinfo.txt", "a");
	if (f == NULL)
	{
		printf("File of facilityinfo.txt cannot open\n");
		system("pasue");
		exit(-1);
	}
	do
	{
		printf("Today's Date(DD/MM/YYYY) : ");
		scanf("%d/%d/%d", &fUsage.currentDate.day, &fUsage.currentDate.month, &fUsage.currentDate.year);
		printf("Search Time : ");
		scanf("%s", &fUsage.time);
	}

	printf("Today's Date\t\tTime\t\tUser ID\t\tFacility ID\t\tUsage Type\n");
	printf("============\t\t====\t\t=======\t\t===========\t\t==========\n");


}

void fUsageAddRecord()
{
	FILE* f = fopen("facilityinfo.txt", "a");
	if (f == NULL)
	{
		printf("File of facilityinfo.txt cannot open\n");
		system("pasue");
		exit(-1);
	}


}

void fUsageModify()
{
	printf("-----\n");
}

void fUsageDisplay()
{
	printf("------\n");
}

int fUsageMenu()
{
	printf("=====================\n");
	printf("Facility Usage Module\n");
	printf("=====================\n");
	printf("1. View Record\n");
	printf("2. Add\n");
	printf("3. Modify Record\n");
	printf("4. Display Facility Usage Status\n");
	printf("5. Return to Menu\n");

	char choice[10];
	printf("\nEnter Menu Choice : ");
	scanf("%s", &choice);
	switch (choice[0])
	{
	case'1':fUsageRecord();
		break;
	case'2':fUsageAddRecord();
		break;
	case'3':fUsageModify();
		break;
	case'4':fUsageDisplay();
		break;
	case'5':
		return 0;
	default:
		return 1;
	}
	return choice[0];
}
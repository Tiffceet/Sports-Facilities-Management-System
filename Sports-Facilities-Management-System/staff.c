#include "stdcxx.h"
#include "staff.h"


int i;

//struct {
//
//
//};

typedef struct// struture for to store staff
{
	char stfName[30];
	char stfPassW[100];
	char stfConPassW[100];
	char stfID[6];
	char stfPosi[10];
}Staff;


void staffmain()
{
	addStaffList();
	readStaffList();
	system("pause");
}

void addStaffList()//For adding new staff
{
	Staff staffs[20];
	FILE*stf;

	stf = fopen("staffNameList.bin", "ab");

	if (!stf)//For checking exsitent of file.
	{
		printf("can't open");
		return;
	}
	
	for (i = 0; i < 2; i++)
	{
		printf("Enter staff name : ");
		rewind(stdin);
		scanf("%[^\n]", staffs[i].stfName);
		rewind(stdin);
		printf("Enter staff Passwords(MINIMUM 12): ");
		scanf("%[^\n]", staffs[i].stfPassW);
		rewind(stdin); 
		printf("Enter staff ID : ");
		scanf("%[^\n]", staffs[i].stfID);
		rewind(stdin);
		printf("Enter staff position :");
		scanf("%[^\n]", staffs[i].stfPosi);
		rewind(stdin);

		fwrite(&staffs, sizeof(Staff), 1, stf);
	}
	fclose(stf);
	return;
}

void readStaffList()
{
	FILE*stfRead;
	Staff staffScanList[20];//to store date scaned from file

	stfRead = fopen("staffNameList.bin", "rb");

	if (!stfRead)
	{
		printf("Can't find file (read)");
		return;
	}

	for (i = 0; i < 2; i++)
	{
		while (fread(&staffScanList[i], sizeof(staffScanList[i]), 1, stfRead) != 0)
		{
			printf("Name:%s\nID:%s\nPosition:%s\n", staffScanList[i].stfName,staffScanList[i].stfID,staffScanList[i].stfPosi);
		}
	}
	fclose(stfRead);
	return;
}

void login()
{
	printf("");
}
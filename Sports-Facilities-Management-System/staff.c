#include "stdcxx.h"
#include "staff.h"



//struct {
//
//
//};

typedef struct// struture for to store staff
{
	char stfName[30];
	char stfPassW[100];
	char stfConPassW[100];// confirm password
	char stfID[6];
	char stfPosi[10];
}Staff;


void staffmain()
{
	addStaffList();
	
	system("pause");
}

void addStaffList()//For adding new staff
{
	int i, ans;//for loop
	char idEntered[6]; //to check if id entered is being used

	Staff staffs[20];
	FILE*stf;

	stf = fopen("staffNameList.bin", "ab");

	if (!stf)//For checking exsitent of file.
	{
		printf("can't open");
		return;
	}
	
	for (i = 0; i < 20; i++)
	{
		printf("Enter staff name : ");
		rewind(stdin);
		scanf("%[^\n]", staffs[i].stfName);
		rewind(stdin);
		printf("Enter staff Passwords(MINIMUM 12): ");
		scanf("%[^\n]", staffs[i].stfPassW);
		rewind(stdin); 
		printf("Reenter passowrd to confirm :");
		scanf("%[^\n]",staffs[i].stfConPassW);
	    rewind(stdin);
		while (strcmp(staffs[i].stfPassW, staffs[i].stfConPassW) != 0)
		{
			printf("Passwords does not match please reenter !\n");
			rewind(stdin);
			printf("Enter staff Passwords(MINIMUM 12) :");
			scanf("%[^\n]", staffs[i].stfPassW);
			rewind(stdin);
			printf("Reenter passowrd to confirm :");
			scanf("%[^\n]", staffs[i].stfConPassW);
			rewind(stdin);
		}
		printf("Enter staff ID(6 characteristics max): ");
		scanf("%[^\n]", idEntered);
		rewind(stdin);
		for (i = 0; i < 20; i++)
		{
			while (strcmp(idEntered, staffs[i].stfID) == 0)
			{
				printf("ID used!\n");
				printf("Reenter ID :");
				scanf("%[^\n]", idEntered);
				rewind(stdin);
				
			}
			if (strlen(staffs[i].stfID)==0)
				{
					strcpy(staffs[i].stfID, idEntered);
				}
		}
		printf("Enter staff position :");
		scanf("%[^\n]", staffs[i].stfPosi);
		rewind(stdin);

		fwrite(&staffs[i], sizeof(Staff), 1, stf);
	}
	fclose(stf);
	return;
}

void readStaffList()
{
	int i=0;

	FILE*stfRead;
	Staff staffScanList[20];//to store date scaned from file

	stfRead = fopen("staffNameList.bin", "rb");

	if (!stfRead)
	{
		printf("Can't find file (read)");
		return;
	}
	
	
		while (fread(&staffScanList[0], sizeof(Staff), 1, stfRead) != 0)
		{
			printf("Name:%s\nID:%s\nPosition:%s\n", staffScanList[0].stfName,staffScanList[0].stfID,staffScanList[0].stfPosi);
			
		}
		
	fclose(stfRead);
	return;
}

void login()
{
	printf("");
}
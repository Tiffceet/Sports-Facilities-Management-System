#include "stdcxx.h"
#include "staff.h"


typedef struct// struture for to store staff
{
	char stfName[30];
	char stfPassW[100];
	char stfConPassW[100];// confirm password
	char stfID[7];
	char stfPosi[10];
}Staff;

Staff staffCache[30];

int readStfList()
{
	int count = 0;
	FILE*readstf;

	readstf = fopen("staffNameList.bin", "rb");

	while (fread(&staffCache[count], sizeof(Staff), 1, readstf) != 0)
	{
		count++;
	}
	fclose(readstf);
	return count;
}

void addStaffList()//For adding new staff
{
	int i, ans,totstaff;//for loop
	char idEntered[7]; //to check if id entered is being used
	
	// read file + get count of item in file
	totstaff = readStfList();
	Staff addStaff;
	FILE*stf;

	stf = fopen("staffNameList.bin", "ab");

	if (!stf)//For checking exsitent of file.
	{
		printf("can't open");
		return;
	}


	
		printf("Enter staff name : ");//ADD VALIDATION
		rewind(stdin);
		scanf("%[^\n]", addStaff.stfName);
		rewind(stdin);
		printf("Enter staff Passwords(MINIMUM 12): ");//ADD VALIDATION
		scanf("%[^\n]", addStaff.stfPassW);
		rewind(stdin);
		printf("Reenter password to confirm :");
		scanf("%[^\n]", addStaff.stfConPassW);
		rewind(stdin);
		while (strcmp(addStaff.stfPassW, addStaff.stfConPassW) != 0)
		{
			printf("Passwords does not match please reenter !\n");
			rewind(stdin);
			printf("Enter staff Passwords(MINIMUM 12) :");//ADD VALIDATION
			scanf("%[^\n]", addStaff.stfPassW);
			rewind(stdin);
			printf("Reenter passowrd to confirm :");
			scanf("%[^\n]", addStaff.stfConPassW);
			rewind(stdin);
		}
		printf("Enter staff ID(6 characteristics max): ");//ADD VALIDATION
		scanf("%[^\n]", idEntered);
		rewind(stdin);
		for (i = 0; i < totstaff; i++)
		{
			while (strcmp(idEntered, staffCache[i].stfID) == 0)
			{
				printf("ID used!\n");
				printf("Reenter ID :");
				scanf("%[^\n]", idEntered);
				rewind(stdin);

			}
		}
		strcpy(addStaff.stfID, idEntered);//NEED TO CHANGE THE POINTER
		
		printf("Enter staff position :");//ADD VALIDATION/CODE
		scanf("%[^\n]", addStaff.stfPosi);
		rewind(stdin);

		fwrite(&addStaff, sizeof(Staff), 1, stf);
	
	fclose(stf);
}

void displayStaffList()
{
	
	int i = 0,count;
	count=readStfList();
	for(i=0;i<count;i++)
	{
		printf("Name:%s\nID:%s\nPosition:%s\n", staffCache[i].stfName, staffCache[i].stfID, staffCache[i].stfPosi);

	}
}


void staffSearchName()
{

}

void staffSearchID()
{

}

void login()
{
	printf("");
}

void changeStfList()
{

}

void pwRecover()
{

}

void staffMain()
{
	addStaffList();
	displayStaffList();
	system("pause");
}
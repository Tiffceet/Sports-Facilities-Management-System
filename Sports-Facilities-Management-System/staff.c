#include "stdcxx.h"
#include "staff.h"


typedef struct// struture for to store staff
{
	char stfName[30];
	char stfPassW[100];
	char stfConPassW[100];// confirm password
	char stfID[6];
	char stfPosi[10];
}Staff;

Staff staffCache[30];

void addStaffList()//For adding new staff
{
	int i, ans;//for loop
	char idEntered[6]; //to check if id entered is being used

	Staff addStaff;
	FILE*stf;

	stf = fopen("staffNameList.bin", "ab");

	if (!stf)//For checking exsitent of file.
	{
		printf("can't open");
		return;
	}

	for (i = 0; i < 20; i++)
	{
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
		for (i = 0; i < 20; i++)
		{
			while (strcmp(idEntered, addStaff.stfID) == 0)//NEED TO LET USER RETYPE
			{
				printf("ID used!\n");
				printf("Reenter ID :");
				scanf("%[^\n]", idEntered);
				rewind(stdin);

			}
			if (strlen(addStaff.stfID) == 0)
			{
				strcpy(addStaff.stfID, idEntered);//NEED TO CHANGE THE POINTER
			}
		}
		printf("Enter staff position :");//ADD VALIDATION/CODE
		scanf("%[^\n]", addStaff.stfPosi);
		rewind(stdin);

		fwrite(&addStaff, sizeof(Staff), 1, stf);
	}
	fclose(stf);
	return;
}

void displayStaffList()
{
	int i = 0;

	FILE*stfDis;
	// Staff staffDisplayList[20];//to read and display date scaned from file


	stfDis = fopen("staffNameList.bin", "rb");

	if (!1)
	{
		printf("Can't find file (read)");
		return;
	}


	while (fread(&staffCache[0], sizeof(Staff), 1, stfDis) != 0)
	{
		printf("Name:%s\nID:%s\nPosition:%s\n", staffCache[0].stfName, staffCache[0].stfID, staffCache[0].stfPosi);

	}

	fclose(stfDis);
	return;
}

int readStfList()
{
	int count = 0;
	FILE*readstf;
	// Staff staffs[20];

	readstf = fopen("staffNameList.bin", "rb");

	while (fread(&staffCache[count], sizeof(Staff), 1, readstf) != 0)
	{
		count++;
	}
	fclose(readstf);
	return count;
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
	//addStaffList();
	displayStaffList();
	system("pause");
}
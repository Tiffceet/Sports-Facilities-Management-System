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

void addStaffList()//For adding new staff(NEED TO MAKE THE PRINT F MUCH BETTER LOOKING)
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

		printf("Enter staff name : ");
		scanf("%[^\n]", addStaff.stfName);
		rewind(stdin);
		while (strlen(addStaff.stfName) > 29)
		{
			printf("Reenter name it's too long.\n");
			printf("Enter staff name : ");
			scanf("%[\n]", addStaff.stfName);
			rewind(stdin);
		}
		
		printf("Enter staff Passwords(MINIMUM 8): ");
		scanf("%[^\n]", addStaff.stfPassW);
		rewind(stdin);
		while (strlen(addStaff.stfPassW) < 8)
		{
			printf("password too short please reenter : \n");
			printf("Enter staff Passwords(MINIMUM 8): ");
			scanf("%[^\n]", addStaff.stfPassW);
			rewind(stdin);
		}
		
		printf("Reenter password to confirm :");
		scanf("%[^\n]", addStaff.stfConPassW);
		rewind(stdin);
		while (strcmp(addStaff.stfPassW, addStaff.stfConPassW) != 0)
		{
			printf("Passwords does not match please reenter !\n");
			rewind(stdin);
			printf("Enter staff Passwords(MINIMUM 8) :");
			scanf("%[^\n]", addStaff.stfPassW);
			rewind(stdin);
			while (strlen(addStaff.stfPassW) < 8)
			{
				printf("password too short please reenter : \n");
				printf("Enter staff Passwords(MINIMUM 8): ");
				scanf("%[^\n]", addStaff.stfPassW);
				rewind(stdin);
			}
			printf("Reenter passowrd to confirm :");
			scanf("%[^\n]", addStaff.stfConPassW);
			rewind(stdin);
		}

		printf("Enter staff ID(6 characters): ");
		scanf("%[^\n]", idEntered);
		rewind(stdin);
		while (strlen(idEntered) != 6)
		{
			printf("Needs to be 6 characters please reenter : \n");
			printf("Enter staff ID(6 characters): ");
			scanf("%[^\n]", idEntered);
			rewind(stdin);
		}
		for (i = 0; i < totstaff; i++)
		{
			while (strcmp(idEntered, staffCache[i].stfID) == 0)
			{
				printf("ID used!\n");
				printf("Reenter ID :");
				scanf("%[^\n]", idEntered);
				rewind(stdin);
				while (strlen(idEntered) != 6)
				{
					printf("Needs to be 6 characters please reenter : \n");
					printf("Enter staff ID(6 characters): ");
					scanf("%[^\n]", idEntered);
					rewind(stdin);
				}

			}
		}
		strcpy(addStaff.stfID, idEntered);
		
		printf("Enter staff position :");
		scanf("%[^\n]", addStaff.stfPosi);
		rewind(stdin);

		fwrite(&addStaff, sizeof(Staff), 1, stf);
	
	fclose(stf);
}

void displayStaffList()//(NEED TO MAKE THE PRINT F MUCH BETTER LOOKING)
{
	
	int i = 0,count;
	count=readStfList();
	for(i=0;i<count;i++)
	{
		printf("Name:%s\nID:%s\nPosition:%s\n", staffCache[i].stfName, staffCache[i].stfID, staffCache[i].stfPosi);

	}
}


void staffSearchName()//(NEED TO MAKE THE PRINT F MUCH BETTER LOOKING)
{
	char staffNameSearch[100],ans;
	int i = 0, totstaff,stfcount = 0;
	totstaff = readStfList();
	
	do
	{
		displayStaffList();

		printf("Enter name staff name to search :");
		scanf("%[^\n]", staffNameSearch);
		rewind(stdin);
		for (i = 0; i < totstaff; i++)
		{
			stfcount++;
			if (strcmp(staffNameSearch, staffCache[i].stfName) == 0)
			{
				printf("Name:%s\nID:%s\nPosition:%s\n", staffCache[i].stfName, staffCache[i].stfID, staffCache[i].stfPosi);
				totstaff = 0;
			}
			else if (stfcount >= totstaff)
			{
				printf("There's no such person please reenter staff name.\n");
			}
			else;
		}
		printf("Do you want to search for someone else?(y = yes,anything else = menus)");
		scanf("%c", &ans);
		rewind(stdin);
	}while (ans == 'y');
}

int staffSearchID()//(NEED TO MAKE THE PRINT F MUCH BETTER LOOKING)
{
	char stfID[7],ans;
	int i = 0, totstaff, stfcount = 0,staffAdd;
	totstaff = readStfList();

	do
	{
		displayStaffList();

		printf("Enter name staff ID to search :");
		scanf("%[^\n]", stfID);
		rewind(stdin);
		for (i = 0; i < totstaff; i++)
		{
			stfcount++;
			if (strcmp(stfID, staffCache[i].stfID) == 0)
			{
				printf("Name:%s\nID:%s\nPosition:%s\n", staffCache[i].stfName, staffCache[i].stfID, staffCache[i].stfPosi);
				totstaff = 0;
			}
			else if (stfcount >= totstaff)
			{
				printf("There's no such person please reenter staff ID.\n");
			}
			else;
		}
		printf("Do you want to search for someone else?(y = yes anything else = continue)");
		scanf("%c", &ans);
		rewind(stdin);
	} while (ans == 'y');
	staffAdd = i;
	return staffAdd;
}

void login()
{
	
}

void changeStfList()//NEED TO ADD A DISPLAY FOR OLD AND NEW AND NEED MAKE BETTER LOOKING DISPLAY
{
	char choice[10];
	
	int oldStaffAdd = 0, totstaff, i;
	totstaff = readStfList();
	Staff staffChange;
	oldStaffAdd=staffSearchID();
	Staff*staffOld = &staffCache[oldStaffAdd ];

	printf("What do you want to change about this staff?\n");
	printf("1. Name\n");
	printf("2. PassWord\n");
	printf("3. ID\n");
	printf("4. Position\n");
	printf("5. exit\n");

	do
	{
		printf("Enter a choice :");
		getUserMenuChoice(choice, 9, "Invalid Choice, try again\n");
		rewind(stdin);
		switch (choice[0])
		{

		case '1':
			printf("Enter new name :");
			scanf("%[^\n]", staffChange.stfName);
			rewind(stdin);
			while (strlen(staffChange.stfName) > 29)
			{
				printf("Reenter name it's too long.\n");
				printf("Enter staff name : ");
				scanf("%[\n]", staffChange.stfName);
				rewind(stdin);
			}
			break;
		case '2':
			printf("Enter new password(MINUMUM 8):");
			scanf("%[^\n]", staffChange.stfPassW);
			rewind(stdin);
			while (strlen(staffChange.stfPassW) < 8)
			{
				printf("password too short please reenter : \n");
				printf("Enter staff Passwords(MINIMUM 8): ");
				scanf("%[^\n]", staffChange.stfPassW);
				rewind(stdin);
			}
			break;
		case '3':
			printf("Enter new staff ID(6 characters): ");
			scanf("%[^\n]", staffChange.stfID);
			rewind(stdin);
			while (strlen(staffChange.stfID) != 6)
			{
				printf("Needs to be 6 characters please reenter : \n");
				printf("Enter staff ID(6 characters): ");
				scanf("%[^\n]", staffChange.stfID);
				rewind(stdin);
			}
			for (i = 0; i < totstaff; i++)
			{
				while (strcmp(staffChange.stfID, staffCache[i].stfID) == 0)
				{
					printf("ID used!\n");
					printf("Reenter ID :");
					scanf("%[^\n]", staffChange.stfID);
					rewind(stdin);
					while (strlen(staffChange.stfID) != 6)
					{
						printf("Needs to be 6 characters please reenter : \n");
						printf("Enter staff ID(6 characters): ");
						scanf("%[^\n]", staffChange.stfID);
						rewind(stdin);
					}

				}
			}
			break;
		case '4':
			printf("Enter new staff position :");
			scanf("%[^\n]", staffChange.stfPosi);
			rewind(stdin);
			break;
		case '5':
			printf("Exiting");
			exit(0);
			break;

		default:
			printf("Invalid choice !\n");
		}
		printf("These are the changes that you made:\n");
	} while (choice != '5');

}

void pwRecover()
{

}

void staffMain()
{
	changeStfList();
	//addStaffList();
	//displayStaffList();
	//staffSearchName();
	//staffSearchID();
	system("pause");
}
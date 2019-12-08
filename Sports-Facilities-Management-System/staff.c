#include "stdcxx.h"
#include "staff.h"


Staff staffCache[30];//Main array to keep staff info from files
Staff loggedinstf;//To check for globla logged in status

int readStfList()
{
	int count = 0;
	FILE*readstf;

	readstf = fopen(staffFilePath, "rb");

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
	char idEntered[6],choice[3]; //to check if id entered is being used
	
	// read file + get count of item in files
	totstaff = readStfList();
	Staff addStaff;
	FILE*stf;

	stf = fopen(staffFilePath, "ab");

	if (!stf)//For checking exsitent of file.
	{
		printf("Can't open");
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

		printf("Enter staff ID(4 characters): ");
		scanf("%[^\n]", idEntered);
		rewind(stdin);
		while (strlen(idEntered) != 4)
		{
			printf("Needs to be 4 characters please reenter!\n");
			printf("Enter staff ID(4 characters): ");
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
				while (strlen(idEntered) != 4)
				{
					printf("Needs to be 4 characters please reenter : \n");
					printf("Enter staff ID(4 characters): ");
					scanf("%[^\n]", idEntered);
					rewind(stdin);
				}

			}
		}
		strcpy(addStaff.stfID, idEntered);
	
		do //maybe add more options
		{
			printf("1.Admin\n2.staff\nEnter staff position : ");
			getUserMenuChoice(choice, 3, "Invalid Choice, try again\n");
			rewind(stdin);
			switch (choice[0])
			{
			case '1':
				strcpy(addStaff.stfPosi, "ADMIN");
				break;
			case '2':
				strcpy(addStaff.stfPosi, "STAFF");
				break;
			default:
				choice[0] = 0;
				printf("Invalid entry!\n\n");
			}
		} while (choice[0]==0);
		
		printf("\n\n");
		printf("Name:%s\nID:%s\nPosition:%s\n", addStaff.stfName, addStaff.stfID, addStaff.stfPosi);
		printf("Do you want to add this staff to the system?(y=yes) :");
		getUserMenuChoice(choice, 3, "Invalid Choice, try again\n");
		rewind(stdin);
		if (choice[0] == 'y')
		{

			Date sysDate;
			getSystemDate(&sysDate);
			printf("Joined date:%d/%d/%d\n", sysDate.d, sysDate.m, sysDate.y);
			sprintf(addStaff.dateRegis, "%d/%d/%d", sysDate.d, sysDate.m, sysDate.y);
			sprintf(addStaff.dateModi, "%d/%d/%d", sysDate.d, sysDate.m, sysDate.y);
			fwrite(&addStaff, sizeof(Staff), 1, stf);
			printf("User added.\n");
			system("pause");
		}
		else
		{
			printf("Registration have been canceled.\n");
			printf("Have a nice day.\n");
			system("Pause");
		}
	fclose(stf);
}

void displayStaffList()//(NEED TO MAKE THE PRINT F MUCH BETTER LOOKING)
{
	
	int i = 0,count;
	count=readStfList();
	if (count == 0)
	{
		printf("There is currently no staff that is registered.\n");
	}
	for(i=0;i<count;i++)
	{
		printf("Name:%s\nID:%s\nPosition:%s\nDate:%s\nLast modified:%s\n\n", staffCache[i].stfName, staffCache[i].stfID, staffCache[i].stfPosi,staffCache[i].dateRegis,staffCache[i].dateModi);

	}
}


void staffSearchName()//(NEED TO MAKE THE PRINT F MUCH BETTER LOOKING)
{
	char staffNameSearch[100],ans;
	int i = 0, totstaff,stfcount = 0;
	totstaff = readStfList();

	if (totstaff != 0)
	{

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
					printf("Name:%s\nID:%s\nPosition:%s\nDate Joined:%s\nDate last modified:%s\n\n", staffCache[i].stfName, staffCache[i].stfID, staffCache[i].stfPosi,staffCache[i].dateRegis,staffCache[i].dateModi);
					break;
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
		} while (ans == 'y');
	}
	else
	{
		printf("No record exist.\n");
		system("pause");
	}
}

int staffSearchID()//(NEED TO MAKE THE PRINT F MUCH BETTER LOOKING)
{
	char stfID[6],ans;
	int i = 0, totstaff, stfcount = 0,staffAdd,stafffound=0;
	totstaff = readStfList();
	if (totstaff != 0)
	{
	do
	{
		system("cls");
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
					stafffound = 1;
					break;
				}
				else if (stfcount >= totstaff)
				{
					printf("There's no such person please reenter staff ID.\n");
				}
			}
			if (stafffound != 1)
			{
				printf("Enter 'y' to reenter :");
				scanf("%c", &ans);
				while (ans != 'y')
				{
					printf("\n");
					printf("You did not enter 'y'! :");
					scanf("%c", &ans);
				}
			}
			else
			{
				printf("\n");
				printf("Do you want to search for someone else?(y = yes anything else = continue)");
				scanf("%c", &ans);
			}
			rewind(stdin);
		} while (ans == 'y');
		staffAdd = i;
		return staffAdd;
	}
}


void changeStfList()//NEED TO ADD A DISPLAY FOR OLD AND NEW AND NEED MAKE BETTER LOOKING DISPLAY
{
	char choice[10];
	
	int oldStaffAdd = 0, totstaff, i;
	totstaff = readStfList();
	Staff staffChange;
	oldStaffAdd=staffSearchID();
	FILE*stfopen;

	if (totstaff != 0)
	{
		stfopen = fopen(staffFilePath, "ab");

		strcpy(staffChange.stfID, staffCache[oldStaffAdd].stfID);
		strcpy(staffChange.stfName, staffCache[oldStaffAdd].stfName);
		strcpy(staffChange.stfPassW, staffCache[oldStaffAdd].stfPassW);
		strcpy(staffChange.stfPosi, staffCache[oldStaffAdd].stfPosi);

		do
		{
			system("cls");
			printf("Name:%s\nPassword:%s\nID:%s\nPosition:%s\n\n", staffCache[oldStaffAdd].stfName, staffCache[oldStaffAdd].stfPassW, staffCache[oldStaffAdd].stfID, staffCache[oldStaffAdd].stfPosi);

			printf("What do you want to change about this staff?\n");
			printf("1. Name\n");
			printf("2. PassWord\n");
			printf("3. ID\n");
			printf("4. Position\n");
			printf("5. exit\n");

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
				printf("Enter new staff ID(4 characters): ");
				scanf("%[^\n]", staffChange.stfID);
				rewind(stdin);
				while (strlen(staffChange.stfID) != 4)
				{
					printf("Needs to be 4 characters please reenter : \n");
					printf("Enter staff ID(4 characters): ");
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
						while (strlen(staffChange.stfID) != 4)
						{
							printf("Needs to be 4 characters please reenter : \n");
							printf("Enter staff ID(4 characters): ");
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
				return;

			default:
				printf("Invalid choice !\n");
			}

			printf("These are the changes that you made:\n");
			printf("(OLD)\nName:%s\nPassword:%s\nID:%s\nPosition:%s\n", staffCache[oldStaffAdd].stfName, staffCache[oldStaffAdd].stfPassW, staffCache[oldStaffAdd].stfID, staffCache[oldStaffAdd].stfPosi);
			printf("(NEW)\nName:%s\nPassword:%s\nID:%s\nPosition:%s\n\n", staffChange.stfName, staffChange.stfPassW, staffChange.stfID, staffChange.stfPosi);
			printf("Do you want to commit to the changes?(y=yes)"); 
			getUserMenuChoice(choice, 9, "Invalid Choice, try again\n");
			if (tolower(choice[0]) == 'y')
			{
				strcpy(staffCache[oldStaffAdd].stfName, staffChange.stfName);
				strcpy(staffCache[oldStaffAdd].stfID, staffChange.stfID);
				strcpy(staffCache[oldStaffAdd].stfPassW, staffChange.stfPassW);
				strcpy(staffCache[oldStaffAdd].stfPosi, staffChange.stfPosi);
				Date sysDate;
				getSystemDate(&sysDate);
				printf("%d:%d\n", sysDate.d, sysDate.m, sysDate.y);
				sprintf(staffCache[oldStaffAdd].dateModi, "%d/%d/%d", sysDate.d, sysDate.m, sysDate.y);
				fclose(stfopen);
				stfopen = fopen(staffFilePath, "wb");
				for (int a = 0; a < totstaff; a++)
				{
					fwrite(&staffCache[a], sizeof(Staff), 1, stfopen);
				}
				fclose(stfopen);


				printf("Changes have been made this is the new staff info.\n");
				printf("(NEW)\nName:%s\nPassword:%s\nID:%s\nPosition:%s\n\n"
					, staffCache[oldStaffAdd].stfName, staffCache[oldStaffAdd].stfPassW, staffCache[oldStaffAdd].stfID, staffCache[oldStaffAdd].stfPosi);

				system("cls");
				displayStaffList();
			}
		} while (choice != '5');
	}
	else
	{
	printf("No records exist.\n");
	system("pause");
	}
}

void login()//log in
{
	char nameEntered[30], passwordEntered[30];
	int i = 0, totstaff, stfcount = 0, stfSuccessfullLogin;
	totstaff = readStfList();
	if (totstaff != 0)
	{

		do
		{
			printf("Name :");
			scanf("%[^\n]", nameEntered);
			rewind(stdin);
			printf("Passwords :");
			scanf("%[^\n]", passwordEntered);
			rewind(stdin);
			for (i = 0; i < totstaff; i++)
			{
				if (strcmp(nameEntered, staffCache[i].stfName) == 0 && strcmp(passwordEntered, staffCache[i].stfPassW) == 0)
				{
					printf("Welcome,%s\n", staffCache[i].stfName);
					stfSuccessfullLogin = 1;
					break;
				}
				else
				{
					printf("Password or log in ID is incorrect.\n");
				}
			}
		} while (stfSuccessfullLogin == 0);

		strcpy(loggedinstf.stfPosi, staffCache[i].stfPosi);
		strcpy(loggedinstf.stfName, staffCache[i].stfName);
		strcpy(loggedinstf.stfID, staffCache[i].stfID);
	}
	else
	{
		printf("No record of staff is found.\n");
		printf("Proceeding to staff registration.\n");
		system("pause");
	}
}

int checkPosition()
{

	int position = -1;
	if (strcmp(loggedinstf.stfPosi, "ADMIN") == 0)//For admin
	{
		position = 0;
	}
	else if (strcmp(loggedinstf.stfPosi, "STAFF") == 0)//For staffs
	{
		position = 1;
	}
	else
	{
		position = 2;
	}
	return position;
}

void pwRecover()
{

}

void staffMain()// still need to add places to indentify position
{
	FILE*stflist;
	stflist = fopen(staffFilePath, "ab");
	if (!stflist)
	{
		printf("Can't open file");
		return;
	}
	fclose(stflist);

	int err = 0;
	char choice[10];
	do
	{
		system("cls");
		char choiceText[][100] = { "Staff list", "Add staff", "Search staff", "Change staff info", "Exit" };
		int choice = globalMainMenu("<!> Staff infomations Console <!>", 5, choiceText);
		switch (choice)
		{

		case 1:
			displayStaffList();
			system("pause");
			break;
		case 2:
			addStaffList();
			break;
		case 3:
			staffSearchName();
			break;
		case 4:
			changeStfList();
			break;
		case 5:
			return;
		default:
			break;
		}
	} while (choice != 5);
}


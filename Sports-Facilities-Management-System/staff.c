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

int isAlNum(char str[])
{
	if (!strchr(str, '\0'))
	{
		return 0; // string not initialise
	}
	for (int a = 0; a < strlen(str); a++)
	{
		if (!isalnum(str[a])) // is not alphanumeric
		{
			if (!isspace((unsigned char)str[a])) // is not space
			{
				return 0;
			}
		}

	}
	return 1;
}

void addStaffList()//For adding new staff(NEED TO MAKE CONFRIMATION FOR EVERY ENTRY)
{
	int i, valid,totstaff,totalCondition,strLength,ifUsed;//for loop
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
		
	do
	{
		strLength = 0;
		ifUsed = 1;
		totalCondition = 3;
		printf("Enter staff name : ");
		scanf("%[^\n]", addStaff.stfName);
		if ((strlen(addStaff.stfName)) < 30)
		{
			strLength = 1;
		}
		rewind(stdin);
		valid = isAlNum(addStaff.stfName);
		for (i = 0; i < totstaff; i++)
		{
			if (strcmp(addStaff.stfName, staffCache[i].stfName) == 0)
			{
				ifUsed = 0;
			}
		}
		if (totalCondition != ifUsed + strLength + valid)
		{
			printf("Name fails to meet the following condition \n");
			if (valid != 1)
			{
				printf("Only numbers and alphabet are allowed in entry.\n");
			}
			if (ifUsed != 1)
			{
				printf("Name exist in our system.\n");
			}
			if (strLength != 1)
			{
				printf("Length of entry is too long.(limit = 29)\n");
			}
			rewind(stdin);
		}
	} while (totalCondition != valid + ifUsed + strLength);
		

		
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
			printf("Enter staff ID(4 characters) : ");
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
					printf("Enter staff ID(4 characters) : ");
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
	
		printf("%25s====================================================================\n", "");
		printf("%25s|%20sREGISTING STAFF INFOMATION%20s|\n", "", "", "");
		printf("%25s====================================================================\n", "");
		printf("%25s|Name :%-60s|\n%25s|ID :%-62s|\n%25s|Position :%-56s|\n","", addStaff.stfName,"",addStaff.stfID,"",addStaff.stfPosi);
		printf("%25s====================================================================\n", "");
		printf("Do you want to add this staff to the system?(y=yes) :");
		getUserMenuChoice(choice, 3, "Invalid Choice, try again\n");
		rewind(stdin);
		if (choice[0] == 'y')
		{

			Date sysDate;
			getSystemDate(&sysDate);
			printf("Joined date:%d/%d/%d\n", sysDate.d, sysDate.m, sysDate.y);
			addStaff.dateRegis = sysDate;
			addStaff.dateModi = sysDate;
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
	printf("%25s====================================================================\n", "");
	printf("%25s|%28sSTAFF LIST%28s|\n", "", "", "");
	printf("%25s====================================================================\n", "");
	for(i=0;i<count;i++)
	{
		
		printf("%25s|Name :%-60s|\n"
			"%25s|ID :%-62s|\n"
			"%25s|Position :%-56s|\n"
			"%25s|Date :%d/%d/%-54d|\n"
			"%25s|Last modified :%d/%d/%-45d|\n","",staffCache[i].stfName,"",staffCache[i].stfID,"",staffCache[i].stfPosi,"",staffCache[i].dateRegis.d,staffCache[i].dateRegis.m, staffCache[i].dateRegis.y,"",staffCache[i].dateModi.d, staffCache[i].dateModi.m, staffCache[i].dateModi.y);
		printf("%25s====================================================================\n", "");
	}
}


int staffSearchName()//(NEED TO MAKE THE PRINT F MUCH BETTER LOOKING)
{
	char staffNameSearch[100],ans;
	int i = 0, totstaff,stfcount = 0, staffAdd;
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
					printf("%25s====================================================================\n", "");
					printf("%25s|%28sSTAFF LIST%28s|\n", "", "", "");
					printf("%25s====================================================================\n", "");
					printf("%25s|Name :%-60s|\n"
						"%25s|ID :%-62s|\n"
						"%25s|Position :%-56s|\n"
						"%25s|Date :%d/%d/%-54d|\n"
						"%25s|Last modified :%d/%d/%-45d|\n", "", staffCache[i].stfName, "", staffCache[i].stfID, "", staffCache[i].stfPosi, "", staffCache[i].dateRegis.d, staffCache[i].dateRegis.m, staffCache[i].dateRegis.y, "", staffCache[i].dateModi.d, staffCache[i].dateModi.m, staffCache[i].dateModi.y);
					printf("%25s====================================================================\n", "");
					break;
				}
				else if (stfcount >= totstaff)
				{
					printf("There's no such person please reenter staff name.\n");
				}
				else;
			}
			printf("After viewing staff's infomation enter y to continue,anything else to search for another staff :");
			scanf("%c", tolower(&ans));
			rewind(stdin);
		} while (ans != 'y');
		staffAdd = i;
		return staffAdd;
	}
	else
	{
		printf("No record exist.\n");
		system("pause");
	}
}

void staffSearchID()//(NEED TO MAKE THE PRINT F MUCH BETTER LOOKING)
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
					printf("%25s====================================================================\n", "");
					printf("%25s|%28sSTAFF LIST%28s|\n", "", "", "");
					printf("%25s====================================================================\n", "");
					printf("%25s|Name :%-60s|\n%25s|ID :%-62s|\n%25s|Position :%-56s|\n","",staffCache[i].stfName,"",staffCache[i].stfID,"",staffCache[i].stfPosi);
					printf("%25s====================================================================\n", "");
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
	oldStaffAdd=staffSearchName();
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
			printf("%25s====================================================================\n", "");
			printf("%25s|%25sSTAFF INFOMATION%25s|\n", "", "", "");
			printf("%25s====================================================================\n", "");
			printf("%25s|Name :%-60s|\n%25s|Password :%-56s|\n%25s|ID :%-62s|\n%25s|Position :%-56s|\n","",staffCache[oldStaffAdd].stfName,"", staffCache[oldStaffAdd].stfPassW,"",staffCache[oldStaffAdd].stfID,"",staffCache[oldStaffAdd].stfPosi);
			printf("%25s====================================================================\n", "");

			printf("What do you want to change about this staff?\n");
			printf("1. Name\n");
			printf("2. Password\n");
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
				printf("Reenter password to confirm :");
				scanf("%[^\n]", staffChange.stfConPassW);
				rewind(stdin);
				while (strcmp(staffChange.stfPassW, staffChange.stfConPassW) != 0)
				{
					printf("Passwords does not match please reenter !\n");
					rewind(stdin);
					printf("Enter staff Passwords(MINIMUM 8) :");
					scanf("%[^\n]", staffChange.stfPassW);
					rewind(stdin);
					while (strlen(staffChange.stfPassW) < 8)
					{
						printf("password too short please reenter : \n");
						printf("Enter staff Passwords(MINIMUM 8): ");
						scanf("%[^\n]", staffChange.stfPassW);
						rewind(stdin);
					}
					printf("Reenter passowrd to confirm :");
					scanf("%[^\n]", staffChange.stfConPassW);
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
				do //maybe add more options
				{
					printf("1.Admin\n2.staff\nEnter staff position : ");
					getUserMenuChoice(choice, 3, "Invalid Choice, try again\n");
					rewind(stdin);
					switch (choice[0])
					{
					case '1':
						strcpy(staffChange.stfPosi, "ADMIN");
						break;
					case '2':
						strcpy(staffChange.stfPosi, "STAFF");
						break;
					default:
						choice[0] = 0;
						printf("Invalid entry!\n\n");
					}
				} while (choice[0] == 0);
				rewind(stdin);
				break;
			case '5':
				printf("Exiting");
				return;

			default:
				printf("Invalid choice !\n");
			}

			printf("These are the changes that you made:\n");
			printf("%25s====================================================================\n", "");
			printf("%25s|%25sSTAFF INFOMATION(OLD)%20s|\n", "", "", "");
			printf("%25s====================================================================\n", "");
			printf("%25s|Name :%-60s|\n%25s|Password :%-56s|\n%25s|ID :%-62s|\n%25s|Position :%-56s|\n","",staffCache[oldStaffAdd].stfName,"",staffCache[oldStaffAdd].stfPassW,"",staffCache[oldStaffAdd].stfID,"",staffCache[oldStaffAdd].stfPosi);
			printf("%25s====================================================================\n\n", "");

			printf("%25s====================================================================\n", "");
			printf("%25s|%25sSTAFF INFOMATION(NEW)%20s|\n", "", "", "");
			printf("%25s====================================================================\n", "");
			printf("%25s|Name :%-60s|\n%25s|Password :%-56s|\n%25s|ID :%-62s|\n%25s|Position :%-56s|\n","",staffChange.stfName,"",staffChange.stfPassW,"",staffChange.stfID,"",staffChange.stfPosi);
			printf("%25s====================================================================\n\n", "");
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
				printf("Date:%d/%d/%d\n", sysDate.d, sysDate.m, sysDate.y);
				staffCache[oldStaffAdd].dateModi = sysDate;
				fclose(stfopen);
				stfopen = fopen(staffFilePath, "wb");
				for (int a = 0; a < totstaff; a++)
				{
					fwrite(&staffCache[a], sizeof(Staff), 1, stfopen);
				}
				fclose(stfopen);


				printf("Changes have been made,this is the staff's new info.\n");
				system("pause");
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
			staffSearchID();
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
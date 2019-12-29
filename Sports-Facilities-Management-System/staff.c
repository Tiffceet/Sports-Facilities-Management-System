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

int addStaffList()//For adding new staff(NEED TO MAKE CONFRIMATION FOR EVERY ENTRY)
{
	int i, valid,totstaff,totalCondition,strLength,ifUsed;//for loop
	int changeAdmin = 0;
	char idEntered[6],choice[3],ans; //to check if id entered is being used
	
	// read file + get count of item in files
	totstaff = readStfList();
	Staff addStaff;
	FILE*stf;

	stf = fopen(staffFilePath, "ab");

	if (!stf)//For checking exsitent of file.
	{
		printf("Can't open");
		return 1;
	}
		
	printf("%25s====================================================================\n", "");
	printf("%25s|%24sSTAFF REGISTRATION%24s|\n", "", "", "");
	printf("%25s====================================================================\n", "");

	do
	{
		strLength = 0;
		ifUsed = 1;
		totalCondition = 3;
		printf("Enter staff name (Enter ""CANCEL"" to return to staff module) : ");
		scanf("%[^\n]", addStaff.stfName);
		if (strcmp(addStaff.stfName, "CANCEL") == 0)
		{
			printf("Returning to staff module.\n");
			system("pause");
			return 1;
		}
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
			printf("\n");
			printf("Name fails to meet the following condition :\n");
			printf("====================================================\n");
			if (valid != 1)
			{
				printf("-Only numbers and alphabet are allowed in entry\n");
			}
			if (ifUsed != 1)
			{
				printf("-Name exist in our system\n");
			}
			if (strLength != 1)
			{
				printf("-Length of entry is too long.(limit = 29)\n");
			}
			printf("====================================================\n");
			printf("\n");

			rewind(stdin);
		}
	} while (totalCondition != valid + ifUsed + strLength);
		

		
		printf("Enter staff Passwords(MINIMUM 8): ");
		collectCensoredInput(addStaff.stfPassW, 99);
		rewind(stdin);
		while (strlen(addStaff.stfPassW) < 8)
		{
			printf("password too short please reenter : \n");
			printf("Enter staff Passwords(MINIMUM 8): ");
			collectCensoredInput(addStaff.stfPassW, 99);
			rewind(stdin);
		}
		
		printf("Reenter password to confirm :");
		collectCensoredInput(addStaff.stfConPassW, 99);
		rewind(stdin);
		while (strcmp(addStaff.stfPassW, addStaff.stfConPassW) != 0)
		{
			printf("Passwords does not match please reenter !\n");
			rewind(stdin);
			printf("Enter staff Passwords(MINIMUM 8) :");
			collectCensoredInput(addStaff.stfPassW, 99);
			rewind(stdin);
			while (strlen(addStaff.stfPassW) < 8)
			{
				printf("password too short please reenter!\n");
				printf("Enter staff Passwords(MINIMUM 8): ");
				collectCensoredInput(addStaff.stfPassW, 99);
				rewind(stdin);
			}
			printf("Reenter passowrd to confirm :");
			collectCensoredInput(addStaff.stfConPassW, 99);
			rewind(stdin);
		}

		do {
			strLength = 0;
			ifUsed = 1;
			totalCondition = 3;
			printf("Enter staff ID(4 characters): ");
			scanf("%[^\n]", addStaff.stfID);
			rewind(stdin);

			if (strlen(addStaff.stfID) == 4)
			{
				strLength = 1;
			}
			valid = isAlNum(addStaff.stfID);
			for (i = 0; i < totstaff; i++)
			{
				while (strcmp(addStaff.stfID, staffCache[i].stfID) == 0)
				{
					ifUsed = 0;
					break;
				}
			}
			if (totalCondition != ifUsed + strLength + valid)
			{
				printf("\n");
				printf("ID fails to meet the following condition \n");
				printf("====================================================\n");
				if (valid != 1)
				{
					printf("-Only numbers and alphabet are allowed in entry\n");
				}
				if (ifUsed != 1)
				{
					printf("-ID exist in our system\n");
				}
				if (strLength != 1)
				{
					printf("-Length of entry is not 4\n");
				}
				rewind(stdin);
				printf("====================================================\n");
				printf("\n");
			}
		} while (totalCondition != strLength + ifUsed + valid);

	
		do //maybe add more options
		{
			printf("1.Admin\n2.staff\nEnter staff position : ");
			getUserMenuChoice(choice, 3, "Invalid Choice, try again\n");
			rewind(stdin);
			switch (choice[0])
			{
			case '1':
				printf("Making this staff admin will strip you of your admin position.\n");
				printf("Do you proceed?(y=yes) :");
				scanf("%c", &ans);
				while (ans != 'y' && ans != 'n')
				{
					printf("Invalid entry\n");
					printf("Please reenter y or n :");
					scanf(" %c", &ans);
				}
				if (ans == 'y')
				{
					strcpy(addStaff.stfPosi, "ADMIN");
					changeAdmin = 1;
				}
				else
				{
					strcpy(addStaff.stfPosi, "STAFF");
					printf("The new staff has been assigned positon ""STAFF""\n");
				}
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
		printf("%25s|Name :%-60s|\n%25s|Position :%-56s|\n","", addStaff.stfName,"",addStaff.stfPosi);
		printf("%25s====================================================================\n", "");
		printf("Do you want to add this staff to the system?(y=yes) :");
		getUserMenuChoice(choice, 3, "Invalid Choice, try again\n");
		rewind(stdin);
		if (choice[0] == 'y')
		{

			if (changeAdmin == 1)
			{
				Date sysDate;
				getSystemDate(&sysDate);
				printf("Joined date:%.02d/%.02d/%d\n", sysDate.d, sysDate.m, sysDate.y);
				addStaff.dateRegis = sysDate;
				addStaff.dateModi = sysDate;
				fwrite(&addStaff, sizeof(Staff), 1, stf);
				fclose(stf);
				totstaff = readStfList();

				for (i = 0; i < totstaff; i++)
				{
					if (strcmp(loggedinstf.stfID, staffCache[i].stfID) == 0)
					{
						strcpy(staffCache[i].stfPosi, "STAFF");
						stf = fopen(staffFilePath, "wb");
						for (i = 0; i < totstaff; i++)
						{
							fwrite(&staffCache[i], sizeof(Staff), 1, stf);
						}
						fclose(stf);
						printf("Position ""ADMIN"" was pass on to the new staff.\n");
						printf("Your position was set to ""STAFF""\n");
						printf("Programming is restarting to enforce the change of admin.\n");
						system("pause");
						return 0;

					}

				}
			}


			Date sysDate;
			getSystemDate(&sysDate);
			printf("Joined date:%.02d/%.02d/%d\n", sysDate.d, sysDate.m, sysDate.y);
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
	return 1;
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
			"%25s|Position :%-56s|\n"
			"%25s|Date :%02.d/%02.d/%-54d|\n"
			"%25s|Last modified :%02.d/%02.d/%-45d|\n","",staffCache[i].stfName,"",staffCache[i].stfPosi,"",staffCache[i].dateRegis.d,staffCache[i].dateRegis.m, staffCache[i].dateRegis.y,"",staffCache[i].dateModi.d, staffCache[i].dateModi.m, staffCache[i].dateModi.y);
		printf("%25s====================================================================\n", "");
	}
}


int staffSearchName()//(NEED TO MAKE THE PRINT F MUCH BETTER LOOKING)
{
	char staffNameSearch[100],ans;
	int i = 0, totstaff,stfcount = 0, staffAdd,stffound=0;
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
						"%25s|Position :%-56s|\n"
						"%25s|Date :%.02d/%.02d/%-54d|\n"
						"%25s|Last modified :%.02d/%.02d/%-45d|\n", "", staffCache[i].stfName, "", staffCache[i].stfPosi, "", staffCache[i].dateRegis.d, staffCache[i].dateRegis.m, staffCache[i].dateRegis.y, "", staffCache[i].dateModi.d, staffCache[i].dateModi.m, staffCache[i].dateModi.y);
					printf("%25s====================================================================\n", "");
					stffound = 1;
					break;
				}
				else if (stfcount >= totstaff)
				{
					printf("There's no such person in our system.\n");
					system("pause");
					break;
				}
				else;
			}
			if (stffound == 1)
			{
				printf("After viewing staff's infomation enter y to continue,n to search for another staff :");
				scanf("%c", &ans);
				while (ans != 'y' && ans != 'n')
				{
					printf("Invalid entry\n");
					printf("Please reenter y or n :");
					scanf(" %c", &ans);
				}
			}
			else
			{
				system("cls");
				ans = 'n';
			}
			rewind(stdin);
		} while (ans != 'y');
		if (stffound = 1)
		{
			staffAdd = i;
			return staffAdd;
		}
	}
	else
	{
		printf("No record exist.\n");
		system("pause");
		return 0;
	}
}

void staffSearchID()
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
				do
				{
					printf("Invalid entry\n");
					printf("Please reenter y or n :");
					scanf("%c", &ans);
				} while (ans != 'y' || ans != 'n');
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
				while (ans != 'y' && ans != 'n')
				{
					printf("Invalid entry\n");
					printf("Please reenter y or n :");
					scanf(" %c", &ans);
				}
			}
			rewind(stdin);
		} while (ans == 'y');
		staffAdd = i;
		return staffAdd;
	}
}


int changeStfList()
{
	char choice[10],ans;
	
	int oldStaffAdd = -1, totstaff, i, totalCondition=0, strLength=0, ifUsed=0,valid=0;
	int changeAdmin = 0;
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
			printf("3. Position\n");
			printf("4. exit\n");

			printf("Enter a choice :");
			getUserMenuChoice(choice, 9, "Invalid Choice, try again\n");
			rewind(stdin);
			switch (choice[0])
			{

			case '1':
				do
				{
					strLength = 0;
					ifUsed = 1;
					totalCondition = 3;
					printf("Enter new name : ");
					scanf("%[^\n]", staffChange.stfName);
					if ((strlen(staffChange.stfName)) < 30)
					{
						strLength = 1;
					}
					rewind(stdin);
					valid = isAlNum(staffChange.stfName);
					for (i = 0; i < totstaff; i++)
					{
						if (strcmp(staffChange.stfName, staffCache[i].stfName) == 0)
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
				break;
			case '2':
				printf("Enter new password(MINUMUM 8):");
				collectCensoredInput(staffChange.stfPassW, 99);
				rewind(stdin);
				while (strlen(staffChange.stfPassW) < 8)
				{
					printf("password too short please reenter : \n");
					printf("Enter staff Passwords(MINIMUM 8): ");
					collectCensoredInput(staffChange.stfPassW, 99);
					rewind(stdin);
				}
				printf("Reenter password to confirm :");
				collectCensoredInput(staffChange.stfConPassW, 99);
				rewind(stdin);
				while (strcmp(staffChange.stfPassW, staffChange.stfConPassW) != 0)
				{
					printf("Passwords does not match please reenter !\n");
					rewind(stdin);
					printf("Enter staff Passwords(MINIMUM 8) :");
					collectCensoredInput(staffChange.stfPassW, 99);
					rewind(stdin);
					while (strlen(staffChange.stfPassW) < 8)
					{
						printf("password too short please reenter : \n");
						printf("Enter staff Passwords(MINIMUM 8): ");
						collectCensoredInput(staffChange.stfPassW, 99);
						rewind(stdin);
					}
					printf("Reenter passowrd to confirm :");
					collectCensoredInput(staffChange.stfConPassW, 99);
					rewind(stdin);
				}
				break;
			case '3':
				do //maybe add more options
				{
					if (strcmp(staffCache[oldStaffAdd].stfPosi, "ADMIN") == 0)
					{
						printf("Admins are not allow to change thier position.\n");
						printf("They are only allow to pass thier position to others.\n");
						system("Pause");
						return 1;
					}
					printf("1.Admin\n2.staff\nEnter staff position : ");
					getUserMenuChoice(choice, 3, "Invalid Choice, try again\n");
					rewind(stdin);
					switch (choice[0])
					{
					case '1':
						printf("Making this staff admin will strip you of your admin position.\n");
						printf("Do you proceed?(y=yes) :");
						scanf("%c", &ans);
						while (ans != 'y' && ans != 'n')
						{
							printf("Invalid entry\n");
							printf("Please reenter y or n :");
							scanf(" %c", &ans);
						}
						if (ans == 'y')
						{
							strcpy(staffChange.stfPosi, "ADMIN");
							changeAdmin = 1;
						}
						else
						{
							strcpy(staffChange.stfPosi, "STAFF");
							printf("The staff has been assigned positon ""STAFF""\n");
						}
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
			case '4':
				printf("Exiting");
				return 1;
				break;
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
				if (changeAdmin == 1)
				{
					strcpy(staffCache[oldStaffAdd].stfName, staffChange.stfName);
					strcpy(staffCache[oldStaffAdd].stfPassW, staffChange.stfPassW);
					strcpy(staffCache[oldStaffAdd].stfPosi, staffChange.stfPosi);
					Date sysDate;
					getSystemDate(&sysDate);
					printf("Date:%.02d/%.02d/%d\n", sysDate.d, sysDate.m, sysDate.y);
					staffCache[oldStaffAdd].dateModi = sysDate;

					for (i = 0; i < totstaff; i++)
					{
						if (strcmp(loggedinstf.stfID, staffCache[i].stfID) == 0)
						{
							strcpy(staffCache[i].stfPosi, "STAFF");
							stfopen = fopen(staffFilePath, "wb");
							for (i = 0; i < totstaff; i++)
							{
								fwrite(&staffCache[i], sizeof(Staff), 1, stfopen);
							}
							fclose(stfopen);
						}
						fclose(stfopen);
					}
				}
				else
				{
					strcpy(staffCache[oldStaffAdd].stfName, staffChange.stfName);
					strcpy(staffCache[oldStaffAdd].stfPassW, staffChange.stfPassW);
					strcpy(staffCache[oldStaffAdd].stfPosi, staffChange.stfPosi);
					Date sysDate;
					getSystemDate(&sysDate);
					printf("Date:%.02d/%.02d/%d\n", sysDate.d, sysDate.m, sysDate.y);
					staffCache[oldStaffAdd].dateModi = sysDate;
					fclose(stfopen);
					stfopen = fopen(staffFilePath, "wb");
					for (i = 0; i < totstaff; i++)
					{
						fwrite(&staffCache[i], sizeof(Staff), 1, stfopen);
					}
					fclose(stfopen);
				}
				if (changeAdmin == 1)
				{
					printf("Position ""ADMIN"" was pass on to the new staff.\n");
					printf("Your position was set to ""STAFF""\n");
					printf("Programming is restarting to enforce the change of admin.\n");
					system("pause");
					return 0;
				}
				printf("Changes have been made,this is the staff's new info.\n");
				system("pause");
				system("cls");
				displayStaffList();
			}
		} while (choice != '4');
	}
	else
	{
	printf("No records exist.\n");
	system("pause");
	}
}

void login()//log in
{
	char nameEntered[30], passwordEntered[30],ans;
	int i = 0, totstaff, stfcount = 0, stfSuccessfullLogin=0,incorrectlogins=0,failedlogins=0;
	totstaff = readStfList();
	if (totstaff != 0)
	{

		do
		{
			totstaff = readStfList();
			printf("%25s====================================================================\n", "");
			printf("%25s|%26s<STAFF LOGIN>%27s|\n", "", "", "");
			printf("%25s|%5sNOTE:Only staffs are allowed to login to staff module.%7s|\n", "", "", "");
			printf("%25s|%5sNormal account will not be allowed to login here.%12s|\n", "", "", "");
			printf("%25s====================================================================\n", "");
			printf("Name :");
			scanf("%[^\n]", nameEntered);
			rewind(stdin);
			printf("Passwords :");
			collectCensoredInput(passwordEntered, 99);
			rewind(stdin);
			for (i = 0; i < totstaff; i++)
			{
				if (strcmp(nameEntered, staffCache[i].stfName) == 0 && strcmp(passwordEntered, staffCache[i].stfPassW) == 0)
				{
					printf("Welcome,%s\n", staffCache[i].stfName);
					system("pause");
					stfSuccessfullLogin = 1;
					break;
				}
				else
				{
					incorrectlogins++;
					if (incorrectlogins >= totstaff) 
					{
						printf("Password or log in ID is incorrect.\n");
						system("pause");
						failedlogins++;
						if (failedlogins >= 3)
						{
							printf("Do you want to reset your password?(enter y to proceed to reset):");
							scanf(" %c",&ans);
							while (ans != 'y' && ans != 'n')
							{
								printf("Invalid entry\n");
								printf("Please reenter y or n :");
								scanf(" %c", &ans);
							} 
							if (ans=='y')
							{
								system("cls");
								rewind(stdin);
								pwRecover();
							}
							else
							system("cls");
						}
						system("cls");
						break;
					}
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
		printf("Proceeding to ADMIN registration.\n");
		system("pause");
		system("cls");
	}
}

int checkPosition()
{
	int totstaff = readStfList();
	int position = -1;

	if (totstaff != 0)
	{
		if (strcmp(loggedinstf.stfPosi, "ADMIN") == 0)//For admin
		{
			position = 0;
		}
		else
		{
			position = 1;
		}
		return position;
	}
	else {
		return 0;
	}
}


void pwRecover()
{
	FILE*stfopen;
	stfopen = fopen(staffFilePath, "rb");
	char staffIDEntered[30], ans, newpw[100], newconpw[100];
	int totstaff = 0, i = 0, stfcount = 0, stafffound = 0, staffadd = 0;
	totstaff = readStfList();
	printf("%25s====================================================================\n", "");
	printf("%25s|%24sPASSWORD RECOVERER%24s|\n", "", "", "");
	printf("%25s|%4s**YOU NEED TO ENTER YOUR STAFF ID TO CHANGE YOUR PASSWORD**%3s|\n", "", "", "");
	printf("%25s|%9sASK AN ADMIN FOR HELP IF YOU FORGOT YOUR STAFFID%9s|\n", "", "", "");
	printf("%25s====================================================================\n", "");
	do
	{
		printf("Enter staff ID :");
		scanf("%[^\n]", staffIDEntered);
		rewind(stdin);
		for (i = 0; i < totstaff; i++)
		{
			stfcount++;
			if (strcmp(staffIDEntered, staffCache[i].stfID) == 0)
			{
				printf("%25s====================================================================\n", "");
				printf("%25s|%28sSTAFF LIST%28s|\n", "", "", "");
				printf("%25s====================================================================\n", "");
				printf("%25s|Name :%-60s|\n%25s|ID :%-62s|\n%25s|Position :%-56s|\n", "", staffCache[i].stfName, "", staffCache[i].stfID, "", staffCache[i].stfPosi);
				printf("%25s====================================================================\n", "");
				stafffound = 1;
				staffadd = i;
				break;
			}
			else if (stfcount >= totstaff)
			{
				printf("There's no such person please reenter staff ID.\n");
				printf("Enter y to return to log in or n to reenter ID :");
				scanf("%c", &ans);
				while (ans != 'y' && ans != 'n')
				{
					printf("Invalid entry\n");
					printf("Please reenter y or n :");
					scanf(" %c", &ans);
				}
				rewind(stdin);
				if (ans == 'y')
				{
					printf("Returning to login.\n");
					system("pause");
					system("cls");
					fclose(stfopen);
					return;
				}
			}
		}
	} while (stafffound != 1);

	printf("Enter new password(MINUMUM 8):");
	collectCensoredInput(newpw, 99);
	rewind(stdin);
	while (strlen(newpw) < 8)
	{
		printf("Password too short please reenter : \n");
		collectCensoredInput(newpw, 99);
		rewind(stdin);
	}
	printf("Reenter password to confirm :");
	collectCensoredInput(newconpw, 99);
	rewind(stdin);
	while (strcmp(newconpw,newpw) != 0)
	{
		printf("Passwords does not match please reenter !\n");
		rewind(stdin);
		printf("Enter staff Passwords(MINIMUM 8) :");
		collectCensoredInput(newpw, 99);
		rewind(stdin);
		while (strlen(newpw) < 8)
		{
			printf("password too short please reenter : \n");
			printf("Enter staff Passwords(MINIMUM 8): ");
			collectCensoredInput(newpw, 99);;
			rewind(stdin);
		}
		printf("Reenter password to confirm :");
		collectCensoredInput(newconpw, 99);
		rewind(stdin);
	}
	printf("Here's your new password :%s\n",newpw);
	printf("Do you want to make the change?(y to make change n to cancel changes) :");
	scanf("%c", &ans);
	while (ans != 'y' && ans != 'n')
	{
		printf("Invalid entry\n");
		printf("Please reenter y or n :");
		scanf(" %c", &ans);
	}
	rewind(stdin);
	if (ans == 'y')
	{
		Date sysDate;
		getSystemDate(&sysDate);
		printf("Date:%.02d/%.02d/%d\n", sysDate.d, sysDate.m, sysDate.y);
		staffCache[staffadd].dateModi = sysDate;
		strcpy(staffCache[staffadd].stfPassW, newpw);
		stfopen = fopen(staffFilePath, "wb");
		for (int a = 0; a < totstaff; a++)
		{
			fwrite(&staffCache[a], sizeof(Staff), 1, stfopen);
		}
		fclose(stfopen);
		printf("changes have been made proceding to log in.\n");
		system("pause");
		return;
	}
	else
	{
		printf("Changes was canceled proceeding back to log in.\n");
		fclose(stfopen);
		system("pause");
		return;
	}
}

void staffMain()
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

	login();
	do
	{
		int position = checkPosition();

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
			if (position == 0)
			{
				int r = addStaffList(); // addStaffList() return 0 if it wish to exit staff module due to some odd reasons
				if (!r)
				{
					return;
				}

			}
			else
			{
				printf("Only admins are allowed this feature.\n");
				system("pause");
				break;
			}
			break;
		case 3:
			staffSearchName();
			break;
		case 4:
			if (position == 0)
			{
				int r =changeStfList();
				if (!r)
				{
					return;
				}
			}
			else
			{
				printf("Only admins are allowed this feature.\n");
				system("pause");
				break;
			}
			break;
		case 5:
			return;
		default:
			break;
		}
	} while (choice != 5);
}
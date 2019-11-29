#include "userinfo.h"
#include "stdcxx.h"

void registerInfo()

{
	
	int x = 0, i = 0;
	char confirmpass[15], confirmation;
	userData userData1[100];
	FILE * userinfo, *count;
	char id[16];


	count = fopen("count.dat", "rb");

	if (chkFileExist(count))
	{
		fread(&i, sizeof(i), 1, count);
	}



	userinfo = fopen("userInfo.dat", "ab");
	if (userinfo == NULL)
	{
		printf("File doesnt exist\n");
			system("pause");
			return;
	}

	printf("Enter your user ID(4 characters) = ");
	rewind(stdin);
	scanf("%s", userData1[i].id);
	while (strlen(userData1[i].id) != 4)
	{

		if (strlen(id) != 4)
		{
			printf("Enter a id that is 4 characters  = ");
			rewind(stdin);
			scanf("%s", userData1[i].id);
		}


	}


	printf("Enter your name = ");

	rewind(stdin);
	scanf("%[^\n]", userData1[i].name);



	printf("Enter your password = ");
	rewind(stdin);
	scanf("%s", userData1[i].password);

	printf("Renter your password = ");
	rewind(stdin);
	scanf("%s", confirmpass);
	while (strcmp(userData1[i].password, confirmpass) != 0)
	{
		printf("password doesnt match pls retype new password = ");
		rewind(stdin);
		scanf("%s", userData1[i].password);

		printf("Renter your password = ");
		rewind(stdin);
		scanf("%s", confirmpass);

	}

	printf("Enter your gender (M = male,F = Female,O = other = ");
	rewind(stdin);
	scanf("%c", &userData1[i].gender);

	while (toupper(userData1[i].gender) != 'M' && toupper(userData1[i].gender) != 'F')
	{
		printf("Pls enter only M(Male) or F(Female) = ");
		rewind(stdin);
		scanf("%c", &userData1[i].gender);

	}


	printf("Enter your contact number : ");
	rewind(stdin);
	scanf("%s", &userData1[i].contact);
	
	
	printf("Confirm info to register?(Y = yes,N = No) =");
	while (x == 0)
	{
		rewind(stdin);
		scanf("%c", &confirmation);
		if (toupper(confirmation) == 'Y')
		{
			printf("User has been regis congrats and enjoy your day\n");
			fwrite(&userData1, sizeof(userData), 1, userinfo);
			fclose(userinfo);
			x = 1;
		}
		else if (toupper(confirmation) == 'N')
		{
			x = 1;
			printf("User has not been regis congrats and enjoy your day\n");
			return;
		}
		else
		{
			printf("Pls type Y or N = ");

		}

	}


	++i;

	count = fopen("count.dat", "wb");
	fwrite(&i, sizeof(i), 1, count);
	fclose(count);
}

void modifyInfo()
{
	int x = 0;
	int i = 0;
	char id[16];
	char Pass[20];
	char newPass[20];
	char chckPass[20];
	char newID[20];
	char chckID[20];
	char newContact[20];
	char chckContact[20];

	userData user1[100];
	FILE *userinfo1;
	userinfo1 = fopen("userinfo.dat", "rb");

	while (!chkFileExist(userinfo1))
	{
		printf("File userinfo doesnt exist\n");
		system("pause");
		return;
	}
	userinfo1 = fopen("userinfo.dat", "rb");
	

	
	fread(&user1, sizeof(userData), 1, userinfo1);

	printf("Enter id   = ");
	rewind(stdin);
	scanf("%s", id);

	printf("Enter password = ");
	rewind(stdin);
	scanf("%s", Pass);
	for (i = 0; i < 100; i++) {
		if (strcmp(user1[i].id, id) == 0 && strcmp(user1[i].password, Pass) == 0)
		{
			printf("__________________________\n");
			printf("Modify Info Module\n");
			printf("__________________________\n");
			printf("1. Change ID\n");
			printf("2. Change Password\n");
			printf("3. Change Contact Number\n");
			printf("4. Exit\n");
			printf("\nMenu Choice: ");
			userinfo1 = fopen("userinfo.dat", "wb");
			char choice[6];
			getUserMenuChoice(choice, 6, "Menu Choice: ");
			switch (choice[0])
			{
			case '1':
				while (1)
				{
					printf("Enter new id = ");
					rewind(stdin);
					scanf("%s", newID);

					printf("Enter again ID for checking = ");
					rewind(stdin);
					scanf("%s", chckID);

					if (strcmp(newID, chckID) != 0)
					{
						printf("ID is not same\n");
						return ;

					}
					else if (strcmp(newID, chckID) == 0)
					{

						printf("ID is same\n");
						strcpy(user1[i].id, newID);
						fwrite(&user1[i], sizeof(userData), 1, userinfo1);
						fclose(userinfo1);
						return;

					}
				}
				break;
			case '2':
				while (1)
				{
					printf("Enter new password = ");
					rewind(stdin);
					scanf("%s", newPass);

					printf("Enter again password for checking = ");
					rewind(stdin);
					scanf("%s", chckPass);

					if (strcmp(newPass, chckPass) != 0)
					{
						printf("Password is not same\n");
						return;

					}
					else if (strcmp(newPass, chckPass) == 0)
					{

						printf("Password is same\n");
						strcpy(user1[i].password, newPass);
						fwrite(&user1[i], sizeof(userData), 1, userinfo1);
						fclose(userinfo1);
						return;

					}
				}

				break;
			case '3':while (1)
			{
				printf("Enter new contact number = ");
				rewind(stdin);
				scanf("%s", newContact);

				printf("Enter again contact number for checking = ");
				rewind(stdin);
				scanf("%s", newContact);

				if (strcmp(newContact, chckContact) != 0)
				{
					printf("Contact Number is not same\n");
					return;

				}
				else if (strcmp(newContact, chckContact) == 0)
				{

					printf("Contact Number is same\n");
					strcpy(user1[i].contact,newContact);
					fwrite(&user1[i], sizeof(userData), 1, userinfo1);
					fclose(userinfo1);
					return;

				}
			}
				
				break;
			case '4':return;
				break;
			default:
				return;















			}
		}
	}
}


void displayInfo()
{

	userData user1;
	FILE *userinfo1;
	userinfo1 = fopen("userinfo.dat", "rb");

	while (userinfo1 == NULL)
	{
		printf("File userinfo doesnt exist\n");
		return;
	}
	
	

	while (fread(&user1, sizeof(userData), 1, userinfo1) != 0) {
		printf("Name  %s\n", user1.name);
		printf("Gender is %c\n", user1.gender);
		printf("Contact number is %s\n", user1.contact);
	}
system("pause");
return;
}


void searchInfo()
{
	int i = 0;
	char id[15];
	char password[20];
	userData user1[100];
	FILE *userinfo1;
	userinfo1 = fopen("userinfo.dat", "rb");

	while (!chkFileExist(userinfo1))
	{
		printf("File userinfo doesnt exist\n");
		return;
	}

	
	fread(&user1, sizeof(userData), 1, userinfo1);
	

	printf("Enter your user ID(4 characters) = ");
	rewind(stdin);
	scanf("%s", id);
	while (strlen(id) != 4)
	{

		if (strlen(id) != 4)
		{
			printf("Enter a id that is 4 characters  = ");
			rewind(stdin);
			scanf("%s", id);
		}


	}



	printf("Enter user password = ");
	rewind(stdin);
	scanf("%s", password);
	while (1)
	{
		for (i = 0; i < 100; i++) {
			if (strcmp(user1[i].id, id) == 0 && strcmp(user1[i].password, password) == 0)
			{

				printf("Name = %s\n", user1[i].name);
				printf("ID   = %s\n", user1[i].id);
				printf("Password = %s\n", user1[i].password);
				printf("Gender is = %c\n", user1[i].gender);
				printf("Contact number is = %s\n", user1[i].contact);
				system("pause");

				


			}
			else if ((strcmp(user1[99].id, id) != 0 || strcmp(user1[99].password, password) != 0) && i == 99)
			{
				printf("User id or password is incorrect\n");
				printf("Enter user id again = ");
				rewind(stdin);
				scanf("%s", id);
				while (strlen(id) != 4)
				{

					if (strlen(id) !=4)
					{
						printf("Enter a id that is between 4 char(-1 to exit)  = ");
						rewind(stdin);
						scanf("%s", id);
					}

				}

				printf("Enter user password = ");
				rewind(stdin);
				scanf("%s", password);
			}
		}
	}
}

void userInfo()
{
	system("cls");
	printf("\t\t\t\t\t\t__________________________\n");
	printf("\t\t\t\t\t\tRegisteration\\Login Module\n");
	printf("\t\t\t\t\t\t__________________________\n");
	printf("\t\t\t\t\t\t1. Register As A New User\n");
	printf("\t\t\t\t\t\t2. Change Password\n");
	printf("\t\t\t\t\t\t3. Search Personal User Info\n");
	printf("\t\t\t\t\t\t4. Display all the user Info\n");
	printf("\t\t\t\t\t\t5. Exit\n");
	printf("\n\t\t\t\t\t\tMenu Choice: ");

	char choice[6];
	getUserMenuChoice(choice, 6, "Menu Choice: ");
	switch (choice[0])
	{
	case '1':registerInfo();
		break;
	case '2': modifyInfo();
		break;
	case '3':searchInfo();
		break;
	case '4':displayInfo();
		break;
	case '5':return ;
		break;
	default:
		return ;
	}

	return ;
}

void userinfoMain() {
	sprintf(UserInfoFilePath, "%s\\%s", APPDATA_PATH, "userinfo.dat");
	 userInfo();

}
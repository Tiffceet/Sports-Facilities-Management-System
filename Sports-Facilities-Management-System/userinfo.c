#include "userinfo.h"
#include "stdcxx.h"

void registerInfo()

{
	//Finding a way on how to make "i" as a variable increment on every run to store data
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
	if (chkFileExist(userinfo))
	{
		printf("File doesnt exist\n");
			system("pause");
			return;
	}


	printf("Enter your user ID(8 - 15 characters) = ");
	rewind(stdin);
	scanf("%s", userData1[i].id);
	while (strlen(userData1[i].id) < 8 || strlen(userData1[i].id) > 15)
	{

		if (strlen(id) < 8 || strlen(id) > 15)
		{
			printf("Enter a id that is between 8 to 15 words(-1 to exit)  = ");
			rewind(stdin);
			scanf("%s", userData1[i].id);
		}

		else
		{
			printf("Enter a id that hasnt been taken(-1 to exit)  = ");
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
	for (x = 0; x < strlen(userData1[i].contact); x++)
	{
		if (!isdigit(userData1[i].contact[x]))
		{
			printf("Enter your correct contact number : ");
			rewind(stdin);
			scanf("%s", &userData1[i].contact);
			x = 0;
		}
	}
	x = 0;
	rewind(stdin);
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
	for (i = 0; i < 100; i++)
	{
		fread(&user1[i], sizeof(userData), 1, userinfo1);
	}
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
			printf("1. Change ID\n \n");
			printf("2. Change Password\n");
			printf("3. Change Contact Number\n");
			printf("4. Exit\n");
			printf("\nMenu Choice: ");

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
						return 0;

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
						return 0;

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
					return 0;

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
				return 1;















			}
		}
	}
}


void displayInfo()
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
	
	for (i = 0; i < 100; i++)
	{
		fread(&user1[i], sizeof(userData), 1, userinfo1);
	}

i = searchInfo();
				
printf("Your id is %s\n", user1[i].id);
printf("Your name is %s\n", user1[i].name);
printf("Your gender is %c\n", user1[i].gender);
printf("Your contact number is %s\n", user1[i].contact);
system("pause");
return;
}


int searchInfo()
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

	for (i = 0; i < 100; i++)
	{
		fread(&user1[i], sizeof(userData), 1, userinfo1);
	}


	printf("Enter user id = ");
	rewind(stdin);
	scanf("%s", id);
	while (strlen(id) < 8 || strlen(id) > 15)
	{

		if (strlen(id) < 8 || strlen(id) > 15)
		{
			printf("Enter a id that is between 8 to 15 words(-1 to exit)  = ");
			rewind(stdin);
			scanf("%s",id);
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


				return i;


			}
			else if ((strcmp(user1[i].id, id) != 0 || strcmp(user1[i].password, password) != 0) && i == 99)
			{
				printf("User id or password is incorrect\n");
				printf("Enter user id again = ");
				rewind(stdin);
				scanf("%s", id);
				while (strlen(id) < 8 || strlen(id) > 15)
				{

					if (strlen(id) < 8 || strlen(id) > 15)
					{
						printf("Enter a id that is between 8 to 15 words(-1 to exit)  = ");
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

	printf("__________________________\n");
	printf("Registeration\\Login Module\n");
	printf("__________________________\n");
	printf("1. Register As A New User\n \n");
	printf("2. Change Password\n");
	printf("3. Search User Info\n");
	printf("4. Exit\n");
	printf("\nMenu Choice: ");

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
	case '4':return 1;
		break;
	default:
		return 1;
	}

	return 1;
}

void userinfoMain() {
	sprintf(UserInfoFilePath, "%s\\%s", APPDATA_PATH, "userinfo.dat");
	void userInfo();

}
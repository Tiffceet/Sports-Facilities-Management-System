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


	userinfo = fopen("userInfo.dat", "ab");
	printf("Enter your user ID(8 - 15 characters) = ");
	rewind(stdin);
	scanf("%s", userData1[i].id);
	while (strlen(userData1[i].id) < 8 || strlen(userData1[i].id) > 15)
	{

		if (strlen(id) < 8 || strlen(id) > 15)
		{
			printf("Enter a id that is between 8 to 15 words(-1 to exit)  = ");
			scanf("%s", userData1[i].id);
		}

		else
		{
			printf("Enter a id that hasnt been taken(-1 to exit)  = ");
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
}

void modifyInfo()
{
	int x = 0;
	int i = 0;
	char id[16];
	char currentPass[20];
	char newPass[20];
	char chckPass[20];
	userData user1[100];
	FILE *userinfo1;


	while ((userinfo1 = fopen("userinfo.dat", "rb")) == NULL)
	{
		printf("File userinfo doesnt exist\n");
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
	scanf("%s", currentPass);
	for (i = 0; i < 100; i++) {
		if (strcmp(user1[i].id, id) == 0 && strcmp(user1[i].password, currentPass) == 0)
		{
			while (x == 0)
			{
				printf("Enter new password = ");
				scanf("%s", newPass);

				printf("Enter again password for checking = ");
				scanf("%s", chckPass);

				if (strcmp(newPass, chckPass) != 0)
				{
					printf("Password is not same\n");

				}
				else if (strcmp(newPass, chckPass) == 0)
				{

					printf("Password is same\n");
					x = 1;
				}
			}
		}
	}

	strcpy(user1[i].password, newPass);
	fwrite(&user1[i], sizeof(userData), 1, userinfo1);
	fclose(userinfo1);

	return;

}


void displayInfo()
{
	int i = 0;
	char id[15];
	char password[20];
	userData user1[100];
	FILE *userinfo1;


	while ((userinfo1 = fopen("userinfo.dat", "rb")) == NULL)
	{
		printf("File userinfo doesnt exist\n");
		return;
	}
	userinfo1 = fopen("userinfo.dat", "rb");
	for (i = 0; i < 100; i++)
	{
		fread(&user1[i], sizeof(userData), 1, userinfo1);
	}

	printf("Enter user id = ");
	scanf("%s", id);

	printf("Enter user password = ");
	scanf("%s", password);

	for (i = 0; i < 100; i++)
	{
		if (strcmp(user1[i].id, id) == 0 && strcmp(user1[i].password, password) == 0)
		{
			printf("Your id is %s ", user1[i].id);
			printf("Your name is %s ", user1[i].name);
			printf("Your gender is %c ", user1[i].gender);
			printf("Your contact number is %s", user1[i].contact);
		}


	}





}


void searchInfo()
{







}

void userInfo()
{

	printf("__________________________\n");
	printf("Registeration\\Login Module\n");
	printf("__________________________\n");
	printf("1. Register As A New User\n \n");
	printf("2. Change Password\n");
	printf("3. Display User Info\n");
	printf("4. Search user\n");
	printf("5. Exit\n");
	printf("\nMenu Choice: ");

	char choice[6];
	getUserMenuChoice(choice, 6, "Menu Choice: ");
	switch (choice[0])
	{
	case '1':registerInfo();
		break;
	case '2': modifyInfo();
		break;
	case '3':displayInfo();
		break;
	case '4':
		break;
	case '5':return 0;
		break;
	default:
		return 1;
	}

	return 1;
}

void userinfoMain() {}
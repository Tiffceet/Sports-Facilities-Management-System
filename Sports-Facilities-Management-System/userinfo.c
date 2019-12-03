#include "userinfo.h"
#include "stdcxx.h"



int totalNumUser()
{
	int i = 0;
	FILE * userinfo1;
	userinfo1 = fopen(UserInfoFilePath, "rb");

\	while (fread(&user1, sizeof(userData), 1, userinfo1) != 0)
	{


		i++;
	}

	return i;
}

void registerInfo()

{

	int x = 0, i = 0;
	char confirmpass[15], confirmation;
	userData userData1;
	FILE * userinfo;
	char id[16];
	char nameChck[20];




	userinfo = fopen(UserInfoFilePath, "ab");
	/*if (!chkFileExist(userinfo))
	{
		printf("File doesnt exist\n");
		userinfo = fopen(UserInfoFilePath, "ab");
	} else{
		fclose(userinfo);
		userinfo = fopen(UserInfoFilePath, "ab");
	}*/
	
	printf("Enter your user ID(4 characters) = ");
	rewind(stdin);
	scanf("%s", userData1.id);
	while (strlen(userData1.id) != 4)
	{

		if (strlen(id) != 4)
		{
			printf("Enter a id that is 4 characters  = ");
			rewind(stdin);
			scanf("%s", userData1.id);
		}


	}


	printf("Enter your name = ");
	rewind(stdin);
	scanf("%[^\n]", userData1.name);
	strcpy(nameChck, userData1.name);
	for (i = 0; i < strlen(nameChck); i++)
	{
		while (isalpha(nameChck[i]) == 0 )
		{
			printf("Please enter alphabets only.\n");
			printf("Please enter your name (without spacing):  ");
			rewind(stdin);
			scanf("%[^\n]", &nameChck);
			i = 0;
		}
	}
	strcpy(userData1.name, nameChck);
	
	
	
	printf("Enter your password(minimum 6 - 12) = ");
	rewind(stdin);
	scanf("%s", userData1.password);
	while (strlen(userData1.password) < 6 || strlen(userData1.password) > 12  )
	{

		if (strlen(userData1.password) < 6 || strlen(userData1.password) > 12 )
		{
			printf("Enter the password with at least minimum 6 - 12 words = ");
			rewind(stdin);
			scanf("%s", userData1.password);
		}


	}

	printf("Renter your password = ");
	rewind(stdin);
	scanf("%s", confirmpass);
	while (strcmp(userData1.password, confirmpass) != 0)
	{
		printf("password doesnt match pls retype new password = ");
		rewind(stdin);
		scanf("%s", userData1.password);

		printf("Renter your password = ");
		rewind(stdin);
		scanf("%s", confirmpass);

	}

	printf("Enter your gender (M = male,F = Female,O = other = ");
	rewind(stdin);
	scanf("%c", &userData1.gender);

	while (toupper(userData1.gender) != 'M' && toupper(userData1.gender) != 'F')
	{
		printf("Pls enter only M(Male) or F(Female) = ");
		rewind(stdin);
		scanf("%c", &userData1.gender);

	}


	printf("Enter your contact number : ");
	rewind(stdin);
	scanf("%s", &userData1.contact);


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
			system("pause");
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
void modifyInfo2()
{
	char s[20];
	char pass[20];
	int i = 0;
	int x = 0;
	FILE *userinfo1;
	userinfo1 = fopen(UserInfoFilePath, "rb");
	x = totalNumUser();
	while (userinfo1 == NULL)
	{
		printf("File userinfo doesnt exist\n");
		system("pause");
		return;
	}
	for (i = 0; i < x; i++) {
		fread(&user2[i], sizeof(userData), 1, userinfo1);
	}


	printf("Enter Id = ");
	scanf("%s", s);

	printf("Enter Password = ");
	scanf("%s", pass);

	for (i = 0; i < x; i++)
	{
		if ((strcmp(user2[i].id, s) == 0) && (strcmp(user2[i].password, pass) == 0))
		{
			printf("__________________________\n");
			printf("Modify Info Module\n");
			printf("__________________________\n");
			printf("1. Change ID\n");
			printf("2. Change Password\n");
			printf("3. Change Contact Number\n");
			printf("4. Exit\n");
			printf("\nMenu Choice: ");

			char choice[6];
			getUserMenuChoice(choice, 6, "Menu Choice: ");
			switch (choice[0])
			{
			case '1':userinfo1 = fopen(UserInfoFilePath, "wb");

				printf("Enter new ID = ");
				scanf("%s", s);
				strcpy(user2[i].id, s);

				for (i = 0; i < x; i++) {
					fwrite(&user2[i], sizeof(userData), 1, userinfo1);
				}
				fclose(userinfo1);
				system("pause");
				break;
			case '2':userinfo1 = fopen(UserInfoFilePath, "wb");

				printf("Enter new password = ");
				scanf("%s", s);
				strcpy(user2[i].password, s);

				for (i = 0; i < x; i++) {
					fwrite(&user2[i], sizeof(userData), 1, userinfo1);
				}
				fclose(userinfo1);
				system("pause");
				break;
			case '3':

				userinfo1 = fopen(UserInfoFilePath, "wb");

				printf("Enter new contact = ");
				scanf("%s", s);
				strcpy(user2[i].contact, s);

				for (i = 0; i < x; i++) {
					fwrite(&user2[i], sizeof(userData), 1, userinfo1);
				}
				fclose(userinfo1);
				system("pause");
				break;
			}
		}

	}
}





void displayInfo()
{
	char s[20];
	int i = 0;
	int x = 0;
	FILE *userinfo1;
	userinfo1 = fopen(UserInfoFilePath, "rb");
	x = totalNumUser();
	while (userinfo1 == NULL)
	{
		printf("File userinfo doesnt exist\n");
		system("pause");
		return;
	}
	for (i = 0; i < x; i++) {
		fread(&user2[i], sizeof(userData), 1, userinfo1);
	}
	for (i = 0; i < x; i++)
	{
		printf("Name  %s\n", user2[i].name);
		printf("Gender is %c\n", user2[i].gender);
		printf("Contact number is %s\n", user2[i].contact);
		printf("\n");
	}
	fclose(userinfo1);
	system("pause");
}


void searchInfo()
{
	int i = 0;
	char id[15];
	char password[20];
	userData user1;
	FILE *userinfo1;
	userinfo1 = fopen(UserInfoFilePath, "rb");

	while (!chkFileExist(userinfo1))
	{
		printf("File userinfo doesnt exist\n");
		return;
	}





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
	while (fread(&user1, sizeof(userData), 1, userinfo1) != 0)
	{

		if (strcmp(user1.id, id) == 0 && strcmp(user1.password, password) == 0)
		{

			printf("Name = %s\n", user1.name);
			printf("ID   = %s\n", user1.id);
			printf("Password = %s\n", user1.password);
			printf("Gender is = %c\n", user1.gender);
			printf("Contact number is = %s\n", user1.contact);
			system("pause");
			return;




		}


	}
}

void userInfo()
{
	/*system("cls");
	printf("\t\t\t\t\t\t__________________________\n");
	printf("\t\t\t\t\t\tRegisteration\\Login Module\n");
	printf("\t\t\t\t\t\t__________________________\n");
	printf("\t\t\t\t\t\t1. Register As A New User\n");
	printf("\t\t\t\t\t\t2. Modify User Info\n");
	printf("\t\t\t\t\t\t3. Search Personal User Info\n");
	printf("\t\t\t\t\t\t4. Display all the user Info\n");
	printf("\t\t\t\t\t\t5. Exit\n");
	printf("\n\t\t\t\t\t\tMenu Choice: ");*/

	char choiceText[][100] = { "Registration For New User", "Changing User Info", "Search Details Of User", "Display All The User In Database", "Exit" };
	int choice = globalMainMenu("^_^ USERINFO MODULE ^_^", 5, choiceText);
	switch (choice)
	{
	case 1:registerInfo();
		break;
	case 2: modifyInfo2();
		break;
	case 3:searchInfo();
		break;
	case 4:displayInfo();
		break;
	case 5:return;
		break;
	default:
		return;
	}

	return;
}

void userinfoMain() {
	sprintf(UserInfoFilePath, "%s\\%s", APPDATA_PATH, UserInfoFilePath);
	userInfo();

}
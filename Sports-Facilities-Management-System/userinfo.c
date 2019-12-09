#include "userinfo.h"
#include "stdcxx.h"

int uniqueId(char id[15])
{
	char s[20];
	int i = 0;
	int x = 0;

	FILE *userinfo1;
	userinfo1 = fopen(UserInfoFilePath, "rb");
	if (!chkFileExist(userinfo1))
	{
		printf("File userinfo doesnt exist\n");

	}

	x = totalNumUser();
	for (i = 0; i < x; i++) {
		fread(&user2[i], sizeof(userData), 1, userinfo1);
	}

	int c = 0;
	for (i = 0; i < x; i++) {

		strcpy(s, user2[i].name);


		if (strcmp(id, s) == 0)
		{
			c = 1;
			return c;
		}
		else if (i + 1 == x)
		{
			c = 0;
			return c;

		}

	}





}

int totalNumUser()
{
	int x = 0;
	int i = 0;
	FILE * userinfo1;
	userinfo1 = fopen(UserInfoFilePath, "rb");
	if (!chkFileExist(userinfo1))
	{
		printf("First registration\n");
	}

	while (fread(&user1, sizeof(userData), 1, userinfo1) != 0)
	{


		i++;
	}

	return i;
}
int exitProgram(char quit[10])
{
	char s[10] = { "exit" };
	int a = 1;
	if (strcmp(s, quit) == 0)
	{
		return a;

	}
	else
	{
		a = 0;
		return a;
	}

}
void registerInfo()

{
	char exitProg[10];
	int unique = 0;
	int x = 0, i = 0;
	int totalUser = 0;
	int programExit = 0;
	char confirmpass[15], confirmation;
	userData userData1;
	FILE * userinfo;
	char id[16];
	char nameChck[20];
	char chckContact[20];




	userinfo = fopen(UserInfoFilePath, "ab");
	if (userInfo == NULL)
	{
		printf("File userinfo can't be created\n");
		system("pause");
		return;
	}
	printf("Type exit  if you wanna cancle registration process\n");
	printf("Enter your user ID(4 characters) = ");
	rewind(stdin);
	scanf("%s", userData1.id);
	strcpy(exitProg, userData1.id);
	programExit = exitProgram(exitProg);
	if (programExit == 1)
	{
		fclose(userinfo);
		return;
	}
	x = totalNumUser();
	if (x != 0)
	{
		unique = uniqueId(userData1.id);
	}
	x = 0;

	while (unique == 1)
	{
		printf("The user id has been taken pls kindly choose another id :) = ");
		scanf("%s", userData1.id);
		strcpy(exitProg, userData1.id);
		programExit = exitProgram(exitProg);
		if (programExit == 1)
		{
			fclose(userinfo);
			return;
		}
		unique = uniqueId(userData1.id);
		while (strlen(userData1.id) != 4)
		{


			if (strlen(id) != 4)
			{
				printf("Enter a id that has 4 characters  = ");
				rewind(stdin);
				scanf("%s", userData1.id);
				strcpy(exitProg, userData1.id);
				programExit = exitProgram(exitProg);
				if (programExit == 1)
				{
					fclose(userinfo);
					return;
				}

			}

		}
		unique = uniqueId(userData1.id);

	}
	while (strlen(userData1.id) != 4)
	{

		if (strlen(id) != 4)
		{
			printf("Enter a id that has 4 characters  = ");
			rewind(stdin);
			scanf("%s", userData1.id);
			strcpy(exitProg, userData1.id);
			programExit = exitProgram(exitProg);
			if (programExit == 1)
			{
				fclose(userinfo);
				return;
			}

		}

	}



	printf("Enter your name = ");
	rewind(stdin);
	scanf("%[^\n]", userData1.name);
	strcpy(exitProg, userData1.name);
	programExit = exitProgram(exitProg);
	if (programExit == 1)
	{
		fclose(userinfo);
		return;
	}
	strcpy(nameChck, userData1.name);
	for (i = 0; i < strlen(nameChck); i++)
	{
		while (isalpha(nameChck[i]) == 0)
		{
			printf("Please enter alphabets only.\n");
			printf("Please enter your name (without spacing):  ");
			rewind(stdin);
			scanf("%[^\n]", &nameChck);

			strcpy(exitProg, nameChck);
			programExit = exitProgram(exitProg);
			if (programExit == 1)
			{
				fclose(userinfo);
				return;
			}
			i = 0;
		}
	}
	strcpy(userData1.name, nameChck);



	printf("Enter your password(minimum 6) = ");
	rewind(stdin);
	scanf("%s", userData1.password);
	strcpy(exitProg, userData1.password);
	programExit = exitProgram(exitProg);
	if (programExit == 1)
	{
		fclose(userinfo);
		return;
	}
	while (strlen(userData1.password) < 6 )
	{

		if (strlen(userData1.password) < 6 )
		{
			printf("Enter the password with at least minimum 6 words = ");
			rewind(stdin);
			scanf("%s", userData1.password);
			strcpy(exitProg, userData1.password);
			programExit = exitProgram(exitProg);
			if (programExit == 1)
			{
				fclose(userinfo);
				return;
			}
		}


	}

	printf("Renter your password = ");
	rewind(stdin);
	scanf("%s", confirmpass);
	programExit = exitProgram(confirmpass);
	if (programExit == 1)
	{
		fclose(userinfo);
		return;
	}
	while (strcmp(userData1.password, confirmpass) != 0)
	{
		printf("password doesnt match pls retype new password = ");
		rewind(stdin);
		scanf("%s", userData1.password);
		strcpy(exitProg, userData1.password);
		programExit = exitProgram(exitProg);
		if (programExit == 1)
		{
			fclose(userinfo);
			return;
		}

		printf("Renter your password = ");
		rewind(stdin);
		scanf("%s", confirmpass);
		programExit = exitProgram(confirmpass);
		if (programExit == 1)
		{
			fclose(userinfo);
			return;
		}

	}

	printf("Enter your gender (M = male,F = Female,O = other = ");
	rewind(stdin);
	scanf("%s", &userData1.gender);


	


	printf("Enter your contact number : ");
	rewind(stdin);
	scanf("%s", &userData1.contact);
	strcpy(exitProg, userData1.contact);
	programExit = exitProgram(exitProg);
	if (programExit == 1)
	{
		fclose(userinfo);
		return;
	}
	
	printf("Confirm info to register?(Y = yes,N = No) =");
	while (x == 0)
	{
		rewind(stdin);
		scanf("%c", &confirmation);
		if (toupper(confirmation) == 'Y')
		{
			Date date;
			Time time;
			getSystemDate(&date);
			getSystemTime(&time);
			printf("User registration date is %d/%d/%d and time of registration is %d:%d\n", date.d, date.m, date.y,time.h,time.m);
			sprintf(userData1.dateRegis, " %d/%d/%d", date.d, date.m, date.y);
			sprintf(userData1.timeRegis, " %d:%d", time.h, time.m);


			printf("User has been regis congrats and enjoy your day\n");
			fwrite(&userData1, sizeof(userData), 1, userinfo);
			fclose(userinfo);
			system("pause");
			x = 1;
			return;
		}
		else if (toupper(confirmation) == 'N')
		{
			x = 1;
			fclose(userinfo);
			printf("User has not been regis congrats and enjoy your day\n");
			system("pause");
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
	char confirmation;
	char check;
	char choice[6];
	char exit;
	char s[20];
	char pass[20];
	int v = 0;
	int i = 0;
	int x = 0;
	char exitProg[20];
	int programExit;
	FILE *userinfo1;
	userinfo1 = fopen(UserInfoFilePath, "rb");
	x = totalNumUser();
	while (!chkFileExist(userinfo1))
	{
		printf("File userinfo doesnt exist\n");
		system("pause");
		return;
	}
	for (i = 0; i < x; i++) {
		fread(&user2[i], sizeof(userData), 1, userinfo1);
	}

	while (1)
	{
		printf("Type exit if you wanna return to main module\n");

		printf("Enter Id = ");
		rewind(stdin);
		scanf("%s", s);
		strcpy(exitProg, s);
		programExit = exitProgram(exitProg);
		if (programExit == 1)
		{
			fclose(userinfo1);
			return;
		}
		
		printf("Is the current ID enter is ok?(Y = Yes/N = No)");
		rewind(stdin);
		scanf("%c", &confirmation);
		while (toupper(confirmation) == 'N') 
		{
			if (toupper(confirmation) == 'N')
			{

				printf("Enter Id again = ");
				rewind(stdin);
				scanf("%s", s);
				strcpy(exitProg, s);
				programExit = exitProgram(exitProg);
				if (programExit == 1)
				{
					fclose(userinfo1);
					return;
				}
				printf("Is the current ID enter is ok?(Y = Yes/N = No)");
				rewind(stdin);
				scanf("%c", &confirmation);
			}
		}


		printf("Enter Password = ");
		rewind(stdin);
		scanf("%s", pass);
		strcpy(exitProg, pass);
		programExit = exitProgram(exitProg);
		if (programExit == 1)
		{
			fclose(userinfo1);
			return;
		}
		while (strlen(pass) < 6)
		{

			if (strlen(pass) < 6)
			{
				printf("Enter the password with at least minimum 6 words = ");
				rewind(stdin);
				scanf("%s", pass);
				strcpy(exitProg, pass);
				programExit = exitProgram(exitProg);
				if (programExit == 1)
				{
					fclose(userinfo1);
					return;
				}
			}


		}
		printf("Is the current password is ok?(Y = Yes/N = No)");
		rewind(stdin);
		scanf("%c", &confirmation);
		while (toupper(confirmation) == 'N')
		{
			if (toupper(confirmation) == 'N')
			{

				printf("Enter your password again = ");
				rewind(stdin);
				scanf("%s", pass);
				strcpy(exitProg, pass);
				programExit = exitProgram(exitProg);
				if (programExit == 1)
				{
					fclose(userinfo1);
					return;
				}

				while (strlen(pass) < 6)
				{

					if (strlen(pass) < 6)
					{
						printf("Enter the password with at least minimum 6 words = ");
						rewind(stdin);
						scanf("%s", pass);
						strcpy(exitProg, pass);
						programExit = exitProgram(exitProg);
						if (programExit == 1)
						{
							fclose(userinfo1);
							return;
						}
					}


				}
				printf("Is the current password is ok?(Y = Yes/N = No)");
				rewind(stdin);
				scanf("%c", &confirmation);
			}
		}


		for (i = 0; i < x; i++)
		{
			if ((strcmp(user2[i].id, s) == 0) && (strcmp(user2[i].password, pass) == 0))
			{
				while (1)
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
						v = 1;
						break;
					case '2':userinfo1 = fopen(UserInfoFilePath, "wb");

						printf("Enter new password = ");
						scanf("%s", s);
						strcpy(user2[i].password, s);

						for (i = 0; i < x; i++) {
							fwrite(&user2[i], sizeof(userData), 1, userinfo1);
						}
						fclose(userinfo1);
						v = 1;

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
						v = 1;

						break;

					case '4':return;
						break;

					default:printf("\nPls choose case 1 - 4 only \n");
						break;
					}


					if (v == 1)
					{
						while (1)
						{
							printf("Do you want to do more changes (Y = yes/N = no) = ");
							rewind(stdin);
							scanf("%c", &exit);

							if (toupper(exit) != 'N' || toupper(exit) != 'Y')
							{
								printf("Pls enter either 'Y' or 'N' only \n");
							}

							if (toupper(exit) == 'Y')
							{

								break;
							}
							if (toupper(exit) == 'N')
							{

								return;
							}

						}
					}


				}

			}
			while (i + 1 == x && ((strcmp(user2[i].id, s) != 0) || (strcmp(user2[i].password, pass) != 0)))
			{
				if (strcmp(user2[i].id, s) != 0 && strcmp(user2[i].password, pass) != 0)
				{
					while (1)
					{
						printf("Both Id and Password is wrong \n");

						printf("Do you want to try searching again? (Y = yes/N = no) = ");
						rewind(stdin);
						scanf("%c", &exit);
						if (toupper(exit) == 'Y')
						{

							break;
						}
						if (toupper(exit) == 'N')
						{

							return;
						}
						if (toupper(exit) != 'N' || toupper(exit) != 'Y')
						{
							printf("Pls enter either 'Y' or 'N' only \n");
						}
					}


				}
				else if (strcmp(user2[i].id, s) != 0)
				{
					while (1)
					{
						printf("User Id is wrong\n");

						printf("Do you want to try searcing again(Y = yes/N = no) = ");
						rewind(stdin);
						scanf("%c", &exit);
						if (toupper(exit) == 'Y')
						{

							break;
						}
						if (toupper(exit) == 'N')
						{

							return;
						}
						if (toupper(exit) != 'N' || toupper(exit) != 'Y')
						{
							printf("Pls enter either 'Y' or 'N' only \n");
						}
					}

				}
				else
				{
					while (1)
					{
						printf("Password is wrong \n");

						printf("Do you want to try searcing again (Y = yes/N = no) = ");
						rewind(stdin);
						scanf("%c", &exit);
						if (toupper(exit) == 'Y')
						{

							break;
						}
						if (toupper(exit) == 'N')
						{

							return;
						}
						if (toupper(exit) != 'N' || toupper(exit) != 'Y')
						{
							printf("Pls enter either 'Y' or 'N' only \n");
						}
					}

				}


				break;
			}



		}

	}
}





void displayInfo()
{
	int i = 0;
	int x = 0;
	FILE *userinfo1;
	userinfo1 = fopen(UserInfoFilePath, "rb");
	if (!chkFileExist(userinfo1))
	{
		printf("File userinfo doesnt exist\n");
		system("pause");
		return;

	}


	x = totalNumUser();
	while (!userinfo1)
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
		printf("\t\t*****************************************\n");
		printf("\t\t*Name              = %-19s*\n", user2[i].name);
		printf("\t\t*Gender is         = %-19c*\n", user2[i].gender);
		printf("\t\t*Contact number is = %-19s*\n", user2[i].contact);
		printf("\t\t*Date Of Register  =%-19s *\n", user2[i].dateRegis);
		printf("\t\t*Time Of Register  =%-19s *\n", user2[i].timeRegis);
		printf("\t\t*****************************************\n");
		printf("\n");
	}
	fclose(userinfo1);
	system("pause");
	return;
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
	do {
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
		case 5:
			return;

		default:
			return;
		}
	} while (1);
}

void userinfoMain() {
	

	userInfo();

}
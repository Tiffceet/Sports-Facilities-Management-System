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

		strcpy(s, user2[i].id);


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
	char chckContact[20];




	userinfo = fopen(UserInfoFilePath, "ab");
	if (userInfo == NULL)
	{
		printf("File userinfo can't be created\n");
		system("pause");
		return;
	}

	printf("Enter your user ID only 4 characters(exit to cancle registration)= ");
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


		}

	}



	printf("Enter your name = ");
	rewind(stdin);
	scanf("%[^\n]", userData1.name);

	printf("Enter your password(minimum 6) = ");
	rewind(stdin);
	collectCensoredInput(userData1.password, 99);

	while (strlen(userData1.password) < 6)
	{


		printf("Enter the password with at least minimum 6 words = ");
		rewind(stdin);
		collectCensoredInput(userData1.password, 99);

	}

	printf("Renter your password = ");
	rewind(stdin);
	collectCensoredInput(confirmpass, 99);
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
		collectCensoredInput(userData1.password, 99);
		
		while (strlen(userData1.password) < 6)
		{


			printf("Enter the password with at least minimum 6 words = ");
			rewind(stdin);
			collectCensoredInput(userData1.password, 99);

		}

		printf("Renter your password = ");
		rewind(stdin);
		collectCensoredInput(confirmpass, 99);
		while (strlen(confirmpass) < 6)
		{


			printf("Enter the password with at least minimum 6 words = ");
			rewind(stdin);
			collectCensoredInput(confirmpass, 99);

		}
		

	}

	printf("Enter your gender (M = male,F = Female) = ");
	rewind(stdin);
	scanf("%s", &userData1.gender);
	while (1)
	{
		while (toupper(userData1.gender[0]) != 'M' || toupper(userData1.gender[0]) != 'F')
		{
			if (toupper(userData1.gender[0]) == 'M' || toupper(userData1.gender[0]) == 'F')
			{
				break;
			}
			printf("Either type M or F only\n");
			printf("Enter your gender (M = male,F = Female) = ");
			rewind(stdin);
			scanf("%s", &userData1.gender);

		}

		while (strlen(userData1.gender) > 1)
		{
			printf("Either type M or F only\n");
			printf("Enter your gender (M = male,F = Female) = ");
			rewind(stdin);
			scanf("%s", &userData1.gender);


		}
		if ((toupper(userData1.gender[0]) == 'M' && strlen(userData1.gender) == 1) || (toupper(userData1.gender[0]) == 'F' && strlen(userData1.gender) == 1))
		{
			break;
		}

	}
	printf("Enter your contact number : ");
	rewind(stdin);
	scanf("%s", &userData1.contact);
	for (i = 0; i < strlen(userData1.contact); i++)
	{
		while (isdigit(userData1.contact[i]) == 0)
		{
			printf("Enter your contact number in integer and without dash  : ");
			rewind(stdin);
			scanf("%s", &userData1.contact);
			i = 0;
		}
	}

	printf("Confirm info to register?(Y = yes,N = No) =");
	while (x == 0)
	{
		rewind(stdin);
		scanf("%c", &confirmation);
		if (toupper(confirmation) == 'Y')
		{
			Date enterDate;
			Time enterTime;
			getSystemDate(&enterDate);
			getSystemTime(&enterTime);
			printf("User registration date is %d/%d/%d and time of registration is %d:%.2d\n", enterDate.d, enterDate.m, enterDate.y, enterTime.h, enterTime.m);
			userData1.dateEnter = enterDate;
			userData1.timeEnter = enterTime;


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
	char confirmation[20];
	char check;
	char choice[6];
	char exit[20];
	char s[20];
	char newPass[20];
	char newContact[20];
	char pass[100];
	int v = 0;
	int i = 0;
	int x = 0;
	int z = 0;
	char  changes[20];
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
		printf("Enter Id(type exit if you wanna return to main module) = ");
		rewind(stdin);
		scanf("%s", s);
		strcpy(exitProg, s);
		programExit = exitProgram(exitProg);
		if (programExit == 1)
		{
			fclose(userinfo1);
			return;
		}
		while (strlen(s) != 4)
		{

			if (strlen(s) != 4)
			{
				printf("Id enter should be only 4 digit  = ");
				rewind(stdin);
				scanf("%s", s);


			}

		}


		printf("Do you want to retype the current id that have entered?(Y = Yes/N = No) = ");
		rewind(stdin);
		scanf("%s", &confirmation);

		while ((toupper(confirmation[0]) != 'N' || toupper(confirmation[0]) != 'Y') && strlen(confirmation) > 1)
		{
			if ((toupper(confirmation[0]) == 'N' || toupper(confirmation[0]) == 'Y') && strlen(confirmation) == 1)
			{
				break;
			}

			printf("Pease enter either Y or N only(Y = Yes/N = No) = ");
			rewind(stdin);
			scanf("%s", &confirmation);

		}

		while (toupper(confirmation[0]) == 'Y' || strlen(confirmation) > 4)
		{

			printf("Enter Id again(Only 4 character) = ");
			rewind(stdin);
			scanf("%s", s);

			printf("Is the current ID enter is ok?(Y = Yes/N = No) = ");
			rewind(stdin);
			scanf("%s", &confirmation);

			while ((toupper(confirmation[0]) != 'N' || toupper(confirmation[0]) != 'Y') && strlen(confirmation) > 1)
			{
				if ((toupper(confirmation[0]) == 'N' || toupper(confirmation[0]) == 'Y') && strlen(confirmation) == 1)
				{
					break;
				}

				printf("Pease enter either Y or N only(Y = Yes/N = No) = ");
				rewind(stdin);
				scanf("%s", &confirmation);

			}
			if (toupper(confirmation[0]) == 'Y')
			{
				break;

			}

		}


		printf("Enter Password = ");
		rewind(stdin);
		collectCensoredInput(pass, 99);



		while (strlen(pass) < 6)
		{

			if (strlen(pass) < 6)
			{
				printf("Enter the password with at least minimum 6 words = ");
				rewind(stdin);
				collectCensoredInput(pass, 99);

			}


		}
		printf("Is the current password enter by user is ok?(Y = Yes/N = No) = ");
		rewind(stdin);
		scanf("%c", &confirmation);

		while ((toupper(confirmation[0]) != 'N' || toupper(confirmation[0]) != 'Y') && strlen(confirmation) > 1)
		{
			if ((toupper(confirmation[0]) == 'N' || toupper(confirmation[0]) == 'Y') && strlen(confirmation) == 1)
			{
				break;
			}

			printf("Pease enter either Y or N only(Y = Yes/N = No) = ");
			rewind(stdin);
			scanf("%s", &confirmation);

		}
		while (toupper(confirmation[0]) == 'N' || strlen(confirmation) > 4)
		{


			printf("Enter your password again = ");
			rewind(stdin);
			collectCensoredInput(pass, 99);



			while (strlen(pass) < 6)
			{

				if (strlen(pass) < 6)
				{
					printf("Enter the password with at least minimum 6 words = ");
					rewind(stdin);
					collectCensoredInput(pass, 99);

				}


			}

			printf("Is the current password is ok?(Y = Yes/N = No) = ");
			rewind(stdin);
			scanf("%c", &confirmation);


			while ((toupper(confirmation[0]) != 'N' || toupper(confirmation[0]) != 'Y') && strlen(confirmation) > 1)
			{
				if ((toupper(confirmation[0]) == 'N' || toupper(confirmation[0]) == 'Y') && strlen(confirmation) == 1)
				{
					break;
				}

				printf("Pease enter either Y or N only(Y = Yes/N = No) = ");
				rewind(stdin);
				scanf("%s", &confirmation);

			}




		}

		while (1)
		{
			i = 0;
			if (v == 1)
			{
				strcpy(user2[i].password, newPass);
				strcpy(pass, newPass);
			}
			for (i = 0; i < x; i++)
			{
				if ((strcmp(user2[i].id, s) == 0) && (strcmp(user2[i].password, pass) == 0))
				{

					
						userinfo1 = fopen(UserInfoFilePath, "wb");
						
						printf("__________________________\n");
						printf("Modify Info Module\n");
						printf("__________________________\n");
						printf("1. Change Password\n");
						printf("2. Change Contact Number\n");
						printf("3. Exit\n");
						printf("\nMenu Choice: ");

						char choice[6];
						getUserMenuChoice(choice, 6, "Menu Choice: ");
						switch (choice[0])
						{

						case '1':userinfo1 = fopen(UserInfoFilePath, "wb");
							printf("Enter old password = ");
							rewind(stdin);
							collectCensoredInput(pass, 99);
							while (strcmp(user2[i].password, pass) != 0)
							{
								printf("Enter the correct old password = ");
								rewind(stdin);
								collectCensoredInput(pass, 99);
							}
							printf("Enter new password = ");
							rewind(stdin);
							collectCensoredInput(newPass, 99);
							while (strlen(newPass) < 6)
							{


								printf("Enter the password with at least minimum 6 words = ");
								rewind(stdin);
								collectCensoredInput(s, 99);

							}

							strcpy(user2[i].password, newPass);
							strcpy(pass, newPass);

							for (i = 0; i < x; i++) {
								fwrite(&user2[i], sizeof(userData), 1, userinfo1);
							}
							fclose(userinfo1);
							v = 1;
							if (v == 1)
							{
								printf("Password has been change\n");
							}

							break;
						case '2':
							fclose(userinfo1);
							userinfo1 = fopen(UserInfoFilePath, "wb");

							printf("Enter new contact = ");
							scanf("%s", newContact);

							for (z = 0; z < strlen(newContact); z++)
							{
								while (isdigit(s[z]) != 0)
								{
									printf("Enter your contact number in integer and without dash  : ");
									rewind(stdin);
									scanf("%s", newContact);
									z = 0;
								}
							}
							strcpy(user2[i].contact, newContact);


							for (i = 0; i < x; i++) {
								fwrite(&user2[i], sizeof(userData), 1, userinfo1);
							}
							fclose(userinfo1);
							v = 1;
							if (v == 1)
							{
								printf("Contact Number has been change\n");
							}

							break;

						case '3':return;
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
								scanf("%s", changes);

								if ((toupper(changes[0]) != 'N' || toupper(changes[0]) != 'Y') && strlen(changes) > 1)
								{
									printf("Pls enter either 'Y' or 'N' only \n");
								}

								else if (toupper(changes[0]) == 'Y')
								{
									v = 0;
									break;
								}
								else if (toupper(changes[0]) == 'N')
								{

									return;
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
							scanf("%s", exit);
							if ((toupper(exit[0]) != 'N' || toupper(exit[0]) != 'Y') && strlen(exit) > 1)
							{
								printf("Pls enter either 'Y' or 'N' only \n");
							}
							else if (toupper(exit[0]) == 'Y')
							{
								i = 0;

								break;
							}
							else if (toupper(exit[0]) == 'N')
							{

								return;
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
							scanf("%s", exit);
							if ((toupper(exit[0]) != 'N' || toupper(exit[0]) != 'Y') && strlen(exit) > 1)
							{
								printf("Pls enter either 'Y' or 'N' only \n");
							}
							else if (toupper(exit[0]) == 'Y')
							{
								i = 0;

								break;
							}
							else if (toupper(exit[0]) == 'N')
							{

								return;
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
							scanf("%s", exit);
							if ((toupper(exit[0]) != 'N' || toupper(exit[0]) != 'Y') && strlen(exit) > 1)
							{
								printf("Pls enter either 'Y' or 'N' only \n");
							}
							else if (toupper(exit[0]) == 'Y')
							{
								i = 0;

								break;
							}
							else if (toupper(exit[0]) == 'N')
							{

								return;
							}
						}

					}


					break;
				}



			}
		if (toupper(exit[0]) == 'Y')
		{
				break;
		}
		}

	}
}

int displayInfo()
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
		printf("\t\t*Name               = %-12s      *\n", user2[i].name);
		printf("\t\t*Gender is          = %-12s      *\n", user2[i].gender);
		printf("\t\t*Contact number  is = %-12s      *\n", user2[i].contact);
		printf("\t\t*Date Registered is = %d/%d/%-12d*\n", user2[i].dateEnter.d, user2[i].dateEnter.m, user2[i].dateEnter.y);
		printf("\t\t*Time registered is = %d:%-12d   *\n", user2[i].timeEnter.h, user2[i].timeEnter.m);
		printf("\t\t*****************************************\n");
		printf("\n");
	}
	fclose(userinfo1);
	system("pause");
	return;
}

int searchInfo()
{



	char userAnswer[20] ;
	int x = totalNumUser();
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

	for (i = 0; i < x; i++) {
		fread(&user2[i], sizeof(userData), 1, userinfo1);
	}



	while (1)
	{
		int validationCheck = 0;
		printf("Enter your user ID(4 characters)(type exit to return to main module) = ");
		rewind(stdin);
		scanf("%s", id);
		while (strlen(id) != 4)
		{

			if (strlen(id) != 4)
			{
				printf("Enter a id that is 4 characters(type exit to return to main module)  = ");
				rewind(stdin);
				scanf("%s", id);
				if (strcmp(id, "exit") == 0)
				{
					return;
				}
			}


		}
		if (strcmp(id,"exit") == 0 )
		{
			return;
		}
		

		for (i = 0; i < x; i++)
		{


			if (strcmp(user2[i].id, id) == 0 )
			{

				printf("Name = %s\n", user2[i].name);
				printf("ID   = %s\n", user2[i].id);
				printf("Password = %s\n", user2[i].password);
				printf("Gender is = %s\n", user2[i].gender);
				printf("Contact number is = %s\n", user2[i].contact);
				system("pause");
				return 0;

			}

		}

		
		while (validationCheck == 0)
		{
			printf("Data enter does not match with database do you want to try again (Y = yes/N =No) = ");
			rewind(stdin);
			scanf("%s", userAnswer);
			if (toupper(userAnswer[0]) == 'Y' )
			{ 
				validationCheck = 1;
				continue;
			}
			else if (toupper(userAnswer[0]) == 'N' )
			{
				return;
			}
			else
				printf("Please entger either Y or N\n");

		}






	}
}

int userInfo()
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

	char choiceText[][100] = { "Registration For New User", "Modify User Info", "Search Details Of User(ONLY FOR STAFF)", "Display All The User In Database(ONLY FOR STAFF)", "Exit" };
	do {
		int choice = globalMainMenu("^_^ USERINFO MODULE ^_^", 5, choiceText);

		switch (choice)
		{
		case 1:registerInfo();
			break;
		case 2: modifyInfo2();
			break;
		case 3:
		if (!_staffLogin(sessionStaffID, 99))
		{
			return;
		}
		while (searchInfo())
		{
			continue;
		}
			
			break;
		case 4:
		if (!_staffLogin(sessionStaffID, 99))
		{
			return;
		}
	     while (displayInfo())
	    {
				   continue;
		}
			
			break;
		case 5:
			return 0;

		default:
			return 1;
		}
	} while (1);
	return 1;
}

void userinfoMain() {



	userInfo();
	
	

}

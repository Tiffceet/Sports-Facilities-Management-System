#include "stdcxx.h"
#include "booking.h"
void init();
int mainMenu();
int main(void)
{
	// initalise env variables
	init();
	printf("%s\n%s\n", APPDATA_PATH, CURRENT_SYS_DATE);
	while (mainMenu()) // if user input is invalid, menu() returns 0
	{
		system("cls"); // clear current console screen
		continue;
	}
	system("pause");
	return 0;
}

// Function to define all env variables
void init()
{
	APPDATA_PATH = getenv("APPDATA");
	if (!APPDATA_PATH) // If appdata is somehow gone, uses relative folder path "data"
	{
		APPDATA_PATH = "data";
	}
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(CURRENT_SYS_DATE, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

int mainMenu()
{
	printf("%41s-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n", "");
	printf("%41s|     Sports Facilities Console     |\n", "");
	printf("%41s-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n", "");
	printf("%41s|     1. Staff                      |\n", "");
	printf("%41s|     2. Facilities                 |\n", "");
	printf("%41s|     3. Users                      |\n", "");
	printf("%41s|     4. Booking facilities         |\n", "");
	printf("%41s|     5. Facilities Usage           |\n", "");
	printf("%41s|     6. Exit                       |\n", "");
	printf("%41s-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n", "");
	printf("%49sEnter menu choice: ", "");

	// prevents user from spamming keys on menu
	char choice[100];
	fgets(choice, 99, stdin);
	if (strlen(choice) != 2) // 2 because fgets() also capture the \n
	{
		return 1;
	}
	rewind(stdin);

	// menu selection
	switch (choice[0])
	{
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		bookingMain();
		break;
	case '5':
		break;
	case '6':
		exit(0); // maybe we should do some file validation (checks if all files are closed properly)
		break;
	default:
		// printf("%52sInvalid Choice.\n", "");
		return 1;
	}
	return 0;
}
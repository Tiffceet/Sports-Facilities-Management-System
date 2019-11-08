#include "stdcxx.h"
// function to define all env variables
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

// function for everyone to collect user choice for menu selection
// store user input in buffer and check if the choice is 1 character long
// please let buffer size > 2
int getUserMenuChoice(char buffer[], int size) 
{
	// prevents user from spamming keys on menu
	fgets(buffer, size, stdin);
	rewind(stdin);
	if (strlen(buffer) != 2) // 2 because fgets() also capture the \n
	{
		return 1;
	}
	return 0;
	// above line can be simplified to "return strlen(buffer != 2);"
}
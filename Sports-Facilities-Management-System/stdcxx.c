#include "stdcxx.h"
// function to define all env variables
void init()
{
	APPDATA_PATH = getenv("APPDATA");
	if (!APPDATA_PATH) // If appdata is somehow gone, uses relative folder path "data"
	{
		APPDATA_PATH = "data";
	}
	else
	{
		system("IF NOT EXIST %appdata%\\SFMS mkdir %appdata%\\SFMS"); // make sure SFMS folder exists
		sprintf(APPDATA_PATH, "%s\\SFMS", APPDATA_PATH); // append SFMS to appdata path
	}
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

// get system date in yyyy-mm-dd
// will write date into dateVar passed into func
void getSystemDate(char dateVar[])
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(dateVar, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

// get system time in hh:mm:ss
// will write time into timeVar passed into func
void getSystemTime(char timeVar[])
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);	
	sprintf(timeVar, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
}

// check if file exists
int chkFileExist(char* dir)
{
	FILE *f;
	if (f = fopen(dir, "r"))
	{
		fclose(f);
		return 1;
	}
	return 0;
}
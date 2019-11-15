#include "stdcxx.h"
// function to define all env variables
void init()
{
	char *temp = getenv("APPDATA");
	if (!temp) // If appdata is somehow gone, uses relative folder path "data"
	{
		strcpy(APPDATA_PATH, "data");
	}
	else
	{
		system("IF NOT EXIST %appdata%\\SFMS mkdir %appdata%\\SFMS"); // make sure SFMS folder exists
		sprintf(APPDATA_PATH, "%s\\SFMS", temp); // append SFMS to appdata path
	}
}

// function for everyone to collect user choice for menu selection
// store user input in buffer and check if the choice is 1 character long
// please let buffer size > 2
void getUserMenuChoice(char buffer[], int size, char *errMsg) 
{
retry:
	// prevents user from spamming keys on menu
	fgets(buffer, size, stdin);
	char *trimmedCharArr = trimwhitespace(buffer);
	rewind(stdin);

	if (strlen(trimmedCharArr) != 1)
	{
		printf("%s", errMsg);
		goto retry;
	}
	// because we are checking trimmedCharArr, gonna make sure buffer is trimmed
	strcpy(buffer, trimmedCharArr);
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

char *trimwhitespace(char *str)
{
	char *end;
	// Trim leading space
	while (isspace((unsigned char)*str)) str++;
	if (*str == 0)  // All spaces?
		return str;
	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;
	// Write new null terminator character
	end[1] = '\0';
	return str;
}

// get string input function -> the safe way
void s_input(char *str, int size)
{
	rewind(stdin);
	fgets(str, size, stdin);
	// replace \n with \0
	char *loc = strchr(str, '\n');
	if (loc && *(loc + 1) == '\0')
	{
		*loc = '\0';
	}
	rewind(stdin);
}
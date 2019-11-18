#include "stdcxx.h"
// function to define all env variables
void init()
{
	char *temp = getenv("APPDATA");
	if (!temp) // If appdata is somehow gone, uses relative folder path "data"
	{
		strcpy(APPDATA_PATH, "data");
		strcpy(CACHE_FILE, "data\\cache.txt");
		strcpy(CACHE_FILE_BIN, "data\\cache.bin");
	}
	else
	{
		system("IF NOT EXIST %appdata%\\SFMS mkdir %appdata%\\SFMS"); // make sure SFMS folder exists
		sprintf(APPDATA_PATH, "%s\\SFMS", temp); // append SFMS to appdata path
		sprintf(CACHE_FILE, "%s\\cache.txt",APPDATA_PATH);
		sprintf(CACHE_FILE_BIN, "%s\\cache.bin", APPDATA_PATH);
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
	long fsize = 0;
	if (f = fopen(dir, "r"))
	{
		fseek(f, 0, SEEK_END); // move file pointer to the end of file
		fsize = ftell(f);
		if (fsize == 0) // if file is empty
		{
			fclose(f);
			return 0;
		}
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

int validateDate(int dd, int mm, int yy)
{
	//check year
	if (yy >= 1900 && yy <= 9999)
	{
		//check month
		if (mm >= 1 && mm <= 12)
		{
			//check days
			if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
				return 1;
			else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
				return 1;
			else if ((dd >= 1 && dd <= 28) && (mm == 2))
				return 1;
			else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else	
		return 0;
	return 0;
}
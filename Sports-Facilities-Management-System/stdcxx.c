#include "stdcxx.h"

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
		system("IF NOT EXIST \"%appdata%\\SFMS\" mkdir \"%appdata%\\SFMS\""); // make sure SFMS folder exists
		sprintf(APPDATA_PATH, "%s\\SFMS", temp); // append SFMS to appdata path
		sprintf(CACHE_FILE, "%s\\cache.txt", APPDATA_PATH);
		sprintf(CACHE_FILE_BIN, "%s\\cache.bin", APPDATA_PATH);
	}
}

int globalMainMenu(char* title, int choiceCount, char choiceText[][100])
{
	rewind(stdin);
	unsigned char input1, input2;
	char titleFormat[300];
	int curPos = 1;
	if(strlen(title) % 2 == 0){
		sprintf(titleFormat, "%%22s| %%%ds%%s%%%ds |\n", (70 - strlen(title))/2, (70 - strlen(title)) / 2);
	}
	else
	{
		sprintf(titleFormat, "%%22s| %%%ds%%s%%%ds |\n", (70 - strlen(title)) / 2, (70 - strlen(title)) / 2 + 1);
	}
	do{
		system("cls");
		printf("%14s   ____              __        ____         _ ___ __  _           ____        __          \n", "");
		printf("%14s  / __/__  ___  ____/ /____   / __/__ _____(_) (_) /_(_)__ ___   / __/_ _____/ /____ __ _ \n", "");
		printf("%14s _\\ \\/ _ \\/ _ \\/ __/ __(_-<  / _// _ `/ __/ / / / __/ / -_|_-<  _\\ \\/ // (_-< __/ -_)  ' \\\n", "");
		printf("%14s/___/ .__/\\___/_/  \\__/___/ /_/  \\_,_/\\__/_/_/_/\\__/_/\\__/___/ /___/\\_, /___|__/\\__/_/_/_/\n", "");
		printf("%14s   /_/                                                             /___/                  \n\n", "");
		printf("%22s-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n", "");
		// printf("%s;\n", titleFormat);
		printf(titleFormat, "", "",title, "");
		printf("%22s-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n", "");
		printf("%22s|                                                                        |\n", "");
		for (int a = 0; a < choiceCount; a++)
		{
			if(curPos == a+1){
				printf("%22s| %3s %2d. %-62s |\n", "", "->", a+1,choiceText[a]);			
			}
			else
			{
				printf("%22s| %3s %2d. %-62s |\n", "", "", a + 1, choiceText[a]);
			}

		}
		printf("%22s|                                                                        |\n", "");
		printf("%22s-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n", "");
		printf("%22s* \\               Press 'Up' & 'Down' to move selection.               / *\n", "");
		printf("%22s   \\ *              Press 'ENTER' to comfirm selection              * /\n", "");
		input1 = _getch();
		if (input1 == 0) // if fn keys are pressed
		{
			// simply ignore
			_getch();
			continue;
		}
		if (input1 == 13) // if enter key is pressed
		{
			return curPos;
		}
		if (input1 == 224) // if arrow key is pressed
		{
			input2 = _getch();
			if (input2 == 80) // if Down is pressed
			{
				curPos++;
			}
			if (input2 == 72) // if Up is pressed
			{
				curPos--;
			}
		}
		if (curPos < 1)
		{
			curPos = choiceCount;
		}
		if (curPos > choiceCount)
		{
			curPos = 1;
		}
	} while (1);
}

void getUserMenuChoice(char buffer[], int size, char *errMsg)
{
	while (1) {
		// prevents user from spamming keys on menu
		rewind(stdin);
		fgets(buffer, size, stdin);
		char *trimmedCharArr = trimwhitespace(buffer);
		rewind(stdin);

		if (strlen(trimmedCharArr) != 1)
		{
			printf("%s", errMsg);
			continue;
		}
		// because we are checking trimmedCharArr, gonna make sure buffer is trimmed
		strcpy(buffer, trimmedCharArr);
		break;
	}
}

void getSystemDate(Date *dateVar)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	dateVar->y = tm.tm_year + 1900;
	dateVar->m = tm.tm_mon + 1;
	dateVar->d = tm.tm_mday;
}

void getSystemTime(Time *timeVar)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	timeVar->h = tm.tm_hour;
	timeVar->m = tm.tm_min;
	timeVar->s = tm.tm_sec;
}

int chkFileExist(FILE *f)
{
	long fsize = 0;
	if (f)
	{
		fseek(f, 0, SEEK_END); // move file pointer to the end of file
		fsize = ftell(f);
		if (fsize == 0) // if file is empty
		{
			fclose(f);
			return 0;
		}
		fseek(f, 0, SEEK_SET);
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

int collectCensoredInput(char* str, int size)
{
	int idx = 0;
	unsigned char buf;
	do
	{
		buf = _getch();

		// if weird key is being pressed
		// weird key that give escaped character when its being pressed
		// e.g. delete key, del key on keypad, f1-f10 keys
		if (buf == 0)
		{
			_getch();
			continue;
		}

		if (buf == 13) // if enter key pressed
		{
			str[idx] = '\0';
			return;
		}
		
		if (buf == 8) // backspace is being pressed
		{
			if (idx <= 0) { // if user input is empty
				printf("");
			}
			else
			{          // remove last character input
				printf("\b \b");
				idx--;
			}
			continue;
		}

		if (idx == size-1) // if idx already reach end of string
		{
			continue;
		}

		if (isdigit(buf) || isalpha(buf))
		{
			str[idx++] = buf;
			printf("*");
		}
		else               // is other non-digit character is being pressed
		{
			// do nothing
		}
	} while (1);
}

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
			// else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
			else if (dd == 29 && mm == 2 && yy % 4 == 0)
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

int validateTime(int h, int m, int s)
{
	if (h < 0 || h >23)
	{
		return 0;
	}
	if (m < 0 || m > 59)
	{
		return 0;
	}
	if (s < 0 || s > 59)
	{
		return 0;
	}
	return 1;
}

int compareTime(int h1, int m1, int s1, int h2, int m2, int s2)
{
	if (h1 == h2 && m1 == m2 && s1 == s2) return 0;
	if (h1 > h2) return 1;
	if (h2 > h1) return -1;
	if (m1 > m2) return 1;
	if (m2 > m1) return -1;
	if (s1 > s2) return 1;
	if (s2 > s1) return -1;
	return -2;
}

int compareDate(int dd1, int mm1, int yy1, int dd2, int mm2, int yy2)
{
	if (dd1 == dd2 && mm1 == mm2 && yy1 == yy2) return 0;
	if (yy1 > yy2) return 1;
	if (yy2 > yy1) return -1;
	if (mm1 > mm2) return 1;
	if (mm2 > mm1) return -1;
	if (dd1 > dd2) return 1;
	if (dd2 > dd1) return -1;
	return -2;
}
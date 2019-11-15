/* 
	This header file contains:
		- all includes on standard C Library
		- Environment variables
		- global utilities functions
*/
#ifndef STDCXX_H
#define STDCXX_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>
#pragma warning(disable: 4996)

// Env variables declarations
char APPDATA_PATH[1024];
typedef struct
{
	int y, m, d;
} Date;

typedef struct
{
	int h, m, s;
} Time;

// function declarations
void init();
void getUserMenuChoice(char buffer[], int size, char *errMsg);
void getSystemDate(char dateVar[]);
void getSystemTime(char timeVar[]);
int chkFileExist(char* dir);
char *trimwhitespace(char *str);
void s_input(char *str, int size);
#endif
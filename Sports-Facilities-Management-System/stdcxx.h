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
char CACHE_FILE_BIN[1024];
char CACHE_FILE[1024];
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

// functions related to inputs
void getUserMenuChoice(char buffer[], int size, char *errMsg);
int chkFileExist(char* dir);
char *trimwhitespace(char *str);
void s_input(char *str, int size);

// functions related to date and time verification
void getSystemDate(char dateVar[]);
void getSystemTime(char timeVar[]);
int validateDate(int dd, int mm, int yy);
int validateTime(int h, int m, int s);
int compareTime(int h1, int m1, int s1, int h2, int m2, int s2);
int compareDate(int dd1, int mm1, int yy1, int dd2, int mm2, int yy2);
#endif
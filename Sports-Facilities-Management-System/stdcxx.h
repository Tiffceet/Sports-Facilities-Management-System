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
#include <conio.h>
#pragma warning(disable: 4996)

// Env variables declarations
char staffFilePath[1024];
char bookingFilePath[1024];
char UserInfoFilePath[1024];
char facilityFilePath[1024];
char fUsageFilePath[1024];
char sessionStaffID[100]; // to keep track of what staff is being log on
typedef struct
{
	int y, m, d;
} Date;

typedef struct
{
	int h, m, s;
} Time;

// ===================================================================================================
// function declarations
// ===================================================================================================

// Function to define all env variables
void init();

// login Staff and store ID onto staffID
// if login was successful, it will return true
int _staffLogin(char *staffID, int size);

// Function for every module's main menu
// return user selection
// if user ctrl+enter, it will return negative value of the selection
int globalMainMenu(char* title, int choiceCount, char choiceText[][100]);

// ===================================================================================================
// functions related to inputs
// ===================================================================================================

// Function for everyone to collect user choice for menu selection
// Store user input in buffer and check if the choice is 1 character long
// Please let buffer size > 2
void getUserMenuChoice(char buffer[], int size, char *errMsg);

// Check if file exists
// Return true if file exist
int chkFileExist(FILE *f);

char *trimwhitespace(char *str);

// For collecting password
// Only alphanumberic are allowed
void collectCensoredInput(char* str, int size);

// Get string input function -> the safe way
void s_input(char *str, int size);

// Get integer input function -> the safe way
// return true if user entered an integer
int i_input(int *num);

// ===================================================================================================
// functions related to date and time verification
// ===================================================================================================

// Get system date in yyyy-mm-dd
// Will write date into dateVar passed into func
void getSystemDate(Date *dateVar);

// Get system time in hh:mm:ss
// Will write time into timeVar passed into func
void getSystemTime(Time *timeVar);
int validateDate(int dd, int mm, int yy);
int validateTime(int h, int m, int s);

// return 1 if time1 is later than time2
// return -1 if time2 is later than time1
// return 0 if both time are the same
int compareTime(int h1, int m1, int s1, int h2, int m2, int s2);

// return 1 if date1 is later than date2
// return -1 if date2 is later than date1
// return 0 if both time are the same
int compareDate(int dd1, int mm1, int yy1, int dd2, int mm2, int yy2);

#endif
/* 
	This header file contains:
		- all includes on standard C Library
		- Environment variables
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
const char *APPDATA_PATH;
const char CURRENT_SYS_DATE[50];
#endif
/* 
	This header file contains:
		- all includes on standard C Library
		- Environment variables
*/
/*
	Please do not include stdcxx.h directly
	Usage:
		#ifndef STDCXX_H
		#include "stdcxx.h"
		#endif
*/
#define STDCXX_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#pragma warning(disable: 4996)

// Env variables declarations
char *appdataPath;

// Functions to define all env variables
void init()
{
	appdataPath = getenv("APPDATA");
	if (!appdataPath) // If appdata is somehow gone, uses relative folder path "data"
	{
		appdataPath = "data";
	}
}


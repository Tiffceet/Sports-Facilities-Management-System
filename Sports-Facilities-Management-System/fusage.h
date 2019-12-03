#include "stdcxx.h"
#ifndef FUSAGE_H
#define FUSAGE_H

typedef struct
{
	Date date;
	char time[30];
	char userID[30], facilityID[20];
	char usageType[20];
} FacilityUsage;

typedef struct
{
	char staffID[30], password[30];
} StaffValidation;

void staffLogin();
void fusagemain();
void fUsageRecord();
void fUsageAddRecord();
void fUsageSearchRecord();
void fUsageModify();
void fUsageDisplay();
int fUsageMenu();

int err;
// variable for filepath
char fusageFilePath[1024];
#endif
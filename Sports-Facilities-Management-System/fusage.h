#include "stdcxx.h"
#include "facility.h"
#include "staff.h"
#include "userinfo.h"
#ifndef FUSAGE_H
#define FUSAGE_H

typedef struct
{
	Date date;
	int time[6];
	char userID[30], facilityID[10];
	char usageType[20];
} FacilityUsage;

FacilityUsage fUsage[100];
userData uData[100];
Facility fData[100];

int staffLogin();

void fusagemain();
int fUsageRecord();
void fUsageAddRecord();
void fUsageSearchRecord();
void fUsageModify();
void fUsageDelete();
void fUsageDisplay();
int fUsageMenu();

int date(Date* date);
int chkTime(char* time);

void slctFacilityID(char*facilityID);
void getUserID(char* userID);
//void chkAvailableAdd(Date* date, int* time, char* facilityID);

int err;
// variable for filepath
char fusageFilePath[1024];
#endif
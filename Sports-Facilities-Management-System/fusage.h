#include "stdcxx.h"
#include "facility.h"
#include "staff.h"
#include "userinfo.h"
#ifndef FUSAGE_H
#define FUSAGE_H

typedef struct
{
	Date date;
	char time[20];
	char userID[30], facilityID[10];
	char usageType[20];
} FacilityUsage;

FacilityUsage fUsage[100];
userData uData[100];
Facility fData[100];
int uDataCount;
int fDataCount;
int bDataCount;

int staffLogin();

void fusagemain();
void fUsageRecord();
void fUsageAddRecord();
void fUsageSearchRecord();
void fUsageModify();
void fUsageDisplay();
int fUsageMenu();

int date(Date* date);
int slctTime(char* time);

void slctFacilityID(char*facilityID);
void slctUserID(char* userID);

void readBookingFileToFUsageFile();

Facility* getFacilityID(char* id);
userData* getUserID(char* id);

int err;
#endif
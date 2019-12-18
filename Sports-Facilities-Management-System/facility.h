
#pragma once
#include "stdcxx.h"
#include "staff.h"
#ifndef FACILITY_H
#define FACILITY_H
int facilityMenu();
void addNewFacility();
void searchFacility();
void displayAllFacility();
void facInfoMain();
Staff staffLogon;

typedef struct
{
	char id[10];
	char name[200];
	Date maintainanceDate;
	char remarks[500];
	char staffHandledID[100];
	Date lastModified;

} Facility;

#endif
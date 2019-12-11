#pragma once
#ifndef FACILITY_H
#define FACILITY_H
int facilityMenu();
void addNewFacility();
void searchFacility();
void displayAllFacility();
typedef struct
{
	char id[5];
	char type[20];
	char description[20];
	char venue[20];
	int maxUser;

}Facility;

#endif
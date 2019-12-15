#pragma once
#ifndef STAFF_H
#define STAFF_H

// struture for to store staff
typedef struct
{
	char stfName[30];
	char stfPassW[100];
	char stfConPassW[100];// confirm password
	char stfID[6];
	char stfPosi[10];
	Date dateRegis;
	Date dateModi;
	Time timeRegis;
	Time timeModi;
}Staff;

void addStaffList();
void displayStaffList();
void staffMain();
void pwRecover();
void changeStfList();
void login();
void staffSearchID();
int staffSearchName();
#endif

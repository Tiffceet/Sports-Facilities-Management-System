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

int addStaffList();
//void noStaffRegistration();
void displayStaffList();
void staffMain();
void pwRecover();
int changeStfList();
void login();
void pwRecover();
void staffSearchID();
int staffSearchName();
int checkPosition();
#endif

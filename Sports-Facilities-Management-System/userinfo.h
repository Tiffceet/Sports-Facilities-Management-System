#pragma once
#include "stdcxx.h"
#ifndef USERINFO_H
#define USERINFO_H
int searchInfo();
int displayInfo();
void userinfoMain();
int userInfo();
void registerInfo();
void modifyInfo2();
int totalNumUser();
char UserInfoFilePath[1024];
int exitProgram(char quit[10]);
int uniqueId(char id[15]);
typedef struct {

	char name[100];
	char id[15];
	Date dateEnter;
	Time timeEnter;
	char gender[20];
	char contact[100];
	char password[100];
}userData;
userData user1, user2[100];
#endif
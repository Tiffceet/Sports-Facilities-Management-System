#pragma once
#ifndef USERINFO_H
#define USERINFO_H
void userEntry();
int searchInfo();
void modifyInfo();
void displayInfo();
void userinfoMain();
void userInfo();
void registerInfo();
char UserInfoFilePath[1024];
typedef struct {

	char name[100];
	char id[100];
	char gender;
	int contact[100];
	char password[100];
}userData;

#endif
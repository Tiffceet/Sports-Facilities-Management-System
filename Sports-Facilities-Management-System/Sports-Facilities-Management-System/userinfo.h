#pragma once
#ifndef USERINFO_H
#define USERINFO_H
void userEntry();
void searchInfo();
void modifyInfo();
void displayInfo();
void userinfoMain();
void userInfo();
void registerInfo();
char UserInfoFilePath[1024];
typedef struct {

	char name[25];
	char id[5];
	char gender;
	char contact[12];
	char password[12];
}userData;

#endif
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
void modifyInfo2();
int totalNumUser();
typedef struct {

	char name[100];
	char id[15];
	char gender;
	char contact[100];
	char password[100];
}userData;
userData user1, user2[100];
#endif
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
typedef struct {

	char name[100];
	char id[100];
	char gender;
	int contact[100];
	char password[100];
}userData;

#endif
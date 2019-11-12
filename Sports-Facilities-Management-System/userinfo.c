#include "userinfo.h"
#include "stdcxx.h"

typedef struct {

	char name[30];
	char id[30];
	char gender;
	int contact;
}userData;
void registerInfo()
{
	userData userData1;
	FILE * userinfo;
	userinfo = fopen("userinfo.bin", "a");

	printf("Enter your name = ");
	scanf("[^\n]", userData1.name);






}
void regisLogUser()
{

	printf("__________________________\n");
	printf("Registeration\\Login Module\n");
	printf("__________________________\n");
	printf("1. Login \n");
	printf("2. Register As A New User\n");
	printf("3. Exit\n");
	printf("\nMenu Choice: ");

	char option[10];

	switch (option[0])
	{
	case '1':registerInfo();
		break;
	case '2':
		break;
	case '3':return 0;
		break;
	default:
		return 1;
	}
	

}



#include<stdlib.h>
#include<stdio.h>

typedef struct
{
	char id[5];
	char type[20];
	char description[20];
	char venue[20];
	int maxUser;

}Facility;

int facilityMenu()
{
	printf("Facility Menu\n");
	printf("--------------\n");
	printf("(1) Add New Facility\n");
	printf("(2) Search Faciity\n");
	printf("(3) Display All Facility\n");
	printf("Enter Your Choice: ");
	char choice[10];
	switch (choice[0])
	{
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	case '5':
		return 0;
	default:
		return 1;
	}
	return 1;

}

void addNewFacility()
{
	int a;
	Facility facility[10]; 
	FILE*facilityFile;
	facilityFile = fopen("facility.txt", "a");

	if (facilityFile==NULL)
	{
		printf("Cannot open facilityFile.");
		return;
	}

	for (a = 0; a< 10; a++)
	{
		printf("Facility: ");
		rewind(stdin);
		scanf("%[^\n]", facility[a].id);
		rewind(stdin);
		printf("Facility Type: ");
		scanf("%[^\n]", facility[a].type);
		rewind(stdin);
		printf("Facility Description:");
		scanf("%[^\n]", facility[a].description);
		rewind(stdin);
		printf("Facility Venue:");
		scanf("%[^\n]", facility[a].venue);
		rewind(stdin);
		printf("Maximum User:");
		scanf("%d", facility[a].maxUser);
		rewind(stdin);

	}
	fclose(facilityFile);
	return;
}

void searchFacility()
{

}

void displayAllFacility()
{

}
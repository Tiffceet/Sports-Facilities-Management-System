#include "stdcxx.h"
#include "facility.h"

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
	char choice[10];
	printf("Enter Your Choice: ");
	rewind(stdin);
	scanf("%s", &choice);
	rewind(stdin);

	switch (choice[0])
	{
	case '1':
		addNewFacility();
		break;
	case '2':
		searchFacility();
		break;
	case '3':
		displayAllFacility();
		break;
	default:
		return 1;
	}

}

void addNewFacility()
{
	int a;
	Facility facility[10];
	FILE*facilityFile;
	facilityFile = fopen("facility.txt", "a");

	if (facilityFile == NULL)
	{
		printf("Cannot open facilityFile.");
		system("pasue");
		exit(-1);
	}

	for (a = 0; a < 10; a++)
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

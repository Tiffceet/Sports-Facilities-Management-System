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
	printf("(3) Modify Faciity\n");
	printf("(4) Display All Facility\n");
	char choice;
	printf("Enter Your Choice: ");
	rewind(stdin);
	scanf("%s", &choice);
	rewind(stdin);

	switch (choice)
	{
	case '1':
		addNewFacility();
		break;
	case '2':
		searchFacility();
		break;
	case '3':
		modifyFacility();
		break;
	case '4':
		displayAllFacility();
		break;
	default:
		return;
	}

}

void addNewFacility()
{
	int a;
	Facility facility[10];
	FILE*facilityFile;
	facilityFile = fopen("facility.dat", "a");

	if (facilityFile == NULL)
	{
		printf("Cannot open facilityFile.");
		return;
	}

	for (a = 0; a < 10; a++)
	{
		printf("Facility id: ");
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
		scanf("%d", &facility[a].maxUser);
		rewind(stdin);

	}
	fclose(facilityFile);
	return;
}

void searchFacility()
{
	int choice1;

	Facility facility[10];
	FILE*facilityFile;
	facilityFile = fopen("facility.dat", "rb");

	while (!chkFileExist(facilityFile))
	{
		printf("Cannot find facility file\n");
		return;
	}

	printf("(1) Badminton\n");
	printf("(2) Basketball\n");
	printf("(3) Tennis\n");
	printf("(4) Ping Pong\n");
	printf("What facility are you searching for? :");
	rewind(stdin);
	scanf("%d", choice1);

	switch (choice1)
	{
	case '1':
		printf("");
		break;
	case '2':
		printf("");
		break;
	case '3':
		printf("");
		break;
	case '4':
		printf("");
		break;
	default:
		return;
	}
}

void modifyFacility()
{
	int choice2, maxFac;
	char facType[15], facDescription[20], facVenue[20];

	Facility facility[10];
	FILE *facilityFile;
	facilityFile = fopen("facility.dat", "rb");
	while (!chkFileExist(facilityFile))
	{
		printf("Cannot find facility file\n");
		system("pause");
		return;
	}

	printf("1. Facility Type\n");
	printf("2. Facility Description\n");
	printf("3. Facility Venue");
	printf("4. Maximum User");;
	printf("Which one do you want to modify: ");
	rewind(stdin);
	scanf("%d", &choice2);

	while (strcmp(choice2, 1) != 0 && strcmp(choice2, 2) != 0 &&
		strcmp(choice2, 3) != 0 && strcmp(choice2, 4) != 0)
	{
		printf("Invalid Input. Please Re-enter:");
		rewind(stdin);
		scanf("%d", choice2);
	}

	if (strcmp(choice2, 1) == 0)
	{
		printf("Facility Type:");
		scanf("%s", facType);
		fprintf(facilityFile, "%s %s %s %s %d", facility->id, facType, facility->venue, facility->description, facility->maxUser);
	}

	if (strcmp(choice2, 2) == 0)
	{
		printf("Facility Description:");
		scanf("%s", facDescription);
		fprintf(facilityFile, "%s %s %s %s %d", facility->id, facility->type, facility->venue, facDescription, facility->maxUser);
	}

	if (strcmp(choice2, 3) == 0)
	{
		printf("Facility Venue:");
		scanf("%s", facVenue);
		fprintf(facilityFile, "%s %s %s %s %d", facility->id, facility->type, facVenue, facility->description, facility->maxUser);
	}

	if (strcmp(choice2, 4) == 0)
	{
		printf("Maximum User of Facility:");
		scanf("%s", maxFac);
		fprintf(facilityFile, "%s %s %s %s %d ", facility->id, facility->type, facility->venue, facility->description, maxFac);
	}

	fclose(facilityFile);
	system("pause");
}

void displayAllFacility()
{
	Facility facility;
	FILE*facilityFile;
	facilityFile = fopen("facility.dat", "rb");

	while (facilityFile == NULL)
	{
		printf("Cannot open facility file.\n");
		system("pause");
		return;
	}

	while (fread(&facility, sizeof(facility), 1, facilityFile) != 0)
	{
		printf("Facility ID:%s\n", facility.id);
		printf("Facility Type:%s\n", facility.type);
		printf("Facility Venue:%s\n", facility.venue);
		printf("Facility Description:%s\n", facility.description);
		printf("Maximum of Facility::%d\n", facility.maxUser);
	}
	fclose(facilityFile);
}



#include "stdcxx.h"
#include "facility.h"

void facInfoMain()
{
	if (!_staffLogin(sessionStaffID, 99))
	{
		return;
	}
	FILE *f = fopen(staffFilePath, "rb");
	// find staffData of the staff log on
	while (fread(&staffLogon, sizeof(Staff), 1, f) != 0) 
	{
		if (strcmp(sessionStaffID, staffLogon.stfID) == 0)
		{
			break;
		}
	}
	fclose(f);
	while (facilityMenu() != 5) // if user didnt choose logout
	{

	}
	// if user finally wants to log out
	sessionStaffID[0] = '\0';

}


void addNewFacility()
{
	char choice[10];

	FILE*facilityFile;
	Facility fac;
	facilityFile = fopen(facilityFilePath, "ab");
	if (facilityFile == NULL)
	{
		printf("Cannot open facilityFile.");
		return;
	}
	do{
		fac.id[0] = '\0';
		do {
			if (strlen(fac.id) > 5)
			{
				printf("Maximum of 5 character");
			}
			printf("New Facility ID (max 5): ");
			s_input(fac.id, 7);
		} while (strlen(fac.id) > 5);

		printf("New Facility Name: ");
		s_input(fac.name, 199);

		int r = -999; // to store scanf output
		fac.maintenanceDate.y = 2020; // for the validation to work
		do {
			if (r != -999) {
				if (r != 2)
				{
					printf("Wrong Date format.\n");
				}
				else if (!validateDate(fac.maintenanceDate.d, fac.maintenanceDate.m, fac.maintenanceDate.y))
				{
					printf("Invalid date\n");
				}
			}
			printf("Facility Yearly Maintenance Date (dd/mm): ");
			rewind(stdin);
			r = scanf("%d/%d", &fac.maintenanceDate.d, &fac.maintenanceDate.m);
			rewind(stdin);
		} while (r != 2 || !validateDate(fac.maintenanceDate.d, fac.maintenanceDate.m, fac.maintenanceDate.y));


		printf("Facility Remarks <Press ENTER if none> : ");
		s_input(fac.remarks, 499);

		strcpy(fac.staffHandledID, sessionStaffID);
		getSystemDate(&fac.lastModified);

		printf("\nFacility ID              : %s\n", fac.id);
		printf("Facility Name            : %s\n", fac.name);
		printf("Facility Maintenance Date: %02d/%02d\n", fac.maintenanceDate.d, fac.maintenanceDate.m);
		printf("Facility Remarks         : %s\n", fac.remarks);
		printf("\nComfirm Adding facility ? (y = yes) ");

		getUserMenuChoice(choice, 9, "Comfirm Adding facility ? (y = yes, n = no) ");
		if (tolower(choice[0]) == 'y')
		{
			fwrite(&fac, sizeof(Facility), 1, facilityFile);
			printf("%s was added into the system.\n", fac.name);
			system("pause");
		}
		else
		{
			printf("Facility was not added.\n");
		}
		printf("Continue adding facility ? (y=yes) ");
		getUserMenuChoice(choice, 9, "Continue adding facility ? (y=yes) ");
	} while (tolower(choice[0] == 'y'));
	fclose(facilityFile);
}

void searchFacility()
{
	char searchFacilityName[200];
	Facility facility[10] = {"0"};
	FILE*facilityFile;
	facilityFile = fopen(facilityFilePath, "rb");

	while (!chkFileExist(facilityFile))
	{
		printf("Cannot find facility file\n");
		return;
	}

	printf("Search by name:");
	s_input(searchFacilityName,199);

	int i = 0;

	while (fread(&facility, sizeof(facility), 1, facilityFile) != 0)
	{
		if (strcmp(facility[i].name, searchFacilityName) == 0)
		{

			printf("Name = %s\n", facility[i].name);
			printf("ID   = %s\n", facility[i].id);
			printf(" Maintenance Date =%02d/%02d\n", facility[i].maintenanceDate);
			printf(" Remarks = %s\n", facility[i].remarks);
			system("pause");
			return;
		}
		else
			i++;
	}
		
}

void modifyFacility()
{
	Facility facData[100];
	int dataCount = 0;
	FILE *f = fopen(facilityFilePath, "rb");
	if (!chkFileExist(f))
	{
		printf("There are no facility data to modify in the system.\n");
		system("pause");
		return;
	}
	while (fread(&facData[dataCount], sizeof(Facility), 1, f) != 0)
	{
		dataCount++;
	}
	fclose(f);

	// Main Logic
	char facilityNameSearch[200];
	char choice[10];
	Facility *facNameSearchResult[100];
	Facility *facToModify;
	Facility newData;
	int facNameSearchResultIDX;
	do{
		facNameSearchResultIDX = 0;
		printf("Enter facility Name to modify: ");
		s_input(facilityNameSearch, 199);
		for (int a = 0; a < dataCount; a++)
		{
			if (strcmp(facilityNameSearch, facData[a].name) == 0)
			{
				facNameSearchResult[facNameSearchResultIDX] = &facData[a];
				facNameSearchResultIDX++;
			}
		}
		if (facNameSearchResultIDX == 0)
		{
			printf("There are no facility of name \"%s\"\n", facilityNameSearch);
			system("pause");
			choice[0] = 'y'; // to break the loop
			continue;
		}
		if (facNameSearchResultIDX != 1) // if there are multiple facility of same name
		{
			for (int a = 0; a < facNameSearchResultIDX; a++)
			{
				printf("\t%d. %s - %s\n", a + 1, facNameSearchResult[a]->id, facNameSearchResult[a]->name);
			}
			int userPickedFromSearchR;
			do {
				printf("\nWhich facility you wish to modify ? (%d - %d) ", 1, facNameSearchResultIDX);
				i_input(&userPickedFromSearchR);
			} while (userPickedFromSearchR < 1 || userPickedFromSearchR > facNameSearchResultIDX);
			facToModify = facNameSearchResult[userPickedFromSearchR - 1]; // -1 to match idx on facNameSearchResult
		}
		else
		{
			facToModify = facNameSearchResult[0];
		}

		strcpy(newData.id, facToModify->id);
		strcpy(newData.name, facToModify->name);
		strcpy(newData.remarks, facToModify->remarks);
		strcpy(newData.staffHandledID, facToModify->staffHandledID);
		newData.maintenanceDate.d = facToModify->maintenanceDate.d;
		newData.maintenanceDate.m = facToModify->maintenanceDate.m;
		newData.maintenanceDate.y = facToModify->maintenanceDate.y;
		newData.lastModified.d = facToModify->lastModified.d;
		newData.lastModified.m = facToModify->lastModified.m;
		newData.lastModified.y = facToModify->lastModified.y;
		do {
			printf("\tID               : %s\n", newData.id);
			printf("\tName             : %s\n", newData.name);
			printf("\tMaintenance Date : %02d/%02d\n", newData.maintenanceDate.d, newData.maintenanceDate.m);
			printf("\tRemarks          : %s\n", newData.remarks);
			printf("\n\t1. Change facility name\n"
				"\t2. Add/Modify Facilty Remarks\n"
				"\t3. Change Yearly Maintenance Date\n");
			printf("Choice ? ");
			getUserMenuChoice(choice, 9, "Choice ? ");
			switch (choice[0])
			{
			case '1':
				printf("Previous name: %s\n", facToModify->name);
				printf("New name     : ");
				s_input(newData.name, 199);
				break;
			case '2':
				printf("Previous Remarks: %s\n", facToModify->remarks);
				printf("New Remarks     : ");
				s_input(newData.remarks, 499);
				break;
			case '3':
				printf("Previous Maintenance Date    : %02d/%02d\n", facToModify->maintenanceDate.d, facToModify->maintenanceDate.m);

				// Get Date input
				int r = -999; // to store scanf output
				newData.maintenanceDate.y = 2020; // for the validation to work
				do {
					if (r != -999) {
						if (r != 2)
						{
							printf("Wrong Date format.\n");
						}
						else if (!validateDate(newData.maintenanceDate.d, newData.maintenanceDate.m, newData.maintenanceDate.y))
						{
							printf("Invalid date\n");
						}
					}
					printf("New Maintenance Date (dd/mm) : ");
					rewind(stdin);
					r = scanf("%d/%d", &newData.maintenanceDate.d, &newData.maintenanceDate.m);
					rewind(stdin);
				} while (r != 2 || !validateDate(newData.maintenanceDate.d, newData.maintenanceDate.m, newData.maintenanceDate.y));

				break;
			}
			printf("Old Facility Info:\n");
			printf("\tID               : %s\n", facToModify->id);
			printf("\tName             : %s\n", facToModify->name);
			printf("\tMaintenance Date : %02d/%02d\n", facToModify->maintenanceDate.d, facToModify->maintenanceDate.m);
			printf("\tRemarks          : %s\n", facToModify->remarks);

			printf("\nNew Facility Info:\n");
			printf("\tID               : %s\n", facToModify->id);
			printf("\tName             : %s\n", newData.name);
			printf("\tMaintenance Date : %02d/%02d\n", newData.maintenanceDate.d, newData.maintenanceDate.m);
			printf("\tRemarks          : %s\n", newData.remarks);

			printf("\nApply Changes ? (y = apply, r = back) ");
			getUserMenuChoice(choice, 9, "Apply Changes ? (y = apply, r = back) ");
			if (tolower(choice[0]) == 'y') {
				strcpy(facToModify->name, newData.name);
				strcpy(facToModify->remarks, newData.remarks);
				strcpy(facToModify->staffHandledID, sessionStaffID);
				facToModify->maintenanceDate.d = newData.maintenanceDate.d;
				facToModify->maintenanceDate.m = newData.maintenanceDate.m;
				facToModify->maintenanceDate.y = newData.maintenanceDate.y;
				getSystemDate(&facToModify->maintenanceDate);
				system("pause");
				break;
			}
		} while (tolower(choice[0]) == 'r');
		printf("Modify more facility ? (y=yes) ");
		getUserMenuChoice(choice, 9, "Modify more facility ? (y=yes) ");
	} while (tolower(choice[0]) == 'y');

	// End of Main Logic

	// End of Function
	f = fopen(facilityFilePath, "wb");
	for (int a = 0; a < dataCount; a++)
	{
		fwrite(&facData[a], sizeof(Facility), 1, f);
	}
	fclose(f);
}

void displayAllFacility()
{
	Facility facData[100];
	int dataCount = 0;
	FILE *f = fopen(facilityFilePath, "rb");
	if (!chkFileExist(f))
	{
		printf("There are no facility in the system.\n");
		system("pause");
		return;
	}
	while (fread(&facData[dataCount], sizeof(Facility),1,f) != 0)
	{
		printf("ID: %s\n", facData[dataCount].id);
		printf("Name: %s\n", facData[dataCount].name);
		printf("Yearly Maintenance Date: %02d/%02d\n", facData[dataCount].maintenanceDate.d, facData[dataCount].maintenanceDate.m);
		printf("Date Last Modified: %02d/%02d/%04d\n", facData[dataCount].lastModified.d, facData[dataCount].lastModified.m, facData[dataCount].lastModified.y);
		printf("Modified/Created by: ");
		// print staff name from ID
		Staff tmp;
		FILE *f2 = fopen(staffFilePath, "rb");
		while (fread(&tmp, sizeof(Staff), 1, f2) != 0)
		{
			if (strcmp(tmp.stfID, facData[dataCount].staffHandledID) == 0)
			{
				printf("%s\n", tmp.stfName);
				break;
			}
		}
		fclose(f2);
		// End of print staff name from ID
		printf("Remarks: %s\n", facData[dataCount].remarks);
	}
	fclose(f);
	system("pause");
}

int facilityMenu()
{
	char choiceText[][100] = {"Add New Facility", "Search Facility", "Modify Facility", "Display All Facility", "Return to console(Log Out)"};
	int choice = globalMainMenu("Facility Info Module", 5, choiceText);

	switch (choice)
	{
	case 1:
		addNewFacility();
		break;
	case 2:
		searchFacility();
		break;
	case 3:
		modifyFacility();
		break;
	case 4:
		displayAllFacility();
		break;		
	default:
		return;
	}
	return choice;

}

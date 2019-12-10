#include "stdcxx.h"
#include "facility.h"
#include "fusage.h"
#include "staff.h"
#include "userinfo.h"
#ifndef BOOKING_H
#define BOOKING_H

typedef struct
{
	char bookingID[10];
	Date currentDate;
	Time currentTime;
	Date bookingDate;
	int timeSlotsBooked[6];
	char usrID[20];
	char staffID[20];
	char facilityID[20];
} BookingData;

// Global variable
int err; // to keep track of input errors
// to store data while in here
Staff staffData[100];
int staffDataCount;
userData usrData[100];
int usrDataCount;
int facilityDataCount;

// Main functions
void bookingMain();
int bookingMenu();
void printBookingInfo();
void bookingBook();
void bookingSearchRecords();
int generateFilteredSearchResult(BookingData **filteredData, BookingData *data, int dataCount, int *isSet, Date *dotFrom, Date *dotTo, Date *bookFrom, Date *bookTo, int *timeslot);
void bookingModifyRecords();
void bookingDisplayAll();
void bookingDisplayFilters(BookingData *data, int dataCount);
int dispfilterDOT(int *isSet, Date *dotFrom, Date *dotTo);
int dispfilterBookingDate(Date *bookingDateFrom, Date *bookingDateTo);
int dispfilterTimeslotBooked(int *timeslot);
int dispFilterUserInvolved(char userIDsfilter[][100], int *uCount);
void printBookingDetails(char *bookingID, BookingData *data, int dataSize);

// Util Functions & Sub Functions
int readBookingDataIntoStructArray(BookingData *data, int size);
void writeBookingDataIntoFile(BookingData *data, int dataCount);
void incrementBookingID(char *oldStaffID);
int checkForTimeslotsAvailablity(int *timeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID);
int getTimeslotBooked(int *timeslot);

// Functions for BIP (Book-In-Progress)
int bipChangeFacility(char *userPickedfacilityID);
int bipChangeBookingDate(Date *bookingDate);
int bipChangeTimeslot(int *userPickedtimeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID);

// Functions for obtaining data from other modules
void readDataFromOtherModules();
Staff* getStaffDataByID(char *id);
userData* getUserDataByID(char *id);

// login functions
int _staffLogin(char *staffID, int size);
int _usrLogin(char *usrID, int size);
#endif
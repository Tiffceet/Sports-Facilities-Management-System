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
Facility facData[100];
int facilityDataCount;

char mode; // to keep track of what mode are the system in. 'u' if usermode, 's' if staffmode

// Main functions
void bookingMain();
int bookingMenu();
void printBookingInfo();
void bookingBook();
void bookingSearchRecords(int showRawRecordsOnly, BookingData **filteredRecords, int *filteredRecordsCount, int requireUserLogin, char passedUID[], BookingData *passedData, int passedDataCount);
int modifySpecificBooking(BookingData *bookingToModify, BookingData *data, int dataCount);
int generateFilteredSearchResult(BookingData **filteredData, BookingData *data, int dataCount, int *isSet, Date *dotFrom, Date *dotTo, Date *bookFrom, Date *bookTo, int *timeslot, Staff **staffFilter, int sCount, userData **userFilter, int uCount, Facility **facFilter, int fCount);
void bookingModifyRecords();
void bookingDisplayAll();
void bookingDisplayFilters(BookingData *data, int dataCount, char userID[]);
int dispfilterDOT(int *isSet, Date *dotFrom, Date *dotTo);
int dispfilterBookingDate(Date *bookingDateFrom, Date *bookingDateTo);
int dispfilterTimeslotBooked(int *timeslot);
int dispFilterUserInvolved(userData **userIDsfilter, int *uCount);
int dispFilterStaffInvovled(Staff **staffIDFilter, int *sCount);
int dispFilterFacInvolved(Facility **facFilter, int *fCount);
void printBookingDetails(char *bookingID, BookingData *data, int dataSize);

// Util Functions & Sub Functions
int readBookingDataIntoStructArray(BookingData *data, int size);
void writeBookingDataIntoFile(BookingData *data, int dataCount);
void incrementBookingID(char *oldStaffID);
int checkForTimeslotsAvailablity(int *timeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID);
int checkOverallTimeslotsAvailablity(int *timeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityName);
int getTimeslotBooked(int *timeslot);
int getTimeslotArrayCount(int *timeslot);

// Functions for BIP (Book-In-Progress)
int bipChangeFacility(char *userPickedfacilityID);
int bipChangeBookingDate(Date *bookingDate);
int bipChangeTimeslot(int *userPickedtimeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID);

// Functions for obtaining data from other modules
void readDataFromOtherModules();
Staff* getStaffDataByID(char *id);
userData* getUserDataByID(char *id);
Facility* getFacilityByID(char *id);

// login functions
int _usrLogin(char *usrID, int size);
int _staffPWReauth();

// functions to deal with facility module
int findNextFreeFacID(char facName[], char *facID, Date *bookingDate, int bookingSlotIDX);
int getFacilityCount(char facilityName[]);

#endif
#include "stdcxx.h"
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
char bookingFilePath[1024];
int err; // to keep track of input errors

// Main functions
void bookingMain();
int bookingMenu();
void printBookingInfo();
void bookingBook();
void bookingSearchRecords();
void printFilteredSearchResult(BookingData *data, int *isSet, Date *dotFrom, Date *dotTo, Date *bookFrom, Date *dateTo, int *timeslot);
void bookingModifyRecords();
void bookingDisplayAll();
void bookingDisplayFilters(BookingData *data, int dataCount);
int dispfilterDOT(int *isSet, Date *dotFrom, Date *dotTo);
int dispfilterBookingDate(Date *bookingDateFrom, Date *bookingDateTo);
int dispfilterTimeslotBooked(int *timeslot);

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
#endif
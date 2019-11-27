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
void bookingSeachRecords();
void bookingModifyRecords();
void bookingDisplayAll();

// Util Functions & Sub Functions
int readBookingDataIntoStructArray(BookingData *data, int size);
void writeBookingDataIntoFile(BookingData *data, int dataCount);
void incrementBookingID(char *oldStaffID);
void askUserForBookingDate(Date *userPickedDate);
int checkForTimeslotsAvailablity(int *timeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID);
#endif
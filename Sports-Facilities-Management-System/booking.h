#ifndef BOOKING_H
#define BOOKING_H

// Main functions
void bookingMain();
int bookingMenu();
void printBookingInfo();
void bookingBook();
void bookingSeachRecords();
void bookingModifyRecords();
void bookingDisplayAll();

// Util Functions
void incrementBookingID(char *oldStaffID);
void askUserForBookingDate(Date *userPickedDate);
void checkForTimeslotsAvailablity(int *timeslot, BookingData *data, int dataSize, Date *bookingDate, char *facilityID);
// Global variable
char bookingFilePath[1024];
int err; // to keep track of input errors
#endif
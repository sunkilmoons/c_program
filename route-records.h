#include <stdio.h>

typedef struct RouteRecord_struct
{
    char origin[4];
    char destination[4];
    char airline[3];
    int passengers[6];

} RouteRecord;

typedef enum SearchType
{
    ROUTE,
    ORIGIN,
    DESTINATION,
    AIRLINE
} SearchType;

/*
This function goes through the CSV file and counts the number of total records (not including the header)
Dynamically allocate memory for an array of RouteRecord’s based on the count.
Each RouteRecord struct object has an array of 6 integers to hold the number of passengers for six months. Initialize each of these integer values to 0. You do not need to initialize the other data members in the struct.
Rewind the file pointer
Return the pointer to the array you dynamically allocated.
*/
RouteRecord *createRecords(FILE *fileIn);

/*
This function will process the data in the CSV file. Essentially, the code will go through each record, parse out the record, and enter it into the array. The function will follow these rules:
The function will call findAirlineRoute() to see if the exact route with the origin, destination, and airline was already entered in the array. If it was found, then you will update the existing record in your array with the passenger data for that month. Recall there should be six entries (one for each month) for each route operated by an airline. If the route operated by the airline does not already exist in the array, add this new route to the array.
The function returns the actual number of RouteRecord’s used in the array. The value returned will be less than the size of the array created since not all records in the original CSV file will be entered into the array. 
*/
int fillRecords(RouteRecord *r, FILE *fileIn);

/*
This RECURSIVE function finds a record in the RouteRecord array with the same origin and destination airport codes and airline. It returns the index number in which these three strings appear in the array. The function will return -1 if it cannot find these three strings in the same struct object.
*/
int findAirlineRoute(RouteRecord *r, int length, const char *origin, const char *destination, const char *airline, int curIdx);

/*
This function searches the RouteRecord array and prints out the results of the search.
You will traverse the array and compare specific data members against the keys.
The parameter st determines if the function is searching by ROUTE, ORIGIN, DESTINATION, AIRLINE.
For ORIGIN, DESTINATION, AIRLINE, key1 will hold the value you are looking for. For ROUTE, you are searching both the origin and destination, so key1 and key2 will hold those values, respectively, that you will use to compare against the data members. For example, if the search is by the destination: st will be equal to DESTINATION, key1 will have an airport code that the user entered, and you will compare each struct’s destination data member against the airport code.
You will print out the airline and the route for each matching value. Then, you will print out the total number of passengers on all matching records, total number of passengers by month for all matching records, as well as average numbers of passengers per month. Note that you must handle any instances where you the search has 0 results.
*/
void searchRecords(RouteRecord *r, int length, const char *key1, const char *key2, SearchType st);

// This function prints the menu
void printMenu();
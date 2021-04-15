#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "route-records.h"

RouteRecord *createRecords(FILE *fileIn)
{
    int lineCount = 0;
    char c;

    for (c = getc(fileIn); c != EOF; c = getc(fileIn))
    {
        if (c == '\n')
            lineCount++;
    }
    lineCount--;

    printf("Line count is: %d\n", lineCount);

    RouteRecord *routes;

    routes = malloc(sizeof(*routes) * lineCount);

    for (int i = 0; i < lineCount; ++i)
    {
        for (int p = 0; p < 6; ++p)
            routes[i].passengers[p] = 0;
    }

    rewind(fileIn);

    return routes;
}

int fillRecords(RouteRecord *r, FILE *fileIn)
{
    int numRecords = 0;
    char buffer[1024];

    int row = 0;
    int column = 0;

    int length = 0;
    char c;

    for (c = getc(fileIn); c != EOF; c = getc(fileIn))
    {
        if (c == '\n')
            length++;
    }
    length--;

    rewind(fileIn);

    while (fgets(buffer, 1024, fileIn))
    {
        column = 0;

        row++;

        if (row == 1)
            continue;

        char *value = strtok(buffer, ",");

        RouteRecord record;
        int month;

        while (value)
        {
            switch (column)
            {
            case 0: // month
                // sscanf(value, "%d", &month);
                month = *value - '0';
                month--;
                break;

            case 1: // origin
                // printf("\tOrigin: ");
                strcpy(record.origin, value);
                break;

            case 2: // destination
                // printf("\tDestination: ");
                strcpy(record.destination, value);
                break;

            case 3: // airline
                // printf("\tAirline: ");
                strcpy(record.airline, value);
                break;

            case 4: // passenger category
                // printf("\tPassenger Category: ");
                break;

            case 5: // num passengers
                // printf("\tNum passengers: ");
                sscanf(value, "%d", &record.passengers[month]);
                break;
            default:
                break;
            }
            // printf("%s", value);
            value = strtok(NULL, ",");
            column++;
        }

        // printf("Origin: %s\tDest: %s\tAirline: %s\tPassengers: %d\n", record.origin, record.destination, record.airline, record.passengers[month]);

        int routeIdx = findAirlineRoute(r, length, record.origin, record.destination, record.airline, -1);

        if (routeIdx == -1)
        {
            // printf("Adding record to records... at index: %d\n", row - 2);
            strcpy(r[row - 2].origin, record.origin);
            strcpy(r[row - 2].destination, record.destination);
            strcpy(r[row - 2].airline, record.airline);
            r[row - 2].passengers[month] = record.passengers[month];
            numRecords++;
        }
        else
        {
            // printf("Updating record... at index: %d\n", routeIdx);
            r[routeIdx].passengers[month] += record.passengers[month];
        }

        // printf("Row: %d\n", row - 2);
    }

    rewind(fileIn);

    return numRecords;
}

int findAirlineRoute(RouteRecord *r, int length, const char *origin, const char *destination, const char *airline, int curIdx)
{
    int newIdx = curIdx + 1;

    // printf("%d\n", newIdx);

    if (newIdx < length)
    {
        if ((strcmp(r[newIdx].origin, origin) + strcmp(r[newIdx].destination, destination) + strcmp(r[newIdx].airline, airline)) == 0)
        {
            return newIdx;
        }
        return findAirlineRoute(r, length, origin, destination, airline, newIdx);
    }
    else
    {
        return -1;
    }
}

void searchRecords(RouteRecord *r, int length, const char *key1, const char *key2, SearchType st)
{
    int matches = 0;
    int totalPassengers = 0;
    int monthTotals[6] = {0, 0, 0, 0, 0, 0};

    switch (st)
    {
    case ROUTE:
        printf("Searching by route...\n");
        for (int i = 0; i < length; ++i)
        {
            if (strcmp(r[i].origin, key1) + strcmp(r[i].destination, key2) == 0)
            {
                printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                matches++;
                for (int m = 0; m < 6; ++m)
                {
                    monthTotals[m] += r[i].passengers[m];
                }
            }
        }
        break;

    case ORIGIN:
        printf("Searching by origin...\n");
        for (int i = 0; i < length; ++i)
        {
            if (strcmp(r[i].origin, key1) == 0)
            {
                printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                matches++;
                for (int m = 0; m < 6; ++m)
                {
                    monthTotals[m] += r[i].passengers[m];
                }
            }
        }
        break;

    case DESTINATION:
        printf("Searching by destination...\n");
        for (int i = 0; i < length; ++i)
        {
            if (strcmp(r[i].destination, key1) == 0)
            {
                printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                matches++;
                for (int m = 0; m < 6; ++m)
                {
                    monthTotals[m] += r[i].passengers[m];
                }
            }
        }
        break;

    case AIRLINE:
        printf("Searching by airline...\n");
        for (int i = 0; i < length; ++i)
        {
            if (strcmp(r[i].airline, key1) == 0)
            {
                printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                matches++;
                for (int m = 0; m < 6; ++m)
                {
                    monthTotals[m] += r[i].passengers[m];
                }
            }
        }
        break;
    }

    for (int m = 0; m < 6; ++m)
    {
        totalPassengers += monthTotals[m];
    }

    printf("\n%d matches were found.\n", matches);

    printf("\nStatistics\n");
    printf("Total Passengers: %d\n", totalPassengers);
    for (int m = 0; m < 6; ++m)
    {
        printf("Total Passengers in Month %d:\t%d\n", m + 1, monthTotals[m]);
    }
    printf("\nAverage Passengers per Month:\t%d\n", totalPassengers / 6);
}

void printMenu()
{
    printf("\n\n######### Airline Route Records Database MENU #########\n");
    printf("1. Search by Route\n");
    printf("2. Search by Origin Airport\n");
    printf("3. Search by Destination Airport\n");
    printf("4. Search by Airline\n");
    printf("5. Quit\n");
    printf("Enter your selection: ");
}

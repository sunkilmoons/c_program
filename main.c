#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "route-records.h"

int main(int argc, char *argv[])
{
    /* 1. Declare variables here */

    RouteRecord *records;
    int selection = -1;
    int isDone = 0;
    char key1[4];
    char key2[4];

    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */

    if (argc < 2)
    {
        printf("ERROR: Missing file name\n");
        return -1;
    }

    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */

    printf("Opening %s\n", argv[1]);

    FILE *fileIn = fopen(argv[1], "r");

    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
    if (fileIn == NULL)
    {
        printf("ERROR: Could not open file \"%s\"\n", argv[1]);
        return -1;
    }

    /* 5. Do the following to load the records into an array of RouteRecords
    	
    		5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
    		
    		5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
    		
    		5.3 Close the the file.
    */

    records = createRecords(fileIn);

    int uniqueRoutesCount = fillRecords(records, fileIn);

    printf("Unique routes operated by airlines: %d\n", uniqueRoutesCount);

    fclose(fileIn);

    /* 6. Create an infinite loop that will do the following:
    
    		6.1 Call printMenu()
    		
    		6.2 Ask the user to input a value for the menu
    		
    		6.3 Handle the case in which a non-integer value is entered
    		
    		6.4 Create a switch/case statement to handle all the menu options
    		
	    		6.4.1 Each option requires the user to enter a search key
	    		
	    		6.4.2 Quit needs to free the array
    
    */

    while (selection != 5)
    {
        printMenu();
        // fgets(input, sizeof(input), stdin) != NULL;
        if (scanf("%d", &selection) == 0)
        {
            printf("\nInvalid choice\n");
            fflush(stdin);
            continue;
        }

        if (selection < 1 || selection > 5)
        {
            printf("\nInvalid choice\n");
            continue;
        }

        switch (selection)
        {
        case 1:
            printf("Enter Origin: ");
            scanf("%s", key1);
            printf("Enter Destination: ");
            scanf("%s", key2);
            searchRecords(records, uniqueRoutesCount, key1, key2, ROUTE);
            break;

        case 2:
            printf("Enter Origin: ");
            scanf("%s", key1);
            searchRecords(records, uniqueRoutesCount, key1, key2, ORIGIN);
            break;

        case 3:
            printf("Enter Destination: ");
            scanf("%s", key1);
            searchRecords(records, uniqueRoutesCount, key1, key2, ORIGIN);
            break;

        case 4:
            printf("Enter Airline: ");
            scanf("%s", key1);
            searchRecords(records, uniqueRoutesCount, key1, key2, ORIGIN);
            break;

        case 5:
            isDone = 1;
            break;
        }

        if (isDone == 1)
        {
            printf("Good-bye!\n");
            continue;
        }
    }

    return 0;
}
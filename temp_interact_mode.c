#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp_function.h"

#define MAX_LEN_FILENAME 100

extern struct TemperatureData records[MAX_RECORDS_PER_MONTH * MAX_MONTHS];
extern struct MonthlyStatistics monthlyStatistics[MAX_RECORDS_PER_MONTH * MAX_MONTHS];
extern struct YearlyStatistics yearlyStatistics;

void showInteractMenu()
{
    const char *PASS_FILE_EXTENSION = ".csv";

    char *extension = NULL;
    char filename[MAX_LEN_FILENAME];
    char saveFilename[MAX_LEN_FILENAME];

    int numEntries = 0;
    int choice = 0;

    do
    {
        printf("\nMenu:\n");
        printf("1. Open file\n");
        printf("2. Show statistics for all months\n");
        printf("3. Show statistics for one month\n");
        printf("4. Show statistics for the year\n");
        printf("5. Save statistics to a file\n");
        printf("0. Exit\n");
        printf("Select an action: ");
        scanf("%d", &choice);

        putchar('\n');
        switch (choice)
        {
        case 1:
            printf("Enter file name: ");
            scanf("%s", filename);

            extension = strrchr(filename, '.');
            if (extension == NULL || strcmp(extension, PASS_FILE_EXTENSION) != 0)
            {
                fprintf(stderr, "Wrong file extension. Please try again.\n");
                continue;
            }

            numEntries = parseCSVFile(filename, records);
            if (numEntries != -1)
            {
                calculateStatistics(records, numEntries, monthlyStatistics, &yearlyStatistics);
                fprintf(stderr, "%s file was opened successfully.", filename);
            }

            break;
        case 2:
        case 3:
        case 4:
        case 5:
            if (numEntries == 0)
            {
                fprintf(stderr, "Input file is required. Please open file.\n");
                continue;
            }

            switch (choice)
            {
            case 2:
                showMonthlyStatistics(stdout, monthlyStatistics);
                break;
            case 3:
                printf("Select month: ");
                int month = 0;
                scanf("%d", &month);

                if (month < 0 || month > 12)
                {
                    fprintf(stderr, "Wrong input month. Please try again.\n");
                    continue;
                }
                showMonthStatistics(stdout, monthlyStatistics, month);
                break;
            case 4:
                showYearlyStatistics(stdout, &yearlyStatistics);
                break;
            case 5:
                printf("Enter file name: ");
                scanf("%s", saveFilename);

                FILE *fo = fopen(saveFilename, "w");

                showMonthlyStatistics(fo, monthlyStatistics);
                showYearlyStatistics(fo, &yearlyStatistics);

                fclose(fo);
                break;
            }

            break;
        case 0:
            printf("The program is completed.\n");
            break;
        default:
            printf("Invalid selection. Try again.\n");
        }
    } while (choice != 0);
}
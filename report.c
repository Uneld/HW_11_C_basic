#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "temp_function.h"
#include "temp_interact_mode.h"

struct TemperatureData records[MAX_RECORDS_PER_MONTH * MAX_MONTHS];
struct MonthlyStatistics monthlyStatistics[MAX_RECORDS_PER_MONTH * MAX_MONTHS];
struct YearlyStatistics yearlyStatistics;

int main(int argc, char *argv[])
{
    const char *PASS_FILE_EXTENSION = ".csv";

    char *filename = NULL;
    char *extension = NULL;

    char *saveFilename = NULL;
    int month = 0;
    int opt = 0;
    int numEntries;

    while ((opt = getopt(argc, argv, "hf:m:s:i")) != -1)
    {

        switch (opt)
        {
        case 'h':
            printf("This program calculates the statistics of temperature data in a CSV file.\n");
            printf("-f filename.csv: the input file to process (required)\n");
            printf("-m month: the month for statistics output is 1-12 (optional)\n");
            printf("-s filename: save output in file (optional)\n");
            printf("-i enter to interactive mode (optional)\n");

            return 0;
        case 'f':
            filename = optarg;
            break;
        case 'm':
            month = atoi(optarg);
            break;
        case 's':
            saveFilename = optarg;
            break;
        case 'i':
            printf("Welcome to interactive mode\n");
            showInteractMenu();

            return 0;
        default:
            printf("This program calculates the statistics of temperature data in a CSV file.\n");
            printf("Usage: [-h for help] \n");

            return 1;
        }
    }

    if (filename == NULL)
    {
        printf("This program calculates the statistics of temperature data in a CSV file.\n");
        fprintf(stderr, "Input file is required. Use -f option.\n");
        printf("Usage: [-h for help] \n");
        return 1;
    }

    extension = strrchr(filename, '.');
    if (extension == NULL || strcmp(extension, PASS_FILE_EXTENSION) != 0)
    {
        fprintf(stderr, "Wrong file extension. Please try again.\n");
        return 1;
    }

    if (month < 0 || month > 12)
    {
        fprintf(stderr, "Wrong input month. Please try again.\n");
        return 1;
    }

    numEntries = parseCSVFile(filename, records);
    calculateStatistics(records, numEntries, monthlyStatistics, &yearlyStatistics);

    if (month == 0)
    {
        showMonthlyStatistics(stdout, monthlyStatistics);
        showYearlyStatistics(stdout, &yearlyStatistics);
    }
    else
    {
        showMonthStatistics(stdout, monthlyStatistics, month);
    }

    if (saveFilename != NULL)
    {
        FILE *fo = fopen(saveFilename, "w");

        if (month == 0)
        {
            showMonthlyStatistics(fo, monthlyStatistics);
            showYearlyStatistics(fo, &yearlyStatistics);
        }
        else
        {
            showMonthStatistics(fo, monthlyStatistics, month);
        }

        fclose(fo);
    }

    return 0;
}

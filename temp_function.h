#ifndef TEMP_FUNCTION_H
#define TEMP_FUNCTION_H

#define MAX_DATA_ROWS 10000
#define MAX_TEMP_VALUE 99
#define MIN_TEMP_VALUE -99
#define MAX_MONTHS 12
#define MAX_RECORDS_PER_MONTH 44640

struct TemperatureData
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int temperature;
};

struct MonthlyStatistics
{
    int year;
    int month;
    float averageTemperature;
    int minTemperature;
    int maxTemperature;
    int count;
};

struct YearlyStatistics
{
    float averageTemperature;
    int minTemperature;
    int maxTemperature;
};

int parseCSVFile(const char *filename, struct TemperatureData *data);
void calculateStatistics(struct TemperatureData *data, int numEntries, struct MonthlyStatistics *statistics, struct YearlyStatistics *yearlyStatistics);

void showYearlyStatistics(FILE *const stream, struct YearlyStatistics *statistics);
void showMonthlyStatistics(FILE *const stream, struct MonthlyStatistics *statistics);
void showMonthStatistics(FILE *const stream, struct MonthlyStatistics *statistics, int month);

#endif /* TEMP_FUNCTION_H */

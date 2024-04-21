# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=gcc
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-c -Wall -std=c99

all: temperature_stats

temperature_stats: report.o temp_function.o temp_interact_mode.o
	$(CC) report.o temp_function.o temp_interact_mode.o -o temperature_stats

report.o: report.c
	$(CC) $(CFLAGS) report.c

temp_function.o: temp_function.c
	$(CC) $(CFLAGS) temp_function.c
	
temp_interact_mode.o: temp_interact_mode.c
	$(CC) $(CFLAGS) temp_interact_mode.c

clean:
	del *.o *.exe

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_RECORDS 1000

typedef struct {
    char name[100];
    char age[10];
    char city[100];
} Record;

int main() {
    struct timespec start, end;
    long long total_elapsed_ns = 0;

    for (int i = 0; i < 10; i++) {
        FILE *file;
        char line[MAX_LINE_LENGTH];
        Record records[MAX_RECORDS];
        int record_count = 0;

        clock_gettime(CLOCK_MONOTONIC, &start);

        file = fopen("test.csv", "r");
        if (!file) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }

        // Skip header
        fgets(line, sizeof(line), file);

        // Read and parse each line
        while (fgets(line, sizeof(line), file) && record_count < MAX_RECORDS) {
            line[strcspn(line, "\n")] = 0; // Remove newline

            char *token = strtok(line, ",");
            if (token != NULL) {
                strncpy(records[record_count].name, token, sizeof(records[record_count].name) - 1);
                
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strncpy(records[record_count].age, token, sizeof(records[record_count].age) - 1);
                    
                    token = strtok(NULL, ",");
                    if (token != NULL) {
                        strncpy(records[record_count].city, token, sizeof(records[record_count].city) - 1);
                        record_count++;
                    }
                }
            }
        }

        fclose(file);

        clock_gettime(CLOCK_MONOTONIC, &end);

        long long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + 
                             (end.tv_nsec - start.tv_nsec);
        total_elapsed_ns += elapsed_ns;
    }

    double average_elapsed_us = (total_elapsed_ns / 10) / 1000.0;
    printf("Average CSV Parse Time: %.3f µs\n", average_elapsed_us);

    return EXIT_SUCCESS;
}
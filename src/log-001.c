/*
 * implementation of functions related to logging our data
 */
#include "../include/log-001.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/*
 * Function that takes care of logging with variadic function. When called
 * behavior is returned to STDOUT + log file in /logs
 *
 * <---------- FIX DUMP TO LOG ---------->
 */
static void logging(const char *format, ...) {
    //static FILE *log_file_ptr;
      
    va_list args, args2;
    va_start(args, format);
    //FILE *file_ptr;
    //char log_file[] = "logs/TEST-LOG-001.txt";
    //log_file_ptr = fopen("logs/TEST-LOG-001.txt", "w");
    if (log_file_ptr) {
        va_start(args2, format);
        va_copy(args2, args);
        vfprintf(log_file_ptr, format, args2);
        fprintf(log_file_ptr, "\n");
        va_end(args2);
    }   
    fprintf(stderr, "LOG: ");
    //va_start(args, format);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);

    // fprintf(stderr, "\n");
    // fclose(log_file_ptr);

    // fclose(file_ptr);
}


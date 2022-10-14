/*
 * implementation of functions related to logging our data
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../../include/log.h"
#include "../../include/util.h"

// pointer for output log file
FILE *log_out;

// keep track of session
static int SESSION_NUM;

/*
 * function to print the current time to our log files
 */
char* timestamp() {
    int size = 0;
    time_t time_iter;
    char *buffer;

    time_iter = time(NULL);

    // retrieve current time
    char *time_str = asctime(localtime(&time_iter));
    // this deletes the carriage return \n
    time_str[strlen(time_str) - 1] = 0;

    // square braces
    size = strlen(time_str) + 1 + 2;
    buffer = (char*)malloc(size);

    // rm_spc(time_str);
    rep_spc(time_str);
    
    memset(buffer, 0x0, size);
    snprintf(buffer, size, "[%s]", time_str);

    return buffer;
}

/*
 * Function that takes care of logging with variadic function. When called
 * behavior is returned to STDOUT + log file in /logs
 *
 * <---------- FIX DUMP TO LOG ---------->
 */
void logging(char* file_name, int line, char *format, ...) {
    va_list list;
    char *ptr_p, *ptr_s;
    int i;

    /* use this for checking if the file exists and appending or writing
     * accordingly
     *
    if(SESSION_NUM > 0)
      fp = fopen ("log.txt","a+");
    else
      fp = fopen ("log.txt","w");
    */
    // char *test_file = ("logs/TEST-LOG-001%s.txt", timestamp());
    // this hardcodes a limit on length of file
    // char log_out[64];
    // struct tm *stamp;
    // time_t current = time(NULL);
    // stamp = gmtime(&current);
    // strftime(log_out, sizeof(log_out), "logs/TEST-LOG-001_%Y-%m-%d_%H:%M:%S.txt", stamp);
    //log_out = fopen("logs/TEST-LOG-001%s.txt", timestamp(), "w");
    //log_out = fopen("logs/TEST-LOG-001.txt", "a+");
    // log_file = ("logs/TEST-LOG-110%s.txt", timestamp());

    // buffer of 256
    char buffer[0x100];

    snprintf(buffer, sizeof(buffer), "logs/LOG-%s.txt", timestamp());

    log_out = fopen(buffer, "w+");
    // log_out = fopen(test_file, "w+");
    // fopen(log_out, "w+");

    fprintf(log_out, "%s", timestamp());
    fprintf(log_out, "[%s][line: %d] ", file_name, line);

    va_start(list, format);

    for (ptr_p = format; *ptr_p; ++ptr_p) {
        if (*ptr_p != '%')
            fputc(*ptr_p, log_out);
            // sprintf(ptr_p, log_out);

        else {
            switch (*++ptr_p) {

                // string
                case 's':
                    ptr_s = va_arg(list, char *);
                    fprintf(log_out, "%s DBG0", ptr_s);
                    // sprintf(log_out, "%s", ptr_r);
                    continue;

                // integer
                case 'd':
                    i = va_arg(list, int);
                    fprintf(log_out, "%d DBG1", i);
                    // sprintf(log_out, "%d", switch_arg);
                    continue;

                default:
                    fputc(*ptr_p, log_out);
                    // sprintf(ptr_p, log_out);
            }
        }
    }
    va_end(list);
    fputc('\n', log_out);
    fclose(log_out);

    /* leaving because I might use this still
    va_list args_file, args_stdout;

    fprintf(stderr, "LOG: ");

    va_start(args_file, format);
    va_start(args_stdout, format);

    vfprintf(file_ptr, format, args_file);
    vfprintf(stderr, format, args_stdout);

    fflush(file_ptr);
    fflush(stderr);

    va_end(args_file);
    va_end(args_stdout);

    fprintf(stderr, "\n");
    */
    /*
    va_list args;
    fprintf( stderr, "LOG: " );
    va_start( args, format );
    vfprintf( stderr, format, args );
    va_end( args );
    fprintf( stderr, "\n" );
    */
}


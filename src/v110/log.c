/*
 * implementation of functions related to logging our data
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../include/log.h"

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

    memset(buffer, 0x0, size);
    snprintf(buffer, size, "[%s]", time_str);

    return buffer;
}
/*
int stampfile() {
    time_t rawtime;
    char buffer[255];
    time(&rawtime);

    sprintf(buffer,"logs/TEST-LOG-001_%s",ctime(&rawtime) );
    
    char *p = buffer;
    
    for (; *p; ++p) {
        if (*p == ' ')
                *p = '_';
    }
    
    printf("%s",buffer);
    fopen(buffer,"w");

    return 0;
}
*/


/*
 * Function that takes care of logging with variadic function. When called
 * behavior is returned to STDOUT + log file in /logs
 *
 * <---------- FIX DUMP TO LOG ---------->
 */
void logging(char* file_name, int line, char *format, ...) {
    va_list list;
    char *ptr_p, *ptr_r;
    int switch_arg;

    /* use this for checking if the file exists and appending or writing
     * accordingly
    if(SESSION_TRACKER > 0)
      fp = fopen ("log.txt","a+");
    else
      fp = fopen ("log.txt","w");
    */
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [64];
    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime(buffer, 64, "logs/TEST-LOG-001_%x_%X.txt", timeinfo);

    log_out = fopen(buffer, "w+");
    //log_out = fopen("logs/TEST-LOG-001.txt", "w+");
    fprintf(log_out, "%s", timestamp());
    fprintf(log_out, "[%s][line: %d] ", file_name, line);

    va_start(list, format);

    for (ptr_p = format; *ptr_p; ++ptr_p) {
        if (*ptr_p != '%')
            fputc(*ptr_p, log_out);

        else {
            switch (*++ptr_p) {

                // string
                case 's':
                    ptr_r = va_arg(list, char *);
                    fprintf(log_out, "%s", ptr_r);
                    continue;

                // integer
                case 'd':
                    switch_arg = va_arg(list, int);
                    fprintf(log_out, "%d", switch_arg);
                    continue;

                default:
                    fputc(*ptr_p, log_out);
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


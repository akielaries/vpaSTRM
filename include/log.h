/*
 * function declaration for logging data 
 */

#ifndef LOG_H
#define LOG_H

char* timestamp();

void logging(char* file_name, int line, char *format, ...);
#define LOGGING(...) logging(__FILE__, __LINE__,__VA_ARGS__)

#endif




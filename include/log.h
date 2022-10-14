/*
 * function declaration for logging data 
 */

#ifndef LOG001_h
#define LOG001_H

void rm_spc(char *str);

void logging(char* file_name, int line, char *format, ...);
#define LOGGING(...) logging(__FILE__, __LINE__,__VA_ARGS__)

#endif




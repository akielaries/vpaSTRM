#include <stdio.h>
#include <stdarg.h>


void send_string(FILE *fd, char *fmt, ...)
{
    va_list args_fd, args_stdout;

    va_start(args_fd, fmt);
    va_start(args_stdout, fmt);

    vfprintf(fd, fmt, args_fd);
    vfprintf(stdout, fmt, args_stdout);

    fflush(fd);
    fflush(stdout);

    va_end(args_fd);
    va_end(args_stdout);
}

int main()
{
    FILE *fp = fopen("../../logs/TEST-out.txt", "w");

    send_string(fp, "hello, ");
    send_string(fp, "world %d times!\n", 42);

    fclose(fp);

    return 0;
}


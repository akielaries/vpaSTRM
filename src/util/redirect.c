/*
 * This file acts as a driver for a functionality I will call 
 * display stats. In this file we will take care of logging 
 * and call some functions
 */

#include "../../include/redirect.h"
#include <stdio.h>

enum{SUCCESS, FAIL, STR_NUM = 6};


void print_str(char **str) {
    int index;

    for (index = 0; index < STR_NUM; index++) 
        printf("%s \n", str[index]);
}

int return_err(char *str) {
    printf("ERROR:  CANNOT OPEN %s \n", str);

    return FAIL;
}

/*
 * Function that will 'dump' our log data to a .txt file
 * essentially redirecting STDOUT->.txt
 */
//void log_dump() {
    //FILE *file_ptr;
    //file_ptr = fopen("../../logs/", "w+");
    
    
//}

int main(void) {
    //log_dump();

    char *str[STR_NUM] = {
        "Redirecting a standard stream to the text file.",
        "These 5 lines of text will be redirected", 
        "so many things you can do if you understand the",
        "concept, fundamental idea - try this one!",
        "--------------DONE--------------------------"
    };
    char filename[] = "../../logs/test-log-001.txt";
    int reval = SUCCESS;

    print_str(str);
    
    if (freopen(filename, "w", stdout) == NULL) {
        reval = return_err(filename);
    }
    else {
        print_str(str);
        fclose(stdout);
    }

    return reval;
}



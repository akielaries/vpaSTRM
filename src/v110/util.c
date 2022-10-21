/*
 * This file contains miscellaneous utility functions used through the vpaSTRM
 * project 
 */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../include/util.h"

/*
 * function to remove spaces from a given string
 */
void rm_spc(char *str) {
    int str_count = 0;
    int str_iter = 0;

    // traverse passed in string
    for (str_iter; str[str_iter]; str_iter++) {
        if (str[str_iter] != ' ') {
            str[str_count++] = str[str_iter];
        }
    }
    str[str_count] = '\0';
}

/*
 * function that takes in a string and replaces spaces with underscores
 */

void rep_spc(char *str) {
    int str_iter = 0;

    // traverse string
    while (str[str_iter]) {
        // if index is a whitespace value replace with underscore
        if (isspace((unsigned char)str[str_iter])) {
            str[str_iter] = '_';
        }
        str_iter++;
    }
}

/*
compares data, returns value greater than 0 if dataOne is larger
than dataTwo, returns value less than 0 if dataOne is less than dataTwo,
and returns 0 is data are the same.
*/
int compare_data(int a, int b) {
    if (a > b) {
        return 1;
    }   
    if (a < b) {
        return -1; 
    }   
    else {
        return 0;
    }   
}

/* 
 * function that swaps two variables of any type
 */
void swap_data(void* a, void* b, size_t s){
    void* tmp = malloc(s);
    memcpy(tmp, a, s);
    memcpy(a, b, s);
    memcpy(b, tmp, s);
    free(tmp);
}



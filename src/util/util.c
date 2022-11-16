/*
 * This file contains miscellaneous utility functions used through the vpaSTRM
 * project 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../include/util.h"

/*
 * functions for enclosing our console prints in color
 * format : \033[x;xxm
 * x can be 
 *      0: normal
 *      1: bold
 *      2: darker shade 
 *      3: italicized
 *      4: underlined
 *      5: flashing
 * xx represents a color
 */
void black() {
    printf("\033[1;30m");
}

void pink() {
    printf("\033[1;31m");
}

void green() {
    printf("\033[1;32m");
}

void yellow() {
    printf("\033[1;33m");
}

void blue() {
    printf("\033[1;34m");
}

void cyan() {
    printf("\033[1;36m");
}

void red() {
    printf("\033[1;35m");
}

void white() {
    printf("\033[1;37m");
}

void reset_color() {
    printf("\033[0m");
}

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


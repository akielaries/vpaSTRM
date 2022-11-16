/*
 * implementation of functions related to logging our data
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/log.h"
#include "../../include/util.h"


/*
 * function that returns the usage of vpaSTRM
 */
void usage_overview() {
    char src[10] = "./vpaSTRM";

    cyan();
    printf("vpaSTRM v1.0.2 2022, akielaries and vpaSTRM contributors\n"); 
    reset_color();
    printf("Lightweight computer vision software tool.\n\n");
    printf("USAGE: %s -[flags] [[in-file opts]]...[out-file]\n", src);
    printf("FLAGS:\n");
    printf("-d      decode\n");
    printf("-h      help\n");
    printf("more coming soon...\n");

    printf("\n");
    /*
     * printf("-l      log\n")
     * printf("-o      output\n");
     * printf("-e      encode\n");
     * printf("-r      rate\n");
     */
    
}

/*
 * function returning usage of decode functionality
 */
void usage_decode() {
    printf("-d, DECODE A VIDEO FILE TO A SERIES OF PICTURES.\n");
    printf("USAGE: ./vpaSTRM -d [in-file]\n");

    printf("\n");
}


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
void usage_overview (const char *argv0) {
    printf("vpaSTRM version 1.1.2 Copyright (c) 2022, Akiel Aries\n"); 
    printf("Light-weight computer vision software tool.\n\n");
    printf("USAGE: %s -[flags] [[in-file opts]]...[out-file]\n", argv0);
    printf("-d      decode\n");
    printf("-h      help\n");
    printf("more coming soon...\n");

    /*
     * printf("-o      output\n");
     * printf("-e      encode\n");
     * printf("-r      rate\n");
     */
    
}

/*
 * function returning usage of decode functionality
 */
void usage_decode (const char *argv1) {
    printf("-d, DECODE A VIDEO FILE TO A SERIES OF PICTURES.\n");
    printf("USAGE: ./vpaSTRM -d video.mp4\n");

    printf("\n");
}



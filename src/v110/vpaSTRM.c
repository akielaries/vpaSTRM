/* <--------------------------------------------------------------------------->
 * INCLUDE LICENSING DETAILS HERE
 *      - BE SURE TO LOOK AT FFMPEG'S DOCS AND CROSS REFERENCE LICENSING WITH
 *      OTHER LIBS AND DEPENDENCIES USED
 *
 * For now this file will serve as a test driver for the project.
 *
 * Ideally, this file needs to be figured out before any further 
 * implementations as they will prove difficult if argument passing for the 
 * core functionality is not done first. 
 *
 * More details as this goes...
 *
 * <--------------------------------------------------------------------------->
 */

/*
 * import libs
 */
#include "../../include/decode.h"
#include "../../include/log.h"
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

/*
 * Function that returns usage of the software
 */
void return_usage (const char *argv0) {
    printf("vpaSTRM, a light-weight computer vision software tool.\n", argv0);
    printf("USAGE: %s -[flags] [[in-file opts]]...[out-file]\n", argv0);
    printf("PRINT FULL USAGE FLAGS HERE\n");

    printf("\n");
}

/* <--------------------------------------------------------------------------->
 * MAIN DRIVER FOR vpaSTRM. ARGUMENTS ARE DEFINE HERE.
 * 
 * <--------------------------------------------------------------------------->
 */

int main (int argc, char *argv[]) {
    LOGGING("<-------------------------NEW-SESSION------------------------->");
     
    // set our arguments to values for passing around
    // int argc = 

    /*
     * omit '0' since the first argument first always be the same, './vpaSTRM'
     */
    int i = 1;

    // if there are no arguments passed in return the usage
    if (argv[1] == NULL) {
        return_usage(argv[0]);
    }
    // parse arguments 1 - N and compare argc val to a given string
    for (i; i < argc; i++) {
    // if (argv[1] != NULL) {
        
        // if the flag -d is passed in
        if (strcmp(argv[1], "-d") && i + 1 < argc) {
            
            // flag for decoding
            if (argv[2] != NULL) {
                // call decode driver
                decode_call(argc, argv);

                // save the argument to a value
                // return it for other functions to use
            }

        }
        else {
            return_usage(argv[0]);
        }
    }
    return 0;
}



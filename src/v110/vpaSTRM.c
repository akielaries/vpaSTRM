/*
 * For now this file will serve as a test driver for the project. This will be 
 * called when the -d flag is called. 
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

void return_usage(void) {
    LOGGING("vpaSTRM, a light-weight computer vision software tool");
    LOGGING("USAGE: ./vpaSTRM -[flags] [[input-file options]]...[output-file]");
    LOGGING("PRINT FULL USAGE FLAGS HERE");

    LOGGING("\n");
}

int main(int argc, char *argv[]) {
    int arg_iter = 1;

    // parse arguments and compare argc val to a given string
    for (arg_iter; arg_iter < argc; arg_iter++) {
        //if (!strcmp())
        /*
         * arg 1 is actually the dash (-) we use and the actual value of the 
         * flag will be arg 2
         */
        if (argv[arg_iter][1] == '-') {
            // flag for decoding
            if (argv[arg_iter][2] == 'd') {
                // call decode driver

                // save the argument to a value
                // return it for other functions to use
            }

        }

    }


}



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
#include "../../include/usage.h"
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


/* <--------------------------------------------------------------------------->
 * MAIN DRIVER FOR vpaSTRM. ARGUMENTS ARE DEFINED HERE.
 * 
 * <--------------------------------------------------------------------------->
 */

int main (int argc, char *argv[]) {
    // initialize our logging for this session
    //log_init();

    LOGGING("<-------------------------NEW-SESSION------------------------->");
     
    /*
     * omit '0' since the first argument first always be the same, './vpaSTRM'
     */
    int i = 1;

    // if there are no arguments passed in return the usage
    if (argv[1] == NULL) {
        usage_overview(argv[0]);
    }
    // parse arguments 1 - N and compare argc val to a given string
    for (i; i < argc; i++) {

        // if the flag -d is passed in
        if (strcmp(argv[i], "-d") == 0) {
            // increment argument
            i++;

            // if argv[2] is specified
            if (argv[i] != NULL) {
                // call decode driver
                decode_call(argc, argv);
                i++;
            }
            // argv[2] not specified
            else {
                usage_decode(argv[1]);
            }

        }
        // -h; help  
        else if (strcmp(argv[i], "-h") == 0) {
            usage_overview(argv[0]);
            i++;
        }
        else {
            // if no arguments/flags are recognized, return usage
            usage_overview(argv[0]);
            return -1;
        }
    }
    return 0;
}



/*
 * <--------------------------------------------------------------------------->
 *                    _____ ______________  ___                               |
 *                   /  ___|_   _| ___ \  \/  |                               |
 * __   ___ __   __ _\ `--.  | | | |_/ / .  . |                               |
 * \ \ / / '_ \ / _` |`--. \ | | |    /| |\/| |                               |
 *  \ V /| |_) | (_| /\__/ / | | | |\ \| |  | |                               |
 *   \_/ | .__/ \__,_\____/  \_/ \_| \_\_|  |_/                               |
 *       | |                                                                  |
 *       |_|                                                                  |
 *                                                                            |
 * <--------------------------------------------------------------------------->
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
#include "../include/decode.h"
#include "../include/usage.h"
#include "../include/log.h"
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
 *  -a  (!WKG)  = amount  | amount of frames we want converted
 *  -d  (WKG)   = decode  | convert video file into pictures 
 *  -e  (!WKG)  = encode  | convert pictures into a video file
 *  -f  (!WKG)  = format  | select file output type
 *  -h  (WKG)   = help    | displays usage
 *  -o  (!WKG)  = output  | select output
 *
 * <--------------------------------------------------------------------------->
 */
int main(int argc, char *argv[]) {
    LOGGING("<-------------------------NEW-SESSION------------------------->");
    
    /*
     * omit '0' since the first argument will always be the same, './vpaSTRM'
     */
    int i = 1;

    // if there are no arguments passed in return the usage
    if (argv[1] == NULL) {
        usage_overview();
    }
   
    // parse arguments 1 - N and compare argc val to a given string
    for (i; i < argc; i++) {

        // if flag -d is passed in as argv[1]
        if (strcmp(argv[i], "-d") == 0) {
            // increment arg. argv[1]->argv[2]
            i++;
        
            // if argv[2] is specified
            if (argv[i] != NULL) {
                // call decode driver
                decode_call(argc, argv);
                i++;
            }

            // argv[2] not specified
            else {
                printf("Error. Check arguments.\n");
                usage_decode();
            }
        }
        
        // -h; help  
        else if (strcmp(argv[i], "-h") == 0) {
            usage_overview();
            i++;
        }
        
        else {
            // if no arguments/flags are recognized, return usage
            usage_overview();
            return -1;
        }
    }
    return 0;
}


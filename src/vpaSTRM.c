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
#include "../include/decode.h"
#include "../include/usage.h"
#include "../include/log.h"
#include "../include/util.h"
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
 *  TODO -a  (!WKG)  = amount  | amount of frames we want converted
 *  -d  (WKG)   = decode  | convert video file into pictures 
 *  TODO -e  (!WKG)  = encode  | convert pictures into a video file
 *  TODO -f  (!WKG)  = format  | select file output type
 *  -h  (WKG)   = help    | displays usage
 *  TODO -o  (!WKG)  = output  | select output
 *
 * <--------------------------------------------------------------------------->
 */
int main(int argc, char *argv[]) {
    LOGGING("<-------------------------NEW-SESSION------------------------->");
    
    /*
     * omit '0' since the first argument will always be the same, './vpaSTRM'
     */
    
    extern char *optarg;
    extern int optind;
    // flags
    int f_flag = 0;

    // option parser
    int opt;

    if (argv[1] == NULL) {
        usage_overview();
        exit(1);
    }

    while ((opt = getopt(argc, argv, "if:lr")) != -1) {
        switch(opt) {
            case 'i':
            case 'l':
            case 'r':
                printf("OPTION PASSED IN: %c \n", opt);
                break;

            case 'f':
                f_flag = 1;
                printf("FILENAME: %s\n", optarg);
                break;

            case ':':
                printf("REQUIRED OPTION: %c \n", optopt);
                break;

            case '?':
                red();
                printf("ERR: Unknown option: %c\n", optopt);
                reset_color();
                usage_overview();
                break;
            
            default:
                printf("Unknown option. %c \n", opt);
                usage_overview();
                break;
        }
    }


    // mandatory f flag
    //if (f_flag == 0) {
    //    printf("Missing filename\n");
    //    exit(1);
    //}

    //else {
    //    usage_overview();
    //    exit(1);
    //}
    
    // parsing extra arguments
    if (optind < argc) {
        for (; optind < argc; optind++) {
            red();
            printf("ERR: Invalid/Extra arguments detected: %s\n", argv[optind]);
            reset_color();
            usage_overview();
        }
    }
    else {
        return 0;
    }

    // return 0;
    exit(0);
}


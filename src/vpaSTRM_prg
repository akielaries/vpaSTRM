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
#include <stdbool.h>
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
    
    /*<------------------------- TODO ------------------------->*/
    extern char *optarg;
    extern int optind;
    // flags
    bool null_flag = false, err = false; 
    bool f_flag = false, d_flag = false;

    // option parser
    int opt;

    if (argv[1] == NULL) {
        usage_overview();
        exit(1);
    }

    /*
     * For defining and parsing flags & args, the workflow is to look for 
     * flags(switch/case), then do some work on them based of the 
     * entries (conditionals). 
     * 
     * The syntax for defining a valid string of flags with getopt can be
     * tricky. The idea is to define which flags require arguments before/after
     *      - Any flag that requires a parameter with it is suffixed by ':'
     *          * for example: in the string "df:mps:" flags 'f' and 's' 
     *          require parametars after being called
     */
    while ((opt = getopt(argc, argv, ":d:f:hio:lr")) != -1) {
        switch(opt) {
            case 'i':
                printf("CALLED: %c\n", opt);
                break;

            case 'l':
                printf("CALLED: %c\n", opt);
                break;

            case 'r':
                printf("OPTION PASSED IN: %c \n", opt);
                break;

            case 'd': 
                d_flag = true;
                break;

            case 'f':
                f_flag = true;
                printf("FILENAME: %s\n", optarg);
                break;

            case 'h':
                usage_overview();
                break;
                exit(0);

            case 'o':
                printf("");
                break;

            case ':':
                null_flag = true;
                break;

            case '?':
                err = true;
                break;
            
            default:
                red();
                printf("Unknown Error\n");
                reset_color();
                usage_overview();
                break;
        }
    }

    if (d_flag) {
        printf("CAUGHT\n");
    }

    if (f_flag) {
        printf("Missing filename\n");
        exit(1);
    }

    //else {
    //    usage_overview();
    //    exit(1);
    //}

    /* Catching invalid flags and missing reqired arguments */
    if (null_flag) {
        red();
        printf("ERR: '-%c' requires an argument\n", optopt);
        reset_color();
        usage_overview();
    }
    else if (err) {
        red();
        printf("ERR: Unknown flag: '-%c'\n", optopt);
        reset_color();
        usage_overview();
    }
    
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
        //usage_overview();
        exit(0);
    }

    return 0;
}


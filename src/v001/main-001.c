/*
 * <--------------------------------------------------------------------------->
 *
 * MAIN DRIVER FUNCTION FOR THIS PROJECT
 *
 * INCLUDE LICENSING DETAILS HERE
 *      - BE SURE TO LOOK AT FFMPEG'S DOCS AND CROSS REFERENCE LICENSING WITH
 *      OTHER LIBS AND DEPENDENCIES USED
 *
 * F : format
 * D : duration
 * R : resolution
 * A : audio channels
 * D : decoding frames into .pgm format
 *
 * Overall purpose of this was to ensure ffmpeg + deopendencies were installed
 * correctly.
 *
 * http://ffmpeg.org/doxygen/trunk/index.html
 *
 * Main components
 *
 * Format (Container) - a wrapper, providing sync, metadata and muxing 
 *                      (multiplexing) for the streams.
 * Stream   - a continuous stream (audio or video) of data over time.
 * Codec    - defines how data are enCOded (from Frame to Packet)
 *          and DECoded (from Packet to Frame).
 * Packet   - are the data (kind of slices of the stream data) to be decoded 
 *          as raw frames.
 * Frame    - a decoded raw frame (to be encoded or filtered).
 * <--------------------------------------------------------------------------->
 */

/*
 * import libs
 */
#include "../../include/DEC-001.h"
#include "../../include/LOG-001.h"
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
 * THIS MAIN FUNCTION WILL CHANGE AS DEVELOPMENT PROGRESSES. 
 * EVENTUALLY I WANT MAIN TO BE IN ITS OWN FILE AND CALLING
 * OTHER "DRIVER" FILES BASED ON ARGUMENTS. FOR NOW, THIS 
 * WILL SERVE FINE FOR THE CURRENT VIDEO->PICTURE 
 * CONVERSION
 */
int main(int argc, const char *argv[]) {
    /* TODO */
    
    if (argc < 2) {
        printf("ERR: SPECIFY VIDEO FILE.\n");
        return 17;
    }

    LOGGING("initializing all the containers, codecs and protocols.");

    return 0;
}


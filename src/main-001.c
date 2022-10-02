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
 * <--Figure out what to do about importing libs, many files rely off the of -->
 * <--the same libs -->
 */

int main() {
    /* TODO */
    return 0;
}


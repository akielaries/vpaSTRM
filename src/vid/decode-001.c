/*
 * implementation of decoding the frames from the passed in file
 * and saving them to a greyscaled image 
 */
#include <stdlib.h>
#include <stdio.h>

static void grayscaled_frame(unsigned char *buffer, 
        int wrap,
        int xsize,
        int ysize,
        char *filename);

    /*
     * initialize variables
     * FILE     : pointer for our grayscaled output file (.pgm)
     * y_index  : int, when writing line by line, iterate by the size of
     *          the y axis
     */
    FILE *gs_output;
    gs_output = fopen(filename, "w");
    int y_index = 0;

    /*
     * write head for .pgm file format
     * Portable Graymap Format -> 
     * https://en.wikipedia.org/wiki/Netpbm_format#PGM_example
     */
    fprintf(gs_output, ""P5\n%d %d\n%d\n", xsize, ysize, 255");

    // write data line by line using ysize as target
    for (y_index; y_index < ysize; y_index++) {
        /*
         * write to file using functions params and outputing to
         * define file
         */
        fwrite(buffer + y_index * wrap, 1, xsize, gs_output);
    }
    // close file
    fclose(gs_output);
}



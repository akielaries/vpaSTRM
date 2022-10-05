/*
 * WRITE + FORMAT
 * This file contains some functions to save our inputs to a variety of 
 * different picture formats.
 *
 * PGM - PORTABLE GRAY MAP
 * PPM - PORTABLE PIX MAP 
 */

/*<--HEADERS-->*/
#include <stdio.h>
#include <stdlib.h>
#include <libavformat/avformat.h>

#include "../../include/WFMT-001.h"

#define BITS_SIZE 255

/*
 * TODO DESCRIBE THIS
 */
void save_pgm(unsigned char *buffer,
                int wrap,
                int xsize,
                int ysize,
                char *filename) {
    /*
     * initialize variables
     * FILE         : pointer for our grayscaled output file (.pgm)
     * y_index      : int, when writing line by line, iterate by the size of
     *          the y axis
     */
    FILE *pgm_file;
    pgm_file = fopen(filename, "w");
    int y_index = 0;

    /*
     * write head for .pgm file format
     * Portable Graymap Format ->
     * https://en.wikipedia.org/wiki/Netpbm_format#PGM_example
     */
    fprintf(pgm_file, "P5\n%d %d\n%d\n", xsize, ysize, BITS_SIZE);

    // write data line by line using ysize as target
    for (y_index; y_index < ysize; y_index++) {
        /*
         * write to file using functions params and outputing to
         * define file
         */
        fwrite(buffer + y_index * wrap, 1, xsize, pgm_file);
    }
    // close file
    fclose(pgm_file);
}

/*
 * TODO DESCRIBE THIS
 */
void save_ppm(AVFrame *p_frame,
                int width,
                int height,
                int i_frame) {
    /*
     * initialize variables
     * FILE         : pointer for our portable pixmap format file (.ppm)
     * sized_file   :
     * y_index      :
     */
    // file ptr for ppm
    FILE *ppm_file;
    char sized_file[32];
    int y_index = 0;

    // open our file to write
    sprintf(sized_file, "frame%d.ppm", i_frame);
    ppm_file = fopen(sized_file, "wb");

    if (ppm_file == NULL) {
        return;
    }

    /*
     * write header for our file
     * Portable Pix Map format ->
     * https://en.wikipedia.org/wiki/Netpbm#PPM_example
     */
    fprintf(ppm_file, "P6\n%d %d\n%d\n", width, height, BITS_SIZE);

    // write our data using y index
    for (y_index; y_index < height; y_index++) {
        fwrite(p_frame->data[0] + y_index * p_frame->linesize[0], 1,
                width * 3,
                ppm_file);
    }
    // close file
    fclose(ppm_file);
}


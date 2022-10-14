/*
 * Function declarations for our save functions to a number of different 
 * picture file formats
 */

#ifndef WFMT_H
#define WFMT_H

/*
 * converts image to a PGM file (Portable Gray Map), a grayscale
 * 2-dimensional image
 */
void save_pgm(unsigned char *buffer,
            int wrap,
            int xsize,
            int ysize,
            char *filename);

/*
 * saves our frames to a PPM file (Portable Pixmap Format), uses
 * text to store information about our image
 */
void save_ppm(AVFrame * p_frame,
            int width,
            int height,
            int i_frame);

#endif


/*
 * function declaration for decoding our packets and saving them as
 * grayscaled images
 */

#include <stdlib.h>
#include <stdio.h>

#ifndef DECODE_h
#define DECODE_H

// decodes our packets with calls to FFMPEG libs avformat and others
int decode_packet(AV_packet *p_packet, 
            AV_codec *p_codec, 
            AV_frame *p_frame);

/*
 * converts image to a PGM file (Portable Gray Map), a grayscale 
 * 2-dimensional image
 */
void frame_pgm(unsigned char *buffer, 
            int wrap,
            int xsize,
            int ysize,
            char *filename);

/*
 * saves our frames to a PPM file (Portable Pixmap Format), uses 
 * text to store information about our image
 */
void save_ppm(AV_frame * p_frame, 
            int width, 
            int height, 
            int i_frame);

#endif


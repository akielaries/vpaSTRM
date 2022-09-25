/*
 * function declaration for decoding our packets and saving them as
 * grayscaled images
 */

#ifndef DECODE_h
#define DECODE_H

static int decode_packet(AVPacket *pPacket, 
            AVCodecContext *pCodecContext, 
            AVFrame *pFrame);

static void grayscaled_frame(unsigned char *buffer, 
            int wrap, 
            int xsize,
            int ysize, 
            char *filename);

#endif




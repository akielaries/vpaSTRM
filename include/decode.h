/*
 * function declaration for decoding our packets and saving them as
 * grayscaled images
 */

#ifndef DECODE_h
#define DECODE_H

static int decode_packet(AVPacket *pPacket, 
            AVCodecContext *pCodecContext, 
            AVFrame *pFrame);

static void save_gray_frame(unsigned char *buf, 
            int wrap, 
            int xsize,
            int ysize, 
            char *filename);

#endif




/*
 * function declaration for decoding our packets and saving them as
 * grayscaled images
 */
#include <libavcodec/avcodec.h>

#ifndef DECODE_H
#define DECODE_H

// driver for decoding our packets 
int decode_call(int argc, char *argv[]);

// decodes our packets with calls to FFMPEG libs avformat and others
int decode(AVPacket *p_packet, 
            AVCodecContext *p_codec, 
            AVFrame *p_frame, 
            char *argv[]);

#endif


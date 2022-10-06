/*
 * function declaration for decoding our packets and saving them as
 * grayscaled images
 */
#include <libavcodec/avcodec.h>

#ifndef DECODE_h
#define DECODE_H

// decodes our packets with calls to FFMPEG libs avformat and others
int decode_packet(AVPacket *p_packet, 
            AVCodecContext *p_codec, 
            AVFrame *p_frame);

#endif


/*
 * function declaration for decoding our packets and saving them as
 * grayscaled images
 */

#ifndef DECODE_h
#define DECODE_H

// decodes our packets with calls to FFMPEG libs avformat and others
int decode_packet(AV_packet *p_packet, 
            AV_codec *p_codec, 
            AV_frame *p_frame);

#endif


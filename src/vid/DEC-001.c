/*
 * implementation of decoding the frames from the passed in file
 * and saving them to a greyscaled image 
 */

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "../../include/DEC-001.h"
#include "../../include/LOG-001.h"

#define BITS_SIZE 255

/*
 * DESCRIBE THIS FUNCTION
 */
int decode_packet(AV_packet *p_packet,
                AV_codec *p_codec,
                AV_frame *p_frame) {
    // Supply raw packet data as input to a decoder
    // https://ffmpeg.org/doxygen/trunk/group__lavc__decoding.html
    // #ga58bc4bf1e0ac59e27362597e467efff3
    int response = avcodec_send_packet(p_codec, p_packet);

    if (response < 0) {
        LOGGING("Error while sending a packet to the decoder: %s", 
                av_err2str(response));
        return response;
    }

    while (response >= 0) {
        /*
        * Return decoded output data (into a frame) from a decoder
        * https://ffmpeg.org/doxygen/trunk/group__lavc__decoding
        * html#ga11e6542c4e66d3028668788a1a74217c
        */
        response = avcodec_receive_frame(p_codec, p_prame);
        if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
            break;
        } 
        
        else if (response < 0) {
            LOGGING("Error while receiving a frame from the decoder: %s", 
                    av_err2str(response));
            return response;
        }

        if (response >= 0) {
            LOGGING(
                "Frame %d (type=%c, size=%d bytes, format=%d) pts %d key_frame %d [DTS %d]",
                p_codec->frame_num,
                av_get_picture_type_char(p_frame->pict_type),
                p_frame->pkt_size,
                p_frame->format,
                p_frame->pts,
                p_frame->key_frame,
                p_frame->coded_picture_number
            );
 
            char frame_file[1024];
            // our saved file name should be from the POV of the root dir which the
            // makefile and shell script to compile/run this project are located
            snprintf(frame_file, sizeof(frame_file), 
                    "../cv-data/output/tests/%s-%d.pgm",
                    "frame", p_codec->frame_num);
            /*
             * Check if the frame is a planar YUV 4:2:0, 12bpp
             * That is the format of the provided .mp4 file
             * RGB formats will definitely not give a gray image
             * Other YUV image may do so, but untested, so give a warning
             */
            if (p_frame->format != AV_PIX_FMT_YUV420P) {
                LOGGING("WARNING: THE GENERATED FILE MAY NOT BE GRAYSCALE BUT \
                        THE 'R' COMPONENT IF THE FILE FORMAT IS RBG!");
            }
            // save a grayscale frame into a .pgm file
            save_pgm(p_frame->data[0], 
                    p_frame->linesize[0], 
                    p_frame->width, 
                    p_frame->height, 
                    frame_file);
        }
    }
    return 0;
}


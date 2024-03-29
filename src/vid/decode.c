/* <--------------------------------------------------------------------------->
 * F : format
 * D : duration
 * R : resolution
 * A : audio channels
 * D : decoding frames into .pgm format
 *
 * Overall purpose of this was to ensure ffmpeg + deopendencies were installed
 * correctly.
 *
 * http://ffmpeg.org/doxygen/trunk/index.html
 *
 * Main components
 *
 * Format (Container) - a wrapper, providing sync, metadata and muxing 
 *                      (multiplexing) for the streams.
 * Stream   - a continuous stream (audio or video) of data over time.
 * Codec    - defines how data are enCOded (from Frame to Packet)
 *          and DECoded (from Packet to Frame).
 * Packet   - are the data (kind of slices of the stream data) to be decoded 
 *          as raw frames.
 * Frame    - a decoded raw frame (to be encoded or filtered).
 * <---------------------------------------------------------------------------> 
 */

/*
 * import libs
 */
#include "../../include/decode.h"
#include "../../include/log.h"
#include "../../include/usage.h"
#include "../../include/wfmt.h"
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#define BITS_SIZE 255

/*
 * DESCRIBE THIS FUNCTION
 */
int decode(AVPacket *p_packet,
            AVCodecContext *p_codec,
            AVFrame *p_frame, 
            char *argv[]) {
    /*
     * Supply raw packet data as input to a decoder
     * https://ffmpeg.org/doxygen/trunk/group__lavc__decoding.html
     * #ga58bc4bf1e0ac59e27362597e467efff3
     */
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
        response = avcodec_receive_frame(p_codec, p_frame);
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
                p_codec->frame_number,
                av_get_picture_type_char(p_frame->pict_type),
                p_frame->pkt_size,
                p_frame->format,
                p_frame->pts,
                p_frame->key_frame,
                p_frame->coded_picture_number
            );
 
            char frame_file[1024];
            
            /* 
             * our saved file name should be from the POV of the root dir which 
             * the makefile and shell script to compile/run this project are 
             * located
             * 
             * change the below snprintf to allow for change based on flags. 
             * this will piggyback off of the flag deciding what format to save
             * the decoded files to. pgm, ppm, jpg, etc...
             */
            /*--------------------------------------------------------------------->
             * | Pick up here for dealing with -o + -f arguments. 
             * |
             * | -o deals with the location where we will save to 
             * | -f deals with the format of our saved file.
             * |
             * | Think about moving ln 84 into the wfmt file in the save_pgm file
             * |
             *--------------------------------------------------------------------->
             */
            snprintf(frame_file, sizeof(frame_file), 
                    "cv-data/output/tests/%s-%d.pgm",
                    "frame", p_codec->frame_number);
            /*
             * Check if the frame is a planar YUV 4:2:0, 12bpp
             * That is the format of the provided .mp4 file
             * RGB formats will definitely not give a gray image
             * Other YUV image may do so, but untested, so give a warning
             */
            if (p_frame->format != AV_PIX_FMT_YUV420P) {
                LOGGING("WARNING: THE GENERATED FILE MAY NOT BE GRAYSCALE BUT THE 'R' COMPONENT IF THE FILE FORMAT IS RBG!");
            }

            // if specified output file is pgm
            //if (strcmp(argv[4], "pgm") == o) {
                // save a grayscale frame into a .pgm file
                save_pgm(p_frame->data[0], 
                        p_frame->linesize[0], 
                        p_frame->width, 
                        p_frame->height, 
                        frame_file);
            //}
        }
    }
    return 0;
}

/*
 * THIS MAIN FUNCTION WILL CHANGE AS DEVELOPMENT PROGRESSES. 
 * EVENTUALLY I WANT MAIN TO BE IN ITS OWN FILE AND CALLING
 * OTHER "DRIVER" FILES BASED ON ARGUMENTS. FOR NOW, THIS 
 * WILL SERVE FINE FOR THE CURRENT VIDEO->PICTURE 
 * CONVERSION
 */
int decode_call(int argc, char *argv[]) {
    /* TODO */
    
    // time the function
    clock_t t;
    t = clock();

    /*  
     * think about moving this to another file and how? 
     * on the CLI : 
     * e.g. ./vpaSTRM -d movie.mp4 -o pgm
     *      - argv[0] = ./vpaSTRM
     *          - running the compiled binary
     *      - argv[1] = -d
     *          - flags defined possibly as chars
     *      - argv[2] = movie.mp4
     *          - relies off argv[1] 
     */

    //if (argc < 2) {
    //    printf("ERR: SPECIFY VIDEO FILE.\n");
    //    return -1;
    //}
    if (argv[2] == NULL) {
        printf("ERROR: SPECIFY VIDEO FILE\n");
        usage_decode(argv[1]);
        return -1;
    }

    LOGGING("initializing all the containers, codecs and protocols.");

    /*
     * AVFormatContext holds the header information from the format (Container)
     * Allocating memory for this component
     * http://ffmpeg.org/doxygen/trunk/structAVFormatContext.html
     */

    AVFormatContext *pFormatContext = avformat_alloc_context();
    if (!pFormatContext) {
    LOGGING("ERROR could not allocate memory for Format Context");
    return -1;
    }

    LOGGING("opening the input file (%s) and loading format (container) header",
          argv[2]);

    /*
     * Open the file and read its header. The codecs are not opened.
     * The function arguments are:
     * AVFormatContext (the component we allocated memory for),
     * url (filename),
     * AVInputFormat (if you pass NULL it'll do the auto detect)
     * and AVDictionary (which are options to the demuxer)
     * http://ffmpeg.org/doxygen/trunk/group__lavf__decoding.
     * html#ga31d601155e9035d5b0e7efedc894ee49
    */
    if (avformat_open_input(&pFormatContext, argv[2], NULL, NULL) != 0) {
        LOGGING("ERROR could not open the file");
        /* <-- 😤 --> */
        return 17;
    }

    /* 
     * now we have access to some information about our file
     * since we read its header we can say what format (container) it's
     * and some other information related to the format itself.
     */
    LOGGING("format %s, duration %lld us, bit_rate %lld",
            pFormatContext->iformat->name,
            pFormatContext->duration, pFormatContext->bit_rate);

    LOGGING("finding stream info from format");

    /*
     * read Packets from the Format to get stream information
     * this function populates pFormatContext->streams
     * (of size equals to pFormatContext->nb_streams)
     * the arguments are:
     * the AVFormatContext
     * and options contains options for codec corresponding to i-th stream.
     * On return each dictionary will be filled with options that were not found.
     * https://ffmpeg.org/doxygen/trunk/group__lavf__decoding.html
     * #gad42172e27cddafb81096939783b157bb
     */
    if (avformat_find_stream_info(pFormatContext,  NULL) < 0) {
        LOGGING("ERROR could not get the stream info");
        return -1;
    }

    /*
     * the component that knows how to enCOde and DECode the stream
     * it's the codec (audio or video)
     * http://ffmpeg.org/doxygen/trunk/structAVCodec.html
     */
    const AVCodec *pCodec = NULL;
    /*
     * this component describes the properties of a codec used by the stream i
     * https://ffmpeg.org/doxygen/trunk/structAVCodecParameters.html
     */
    AVCodecParameters *pCodecParameters =  NULL;
    int video_stream_index = -1;

    // loop though all the streams and print its main information
    for (int i = 0; i < pFormatContext->nb_streams; i++) {
        AVCodecParameters *pLocalCodecParameters =  NULL;
        pLocalCodecParameters = pFormatContext->streams[i]->codecpar;

        LOGGING("AVStream->time_base before open coded %d/%d",
                pFormatContext->streams[i]->time_base.num,
                pFormatContext->streams[i]->time_base.den);

        LOGGING("AVStream->r_frame_rate before open coded %d/%d",
                pFormatContext->streams[i]->r_frame_rate.num,
                pFormatContext->streams[i]->r_frame_rate.den);

        LOGGING("AVStream->start_time %" PRId64,
                pFormatContext->streams[i]->start_time);

        LOGGING("AVStream->duration %" PRId64,
                pFormatContext->streams[i]->duration);

        LOGGING("finding the proper decoder (CODEC)");

        const AVCodec *pLocalCodec = NULL;

        /*
         * finds the registered decoder for a codec ID
         * https://ffmpeg.org/doxygen/trunk/group__lavc__decoding.html
         * #ga19a0ca553277f019dd5b0fec6e1f9dca  
         */
        pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);
        if (pLocalCodec==NULL) {
            LOGGING("ERROR (CODEC) : unsupported codec!");
            // In this example if the codec is not found we just skip it
            continue;
        }

        // when the stream is a video we store its index, codec parameters and codec
        if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
            if (video_stream_index == -1) {
                video_stream_index = i;
                pCodec = pLocalCodec;
                pCodecParameters = pLocalCodecParameters;
            }

            LOGGING("Video Codec: resolution %d x %d",
                    pLocalCodecParameters->width,
                    pLocalCodecParameters->height);
        }

        else if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
            LOGGING("Audio Codec: %d channels, sample rate %d",
                    // pLocalCodecParameters->channels, 
                    pLocalCodecParameters->ch_layout,
                    pLocalCodecParameters->sample_rate);
        }

        // print its name, id and bitrate
        LOGGING("\tCodec %s ID %d bit_rate %lld",
                pLocalCodec->name,
                pLocalCodec->id,
                pLocalCodecParameters->bit_rate);
    }

    if (video_stream_index == -1) {
        LOGGING("ERROR (STREAM): File %s does not contain a video stream!", 
                argv[1]);

        return -1;
    }

    // https://ffmpeg.org/doxygen/trunk/structAVCodecContext.html
    AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec);
    if (!pCodecContext) {
        //LOGGING("failed to allocated memory for AVCodecContext");
        LOGGING("ERROR (CODEC) : failed to allocated memory for context");
        return -1;
    }

    /*
     * Fill the codec context based on the values from the supplied codec parameters
     * https://ffmpeg.org/doxygen/trunk/group__lavc__core.html#
     * gac7b282f51540ca7a99416a3ba6ee0d16
     */
    if (avcodec_parameters_to_context(pCodecContext, pCodecParameters) < 0) {
        //LOGGING("failed to copy codec params to codec context");
        LOGGING("ERROR (CODEC) : failed to copy parameters to context");
        return -1;
    }

    /*
     * Initialize the AVCodecContext to use the given AVCodec.
     * https://ffmpeg.org/doxygen/trunk/group__lavc__core.html#
     * ga11f785a188d7d9df71621001465b0f1d
     */
    if (avcodec_open2(pCodecContext, pCodec, NULL) < 0) {
        LOGGING("ERROR (CODEC) : failed to open with avcodec_open2");
        return -1;
    }

    // https://ffmpeg.org/doxygen/trunk/structAVFrame.html
    AVFrame *pFrame = av_frame_alloc();
    if (!pFrame) {
        LOGGING("ERROR (FRAME) : failed to allocate memory for AVFrame");
        return -1;
    }

    // https://ffmpeg.org/doxygen/trunk/structAVPacket.html
    AVPacket *pPacket = av_packet_alloc();
    if (!pPacket) {
        LOGGING("ERROR (PACKET) : failed to allocate memory for AVPacket");
        return -1;
    }

    int response = 0;
    /* <------ ASK FOR THIS AS A PARAMETER ------> */
    // int how_many_packets_to_process = 8;

    /*
     * fill the Packet with data from the Stream
     * https://ffmpeg.org/doxygen/trunk/group__lavf__decoding.html#
     * ga4fdb3084415a82e3810de6ee60e46a61
     */
    while (av_read_frame(pFormatContext, pPacket) >= 0) {
        // if it's the video stream
        if (pPacket->stream_index == video_stream_index) {
            LOGGING("AVPacket->pts %" PRId64, pPacket->pts);
            response = decode(pPacket, pCodecContext, pFrame, argv);

            if (response < 0) {
                break;
            }
        // stop it, otherwise we'll be saving hundreds of frames
        //if (--how_many_packets_to_process <= 0) break;

        }
    /*
     * https://ffmpeg.org/doxygen/trunk/group__lavc__packet.html
     * #ga63d5a489b419bd5d45cfd09091cbcbc2
     */

        av_packet_unref(pPacket);
    }
    // LOGGING("releasing all the resources");
    LOGGING("\n <-------DUMPING-------> \n");

    avformat_close_input(&pFormatContext);
    av_packet_free(&pPacket);
    av_frame_free(&pFrame);
    avcodec_free_context(&pCodecContext);

    printf("\n<----------------------------------------------------------->\n");

    // end time 
    t = clock() - t;
    // return time in seconds
    double final_time = ((double)t) / CLOCKS_PER_SEC;
    printf("Decoded in: %f seconds\n", final_time);

    return 0;

}


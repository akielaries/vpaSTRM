/*
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
 *
 */

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

// pointer for output log file
FILE *log_out;

// keep track of session
static int SESSION_NUM;

// print out the steps and errors
static void logging(char* file_name, int line, const char *format, ...);
#define LOGGING(...) logging(__FILE__, __LINE__,__VA_ARGS__)

// decode packets into frames
static int decode_packet(AVPacket *pPacket, AVCodecContext *pCodecContext, 
        AVFrame *pFrame);

// save a frame into a .pgm file
static void save_gray_frame(unsigned char *buf, int wrap, int xsize, int ysize, 
        char *filename);


int main(int argc, const char *argv[]) {
    //log_file_ptr = fopen("logs/TEST-LOG-001.txt", "w");

    if (argc < 2) {
        printf("You need to specify a media file.\n");
        // return -1;
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
          argv[1]);
    
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

  if (avformat_open_input(&pFormatContext, argv[1], NULL, NULL) != 0) {
    LOGGING("ERROR could not open the file");
    return -1;
  }

  // now we have access to some information about our file
  // since we read its header we can say what format (container) it's
  // and some other information related to the format itself.
  LOGGING("format %s, duration %lld us, bit_rate %lld", 
          pFormatContext->iformat->name, 
          pFormatContext->duration, pFormatContext->bit_rate);

  LOGGING("finding stream info from format");
  // read Packets from the Format to get stream information
  // this function populates pFormatContext->streams
  // (of size equals to pFormatContext->nb_streams)
  // the arguments are:
  // the AVFormatContext
  // and options contains options for codec corresponding to i-th stream.
  // On return each dictionary will be filled with options that were not found.
  // https://ffmpeg.org/doxygen/trunk/group__lavf__decoding.html#gad42172e27cddafb81096939783b157bb
  if (avformat_find_stream_info(pFormatContext,  NULL) < 0) {
    LOGGING("ERROR could not get the stream info");
    return -1;
  }

  // the component that knows how to enCOde and DECode the stream
  // it's the codec (audio or video)
  // http://ffmpeg.org/doxygen/trunk/structAVCodec.html
  AVCodec *pCodec = NULL;
  // this component describes the properties of a codec used by the stream i
  // https://ffmpeg.org/doxygen/trunk/structAVCodecParameters.html
  AVCodecParameters *pCodecParameters =  NULL;
  int video_stream_index = -1;

  // loop though all the streams and print its main information
  for (int i = 0; i < pFormatContext->nb_streams; i++)
  {
    AVCodecParameters *pLocalCodecParameters =  NULL;
    pLocalCodecParameters = pFormatContext->streams[i]->codecpar;
    LOGGING("AVStream->time_base before open coded %d/%d", pFormatContext->streams[i]->time_base.num, pFormatContext->streams[i]->time_base.den);
    LOGGING("AVStream->r_frame_rate before open coded %d/%d", pFormatContext->streams[i]->r_frame_rate.num, pFormatContext->streams[i]->r_frame_rate.den);
    LOGGING("AVStream->start_time %" PRId64, pFormatContext->streams[i]->start_time);
    LOGGING("AVStream->duration %" PRId64, pFormatContext->streams[i]->duration);

    LOGGING("finding the proper decoder (CODEC)");

    AVCodec *pLocalCodec = NULL;

    // finds the registered decoder for a codec ID
    // https://ffmpeg.org/doxygen/trunk/group__lavc__decoding.html#ga19a0ca553277f019dd5b0fec6e1f9dca
    pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

    if (pLocalCodec==NULL) {
      LOGGING("ERROR unsupported codec!");
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

      LOGGING("Video Codec: resolution %d x %d", pLocalCodecParameters->width, pLocalCodecParameters->height);
    } else if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
      LOGGING("Audio Codec: %d channels, sample rate %d", pLocalCodecParameters->channels, pLocalCodecParameters->sample_rate);
    }

    // print its name, id and bitrate
    LOGGING("\tCodec %s ID %d bit_rate %lld", pLocalCodec->name, pLocalCodec->id, pLocalCodecParameters->bit_rate);
  }

  if (video_stream_index == -1) {
    LOGGING("File %s does not contain a video stream!", argv[1]);
    return -1;
  }

  // https://ffmpeg.org/doxygen/trunk/structAVCodecContext.html
  AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec);
  if (!pCodecContext)
  {
    LOGGING("failed to allocated memory for AVCodecContext");
    return -1;
  }

  // Fill the codec context based on the values from the supplied codec parameters
  // https://ffmpeg.org/doxygen/trunk/group__lavc__core.html#gac7b282f51540ca7a99416a3ba6ee0d16
  if (avcodec_parameters_to_context(pCodecContext, pCodecParameters) < 0)
  {
    LOGGING("failed to copy codec params to codec context");
    return -1;
  }

  // Initialize the AVCodecContext to use the given AVCodec.
  // https://ffmpeg.org/doxygen/trunk/group__lavc__core.html#ga11f785a188d7d9df71621001465b0f1d
  if (avcodec_open2(pCodecContext, pCodec, NULL) < 0)
  {
    LOGGING("failed to open codec through avcodec_open2");
    return -1;
  }

  // https://ffmpeg.org/doxygen/trunk/structAVFrame.html
  AVFrame *pFrame = av_frame_alloc();
  if (!pFrame)
  {
    LOGGING("failed to allocate memory for AVFrame");
    return -1;
  }
  // https://ffmpeg.org/doxygen/trunk/structAVPacket.html
  AVPacket *pPacket = av_packet_alloc();
  if (!pPacket)
  {
    LOGGING("failed to allocate memory for AVPacket");
    return -1;
  }

  int response = 0;
  int how_many_packets_to_process = 8;

  // fill the Packet with data from the Stream
  // https://ffmpeg.org/doxygen/trunk/group__lavf__decoding.html#ga4fdb3084415a82e3810de6ee60e46a61
  while (av_read_frame(pFormatContext, pPacket) >= 0)
  {
    // if it's the video stream
    if (pPacket->stream_index == video_stream_index) {
    LOGGING("AVPacket->pts %" PRId64, pPacket->pts);
      response = decode_packet(pPacket, pCodecContext, pFrame);
      if (response < 0)
        break;
      // stop it, otherwise we'll be saving hundreds of frames
      //if (--how_many_packets_to_process <= 0) break;
    }
    // https://ffmpeg.org/doxygen/trunk/group__lavc__packet.html#ga63d5a489b419bd5d45cfd09091cbcbc2
    av_packet_unref(pPacket);
  }

  LOGGING("releasing all the resources");

  avformat_close_input(&pFormatContext);
  av_packet_free(&pPacket);
  av_frame_free(&pFrame);
  avcodec_free_context(&pCodecContext);
  return 0;
}


/*
 * function to print the current time to our log files
 */
char* timestamp() {
    int size = 0;
    time_t time_iter;
    char *buffer;

    time_iter = time(NULL);
    
    // retrieve current time
    char *time_str = asctime(localtime(&time_iter));
    // this deletes the carriage return \n
    time_str[strlen(time_str) - 1] = 0;

    // square braces
    size = strlen(time_str) + 1 + 2;
    buffer = (char*)malloc(size);

    memset(buffer, 0x0, size);
    snprintf(buffer, size, "[%s]", time_str);

    return buffer;
}

//static FILE *log_file_ptr;

//log_file_ptr = fopen("logs/TEST-LOG-001.txt", "w");
/*
 * Function that takes care of logging with variadic function. When called
 * behavior is returned to STDOUT + log file in /logs
 *
 * <---------- FIX DUMP TO LOG ---------->
 */
static void logging(char* file_name, int line, const char *format, ...) {
    va_list list;
    char *ptr_p, *ptr_r;
    int switch_arg;

    /* use this for checking if the file exists and appending or writing
     * accordingly
    if(SESSION_TRACKER > 0)
      fp = fopen ("log.txt","a+");
    else
      fp = fopen ("log.txt","w");
    */
    log_out = fopen("../logs/TEST-LOG-001.txt", "a+");
    fprintf(log_out, "%s", timestamp()); 
    fprintf(log_out, "[%s][line: %d] ", file_name, line);
    
    va_start(list, format);

    for (ptr_p = format; *ptr_p; ++ptr_p) {
        if (*ptr_p != '%') 
            fputc(*ptr_p, log_out);

        else {
            switch (*++ptr_p) {
                
                // string
                case 's':
                    ptr_r = va_arg(list, char *);
                    fprintf(log_out, "%s", ptr_r);
                    continue;
                
                // integer
                case 'd':
                    switch_arg = va_arg(list, int);
                    fprintf(log_out, "%d", switch_arg);
                    continue;

                default:
                    fputc(*ptr_p, log_out);
            }
        }
    }
    va_end(list);
    fputc('\n', log_out);
    fclose(log_out);

    /* leaving because I might use this still
    va_list args_file, args_stdout;
    
    fprintf(stderr, "LOG: ");

    va_start(args_file, format);
    va_start(args_stdout, format);

    vfprintf(file_ptr, format, args_file);
    vfprintf(stderr, format, args_stdout);

    fflush(file_ptr);
    fflush(stderr);

    va_end(args_file);
    va_end(args_stdout);

    fprintf(stderr, "\n");
    */
    /*
    va_list args;
    fprintf( stderr, "LOG: " );
    va_start( args, format );
    vfprintf( stderr, format, args );
    va_end( args );
    fprintf( stderr, "\n" );
    */
}

/*
void teeprintf(FILE *file_ptr, const char *format, ...) {
    va_list args_fd, args_stdout;
    va_start(args_fd, format);
    va_start(args_stdout, format);

    vfprintf(file_ptr, format, args_fd);
    vfprintf(stdout, format, args_stdout);

    // flush output buffer of our stream
    fflush(file_ptr);
    fflush(stdout);

    va_end(args_fd);
    va_end(args_stdout);

}
*/
/*
void redirect(void (*f)(void), char *file) {
    int fd = open(file, O_CREAT | O_TRUN | O_WRONLY, 0644);
    int savefd = dup(1);
    dup2(fd, 1);
    f();
    dup2(savefd, 1);
    close(df);
    close(savefd);

}
*/

static int decode_packet(AVPacket *pPacket, AVCodecContext *pCodecContext, AVFrame *pFrame)
{
  // Supply raw packet data as input to a decoder
  // https://ffmpeg.org/doxygen/trunk/group__lavc__decoding.html#ga58bc4bf1e0ac59e27362597e467efff3
  int response = avcodec_send_packet(pCodecContext, pPacket);

  if (response < 0) {
    LOGGING("Error while sending a packet to the decoder: %s", av_err2str(response));
    return response;
  }

  while (response >= 0)
  {
    // Return decoded output data (into a frame) from a decoder
    // https://ffmpeg.org/doxygen/trunk/group__lavc__decoding.html#ga11e6542c4e66d3028668788a1a74217c
    response = avcodec_receive_frame(pCodecContext, pFrame);
    if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
      break;
    } else if (response < 0) {
      LOGGING("Error while receiving a frame from the decoder: %s", av_err2str(response));
      return response;
    }

    if (response >= 0) {
      LOGGING(
          "Frame %d (type=%c, size=%d bytes, format=%d) pts %d key_frame %d [DTS %d]",
          pCodecContext->frame_number,
          av_get_picture_type_char(pFrame->pict_type),
          pFrame->pkt_size,
          pFrame->format,
          pFrame->pts,
          pFrame->key_frame,
          pFrame->coded_picture_number
      );

      char frame_filename[1024];
      // our saved file name should be from the POV of the root dir which the
      // makefile and shell script to compile/run this project are located
      snprintf(frame_filename, sizeof(frame_filename), "../cv-data/output/tests/%s-%d.pgm", 
              "frame", pCodecContext->frame_number);
      // Check if the frame is a planar YUV 4:2:0, 12bpp
      // That is the format of the provided .mp4 file
      // RGB formats will definitely not give a gray image
      // Other YUV image may do so, but untested, so give a warning
      if (pFrame->format != AV_PIX_FMT_YUV420P)
      {
        LOGGING("Warning: the generated file may not be a grayscale image, but \
                could e.g. be just the R component if the video format is RGB");
      }
      // save a grayscale frame into a .pgm file
      save_gray_frame(pFrame->data[0], pFrame->linesize[0], pFrame->width, pFrame->height, frame_filename);
    }
  }
  return 0;
}

static void save_gray_frame(unsigned char *buf, int wrap, int xsize, int ysize, char *filename)
{
    FILE *f;
    int i;
    f = fopen(filename,"w");
    // writing the minimal required header for a pgm file format
    // portable graymap format -> https://en.wikipedia.org/wiki/Netpbm_format#PGM_example
    fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);

    // writing line by line
    for (i = 0; i < ysize; i++)
        fwrite(buf + i * wrap, 1, xsize, f);
    fclose(f);
}



#include "ImageThread.h"

#ifdef __cplusplus
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/error.h>
#include <libswscale/swscale.h>
}
#endif //__cplusplus

class AV_DATA {
public:
    AV_DATA():
        pFormatCtx(NULL),
        i (-1),
        videoStream(-1),
        pCodecCtxOrig(NULL),
        pCodecCtx(NULL),
        pCodec(NULL),
        pFrame(NULL),
        pFrameRGB(NULL),
        buffer(NULL),
        sws_ctx(NULL)
    {}

    ~AV_DATA(){}

    // Initalizing these to NULL prevents segfaults!
    AVFormatContext   *pFormatCtx;
    int               i, videoStream;
    AVCodecContext    *pCodecCtxOrig;
    AVCodecContext    *pCodecCtx;
    AVCodec           *pCodec;
    AVFrame           *pFrame;
    AVFrame           *pFrameRGB;
    AVPacket          packet;
    int               frameFinished;
    int               numBytes;
    uint8_t           *buffer;
    struct SwsContext *sws_ctx;
    QString path;
};


ImageThread::ImageThread(QObject *parent):
    QThread(parent)
{
    // Register all formats and codecs
    av_register_all();
    avformat_network_init();
    d = new AV_DATA;
}

ImageThread::~ImageThread()
{
    if(d)
    {
        // Free the RGB image
        av_free(d->buffer);
        av_frame_free(&d->pFrameRGB);

        // Free the YUV frame
        av_frame_free(&d->pFrame);

        // Close the codecs
        avcodec_close(d->pCodecCtx);
        avcodec_close(d->pCodecCtxOrig);

        // Close the video file
        avformat_close_input(&d->pFormatCtx);

        delete(d);
    }
}

void ImageThread::setPath(QString path)
{
    d->path = path;
}

void ImageThread::run()
{
    if(avformat_open_input(&d->pFormatCtx, d->path.toUtf8().data(), NULL, NULL)!=0){
        qDebug(QString("Couldn't open file %1").arg(d->path).toUtf8().data());
        return;
    }

    // Retrieve stream information
    if(avformat_find_stream_info(d->pFormatCtx, NULL)<0){
        qDebug("Couldn't find stream information");
        return;
    }

    // Find the first video stream
    d->videoStream = -1;
    for(d->i = 0; d->i < d->pFormatCtx->nb_streams; d->i++)
        if(d->pFormatCtx->streams[d->i]->codecpar->codec_type==AVMEDIA_TYPE_VIDEO) {
            d->videoStream = d->i;
            break;
        }
    if(d->videoStream == -1)
        return; // Didn't find a video stream

    // Get a pointer to the codec context for the video stream
    d->pCodecCtxOrig = d->pFormatCtx->streams[d->videoStream]->codec;
    // Find the decoder for the video stream
    d->pCodec = avcodec_find_decoder(d->pCodecCtxOrig->codec_id);
    if(d->pCodec == NULL) {
        fprintf(stderr, "Unsupported codec!\n");
        return; // Codec not found
    }
    // Copy context
    d->pCodecCtx = avcodec_alloc_context3(d->pCodec);

    AVCodecParameters par;
    avcodec_parameters_from_context(&par, d->pCodecCtxOrig);
    avcodec_parameters_to_context(d->pCodecCtx, &par);

    // Open codec
    if(avcodec_open2(d->pCodecCtx, d->pCodec, NULL)<0)
        return; // Could not open codec

    // Allocate video frame
    d->pFrame = av_frame_alloc();

    // Allocate an AVFrame structure
    d->pFrameRGB = av_frame_alloc();
    if(d->pFrameRGB == NULL)
        return;

    // Determine required buffer size and allocate buffer
    d->numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, d->pCodecCtx->width,
                                     d->pCodecCtx->height);
    d->buffer = (uint8_t *)av_malloc(d->numBytes*sizeof(uint8_t));

    // Assign appropriate parts of buffer to image planes in pFrameRGB
    // Note that pFrameRGB is an AVFrame, but AVFrame is a superset of AVPicture
    avpicture_fill((AVPicture *)d->pFrameRGB, d->buffer, AV_PIX_FMT_RGB24,
                   d->pCodecCtx->width, d->pCodecCtx->height);

    // initialize SWS context for software scaling
    d->sws_ctx = sws_getContext(d->pCodecCtx->width,
                                d->pCodecCtx->height,
                                d->pCodecCtx->pix_fmt,
                                d->pCodecCtx->width,
                                d->pCodecCtx->height,
                                AV_PIX_FMT_RGB24,
                                SWS_BILINEAR,
                                NULL,
                                NULL,
                                NULL
                                );

    while(av_read_frame(d->pFormatCtx, &d->packet)>=0) {

        // Is this a packet from the video stream?
        if(d->packet.stream_index == d->videoStream) {

            // Decode video frame
            avcodec_send_packet(d->pCodecCtx, &d->packet);
            d->frameFinished = avcodec_receive_frame(d->pCodecCtx, d->pFrame);

            // Did we get a video frame?
            if(d->frameFinished == 0) {
                // Convert the image from its native format to RGB
                sws_scale(d->sws_ctx, (uint8_t const * const *)d->pFrame->data,
                          d->pFrame->linesize, 0, d->pCodecCtx->height,
                          d->pFrameRGB->data, d->pFrameRGB->linesize);

                QImage img(d->pFrameRGB->data[0],
                        d->pCodecCtx->width,
                        d->pCodecCtx->height,
                        d->pFrameRGB->linesize[0],
                        QImage::Format_RGB888);

                emit updateImg(img);
            }
        }

        // Free the packet that was allocated by av_read_frame
        av_packet_unref(&d->packet);
    }
}

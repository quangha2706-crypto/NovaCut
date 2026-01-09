#include "Encoder.h"
#include <QDebug>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
}

namespace NovaCut {
namespace Media {

Encoder::Encoder(const QString& filepath)
    : m_filepath(filepath)
    , m_isOpen(false)
    , m_formatCtx(nullptr)
    , m_videoCodecCtx(nullptr)
    , m_audioCodecCtx(nullptr)
    , m_videoStream(nullptr)
    , m_audioStream(nullptr)
    , m_frame(nullptr)
    , m_width(0)
    , m_height(0)
    , m_frameRate(0.0)
    , m_videoFrameCount(0)
    , m_audioFrameCount(0)
{
}

Encoder::~Encoder()
{
    close();
}

bool Encoder::open(int width, int height, double frameRate, 
                   VideoCodec videoCodec, AudioCodec audioCodec)
{
    if (m_isOpen) {
        return true;
    }

    m_width = width;
    m_height = height;
    m_frameRate = frameRate;

    // Allocate output context
    avformat_alloc_output_context2(&m_formatCtx, nullptr, nullptr, m_filepath.toUtf8().constData());
    if (!m_formatCtx) {
        qCritical() << "Failed to create output context";
        return false;
    }

    // Find video encoder
    AVCodecID codecId = AV_CODEC_ID_H264;
    switch (videoCodec) {
        case VideoCodec::H264: codecId = AV_CODEC_ID_H264; break;
        case VideoCodec::H265: codecId = AV_CODEC_ID_H265; break;
        case VideoCodec::VP9: codecId = AV_CODEC_ID_VP9; break;
    }

    const AVCodec* vCodec = avcodec_find_encoder(codecId);
    if (!vCodec) {
        qCritical() << "Video codec not found";
        close();
        return false;
    }

    // Create video stream
    m_videoStream = avformat_new_stream(m_formatCtx, nullptr);
    if (!m_videoStream) {
        qCritical() << "Failed to create video stream";
        close();
        return false;
    }

    // Allocate video codec context
    m_videoCodecCtx = avcodec_alloc_context3(vCodec);
    m_videoCodecCtx->width = m_width;
    m_videoCodecCtx->height = m_height;
    m_videoCodecCtx->time_base = AVRational{1, static_cast<int>(frameRate)};
    m_videoCodecCtx->framerate = AVRational{static_cast<int>(frameRate), 1};
    m_videoCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    m_videoCodecCtx->bit_rate = 4000000; // 4 Mbps

    if (m_formatCtx->oformat->flags & AVFMT_GLOBALHEADER) {
        m_videoCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }

    // Open video codec
    if (avcodec_open2(m_videoCodecCtx, vCodec, nullptr) < 0) {
        qCritical() << "Failed to open video codec";
        close();
        return false;
    }

    avcodec_parameters_from_context(m_videoStream->codecpar, m_videoCodecCtx);

    // Open output file
    if (!(m_formatCtx->oformat->flags & AVFMT_NOFILE)) {
        if (avio_open(&m_formatCtx->pb, m_filepath.toUtf8().constData(), AVIO_FLAG_WRITE) < 0) {
            qCritical() << "Failed to open output file:" << m_filepath;
            close();
            return false;
        }
    }

    // Write header
    if (avformat_write_header(m_formatCtx, nullptr) < 0) {
        qCritical() << "Failed to write header";
        close();
        return false;
    }

    m_frame = av_frame_alloc();
    m_isOpen = true;
    
    qDebug() << "Encoder opened successfully:" << m_filepath;
    return true;
}

void Encoder::close()
{
    if (m_frame) {
        av_frame_free(&m_frame);
        m_frame = nullptr;
    }

    if (m_videoCodecCtx) {
        avcodec_free_context(&m_videoCodecCtx);
        m_videoCodecCtx = nullptr;
    }

    if (m_audioCodecCtx) {
        avcodec_free_context(&m_audioCodecCtx);
        m_audioCodecCtx = nullptr;
    }

    if (m_formatCtx) {
        if (m_isOpen && !(m_formatCtx->oformat->flags & AVFMT_NOFILE)) {
            avio_closep(&m_formatCtx->pb);
        }
        avformat_free_context(m_formatCtx);
        m_formatCtx = nullptr;
    }

    m_isOpen = false;
}

bool Encoder::encodeVideoFrame(const uint8_t* data, int size)
{
    if (!m_isOpen) {
        return false;
    }

    // TODO: Implement video frame encoding
    qDebug() << "Encoding video frame...";
    m_videoFrameCount++;
    return true;
}

bool Encoder::encodeAudioFrame(const uint8_t* data, int size)
{
    if (!m_isOpen) {
        return false;
    }

    // TODO: Implement audio frame encoding
    qDebug() << "Encoding audio frame...";
    m_audioFrameCount++;
    return true;
}

bool Encoder::finalize()
{
    if (!m_isOpen) {
        return false;
    }

    // Write trailer
    if (av_write_trailer(m_formatCtx) < 0) {
        qCritical() << "Failed to write trailer";
        return false;
    }

    qDebug() << "Encoding finalized. Video frames:" << m_videoFrameCount 
             << "Audio frames:" << m_audioFrameCount;
    return true;
}

} // namespace Media
} // namespace NovaCut

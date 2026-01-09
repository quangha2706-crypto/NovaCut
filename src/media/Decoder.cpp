#include "Decoder.h"
#include <QDebug>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

namespace NovaCut {
namespace Media {

Decoder::Decoder(const QString& filepath)
    : m_filepath(filepath)
    , m_isOpen(false)
    , m_formatCtx(nullptr)
    , m_videoCodecCtx(nullptr)
    , m_audioCodecCtx(nullptr)
    , m_frame(nullptr)
    , m_swsCtx(nullptr)
    , m_videoStreamIndex(-1)
    , m_audioStreamIndex(-1)
    , m_width(0)
    , m_height(0)
    , m_frameRate(0.0)
    , m_duration(0.0)
{
}

Decoder::~Decoder()
{
    close();
}

bool Decoder::open()
{
    if (m_isOpen) {
        return true;
    }

    // Open input file
    if (avformat_open_input(&m_formatCtx, m_filepath.toUtf8().constData(), nullptr, nullptr) < 0) {
        qCritical() << "Failed to open input file:" << m_filepath;
        return false;
    }

    if (avformat_find_stream_info(m_formatCtx, nullptr) < 0) {
        qCritical() << "Failed to find stream info";
        close();
        return false;
    }

    // Find video and audio streams
    for (unsigned int i = 0; i < m_formatCtx->nb_streams; i++) {
        AVMediaType codecType = m_formatCtx->streams[i]->codecpar->codec_type;
        if (codecType == AVMEDIA_TYPE_VIDEO && m_videoStreamIndex < 0) {
            m_videoStreamIndex = i;
        } else if (codecType == AVMEDIA_TYPE_AUDIO && m_audioStreamIndex < 0) {
            m_audioStreamIndex = i;
        }
    }

    // Open video codec
    if (m_videoStreamIndex >= 0) {
        AVStream* videoStream = m_formatCtx->streams[m_videoStreamIndex];
        const AVCodec* videoCodec = avcodec_find_decoder(videoStream->codecpar->codec_id);
        
        if (!videoCodec) {
            qCritical() << "Video codec not found";
            close();
            return false;
        }

        m_videoCodecCtx = avcodec_alloc_context3(videoCodec);
        avcodec_parameters_to_context(m_videoCodecCtx, videoStream->codecpar);
        
        if (avcodec_open2(m_videoCodecCtx, videoCodec, nullptr) < 0) {
            qCritical() << "Failed to open video codec";
            close();
            return false;
        }

        m_width = m_videoCodecCtx->width;
        m_height = m_videoCodecCtx->height;
        m_frameRate = av_q2d(videoStream->avg_frame_rate);
    }

    // Open audio codec
    if (m_audioStreamIndex >= 0) {
        AVStream* audioStream = m_formatCtx->streams[m_audioStreamIndex];
        const AVCodec* audioCodec = avcodec_find_decoder(audioStream->codecpar->codec_id);
        
        if (audioCodec) {
            m_audioCodecCtx = avcodec_alloc_context3(audioCodec);
            avcodec_parameters_to_context(m_audioCodecCtx, audioStream->codecpar);
            avcodec_open2(m_audioCodecCtx, audioCodec, nullptr);
        }
    }

    // Allocate frame
    m_frame = av_frame_alloc();
    
    // Duration
    m_duration = m_formatCtx->duration / (double)AV_TIME_BASE;

    m_isOpen = true;
    qDebug() << "Decoder opened successfully:" << m_filepath;
    return true;
}

void Decoder::close()
{
    if (m_swsCtx) {
        sws_freeContext(m_swsCtx);
        m_swsCtx = nullptr;
    }

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
        avformat_close_input(&m_formatCtx);
        m_formatCtx = nullptr;
    }

    m_isOpen = false;
}

bool Decoder::decodeVideoFrame(QImage& image)
{
    if (!m_isOpen || m_videoStreamIndex < 0) {
        return false;
    }

    // TODO: Implement frame decoding and conversion to QImage
    // This is a placeholder implementation
    qDebug() << "Decoding video frame...";
    return false;
}

bool Decoder::decodeAudioFrame(uint8_t* buffer, int& size)
{
    if (!m_isOpen || m_audioStreamIndex < 0) {
        return false;
    }

    // TODO: Implement audio frame decoding
    qDebug() << "Decoding audio frame...";
    return false;
}

bool Decoder::seek(double timestamp)
{
    if (!m_isOpen) {
        return false;
    }

    int64_t seekTarget = static_cast<int64_t>(timestamp * AV_TIME_BASE);
    
    if (av_seek_frame(m_formatCtx, -1, seekTarget, AVSEEK_FLAG_BACKWARD) < 0) {
        qWarning() << "Seek failed to timestamp:" << timestamp;
        return false;
    }

    if (m_videoCodecCtx) {
        avcodec_flush_buffers(m_videoCodecCtx);
    }
    
    if (m_audioCodecCtx) {
        avcodec_flush_buffers(m_audioCodecCtx);
    }

    return true;
}

} // namespace Media
} // namespace NovaCut

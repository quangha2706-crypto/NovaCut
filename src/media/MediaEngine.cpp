#include "MediaEngine.h"
#include "Decoder.h"
#include "Encoder.h"
#include <QDebug>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace NovaCut {
namespace Media {

MediaEngine::MediaEngine()
    : m_initialized(false)
{
}

MediaEngine::~MediaEngine()
{
    shutdown();
}

MediaEngine& MediaEngine::instance()
{
    static MediaEngine instance;
    return instance;
}

bool MediaEngine::initialize()
{
    if (m_initialized) {
        return true;
    }

    qDebug() << "Initializing MediaEngine...";
    
    // Initialize FFmpeg
#if LIBAVFORMAT_VERSION_INT < AV_VERSION_INT(58, 9, 100)
    av_register_all();
#endif
    
    qDebug() << "FFmpeg version:" << av_version_info();
    
    m_initialized = true;
    return true;
}

void MediaEngine::shutdown()
{
    if (!m_initialized) {
        return;
    }

    qDebug() << "Shutting down MediaEngine...";
    // Cleanup FFmpeg resources if needed
    m_initialized = false;
}

bool MediaEngine::getMediaInfo(const QString& filepath, MediaInfo& info)
{
    AVFormatContext* formatCtx = nullptr;
    
    if (avformat_open_input(&formatCtx, filepath.toUtf8().constData(), nullptr, nullptr) < 0) {
        qWarning() << "Failed to open media file:" << filepath;
        return false;
    }

    if (avformat_find_stream_info(formatCtx, nullptr) < 0) {
        qWarning() << "Failed to find stream info:" << filepath;
        avformat_close_input(&formatCtx);
        return false;
    }

    // Find video and audio streams
    int videoStreamIndex = -1;
    int audioStreamIndex = -1;

    for (unsigned int i = 0; i < formatCtx->nb_streams; i++) {
        AVMediaType codecType = formatCtx->streams[i]->codecpar->codec_type;
        if (codecType == AVMEDIA_TYPE_VIDEO && videoStreamIndex < 0) {
            videoStreamIndex = i;
        } else if (codecType == AVMEDIA_TYPE_AUDIO && audioStreamIndex < 0) {
            audioStreamIndex = i;
        }
    }

    // Extract video info
    if (videoStreamIndex >= 0) {
        AVStream* videoStream = formatCtx->streams[videoStreamIndex];
        AVCodecParameters* codecpar = videoStream->codecpar;
        
        info.width = codecpar->width;
        info.height = codecpar->height;
        info.videoBitrate = codecpar->bit_rate;
        info.frameRate = av_q2d(videoStream->avg_frame_rate);
        
        const AVCodec* codec = avcodec_find_decoder(codecpar->codec_id);
        info.videoCodec = codec ? codec->name : "unknown";
    }

    // Extract audio info
    if (audioStreamIndex >= 0) {
        AVStream* audioStream = formatCtx->streams[audioStreamIndex];
        AVCodecParameters* codecpar = audioStream->codecpar;
        
        info.audioChannels = codecpar->ch_layout.nb_channels;
        info.audioSampleRate = codecpar->sample_rate;
        info.audioBitrate = codecpar->bit_rate;
        
        const AVCodec* codec = avcodec_find_decoder(codecpar->codec_id);
        info.audioCodec = codec ? codec->name : "unknown";
    }

    // Duration
    info.duration = formatCtx->duration / (double)AV_TIME_BASE;

    avformat_close_input(&formatCtx);
    return true;
}

std::unique_ptr<Decoder> MediaEngine::createDecoder(const QString& filepath)
{
    return std::make_unique<Decoder>(filepath);
}

std::unique_ptr<Encoder> MediaEngine::createEncoder(const QString& filepath)
{
    return std::make_unique<Encoder>(filepath);
}

} // namespace Media
} // namespace NovaCut

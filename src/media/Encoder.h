#ifndef NOVACUT_MEDIA_ENCODER_H
#define NOVACUT_MEDIA_ENCODER_H

#include <QString>

struct AVFormatContext;
struct AVCodecContext;
struct AVFrame;
struct AVStream;

namespace NovaCut {
namespace Media {

class Encoder
{
public:
    explicit Encoder(const QString& filepath);
    ~Encoder();

    enum class VideoCodec {
        H264,
        H265,
        VP9
    };

    enum class AudioCodec {
        AAC,
        MP3,
        Opus
    };

    bool open(int width, int height, double frameRate, 
              VideoCodec videoCodec = VideoCodec::H264,
              AudioCodec audioCodec = AudioCodec::AAC);
    void close();
    
    bool isOpen() const { return m_isOpen; }

    // Encode frames
    bool encodeVideoFrame(const uint8_t* data, int size);
    bool encodeAudioFrame(const uint8_t* data, int size);

    // Finalize
    bool finalize();

private:
    QString m_filepath;
    bool m_isOpen;

    AVFormatContext* m_formatCtx;
    AVCodecContext* m_videoCodecCtx;
    AVCodecContext* m_audioCodecCtx;
    AVStream* m_videoStream;
    AVStream* m_audioStream;
    AVFrame* m_frame;

    int m_width;
    int m_height;
    double m_frameRate;
    int64_t m_videoFrameCount;
    int64_t m_audioFrameCount;
};

} // namespace Media
} // namespace NovaCut

#endif // NOVACUT_MEDIA_ENCODER_H

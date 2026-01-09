#ifndef NOVACUT_MEDIA_DECODER_H
#define NOVACUT_MEDIA_DECODER_H

#include <QString>
#include <QImage>

struct AVFormatContext;
struct AVCodecContext;
struct AVFrame;
struct SwsContext;

namespace NovaCut {
namespace Media {

class Decoder
{
public:
    explicit Decoder(const QString& filepath);
    ~Decoder();

    bool open();
    void close();
    
    bool isOpen() const { return m_isOpen; }

    // Decode next frame
    bool decodeVideoFrame(QImage& image);
    bool decodeAudioFrame(uint8_t* buffer, int& size);

    // Seek
    bool seek(double timestamp);

    // Info
    int width() const { return m_width; }
    int height() const { return m_height; }
    double frameRate() const { return m_frameRate; }
    double duration() const { return m_duration; }

private:
    QString m_filepath;
    bool m_isOpen;

    AVFormatContext* m_formatCtx;
    AVCodecContext* m_videoCodecCtx;
    AVCodecContext* m_audioCodecCtx;
    AVFrame* m_frame;
    SwsContext* m_swsCtx;

    int m_videoStreamIndex;
    int m_audioStreamIndex;
    int m_width;
    int m_height;
    double m_frameRate;
    double m_duration;
};

} // namespace Media
} // namespace NovaCut

#endif // NOVACUT_MEDIA_DECODER_H

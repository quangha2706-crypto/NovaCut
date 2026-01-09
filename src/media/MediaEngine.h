#ifndef NOVACUT_MEDIA_MEDIAENGINE_H
#define NOVACUT_MEDIA_MEDIAENGINE_H

#include <QObject>
#include <QString>
#include <memory>

namespace NovaCut {
namespace Media {

class Decoder;
class Encoder;

class MediaEngine : public QObject
{
    Q_OBJECT

public:
    static MediaEngine& instance();
    
    bool initialize();
    void shutdown();

    // Media info
    struct MediaInfo {
        int width;
        int height;
        double frameRate;
        double duration;
        int videoBitrate;
        int audioBitrate;
        int audioChannels;
        int audioSampleRate;
        QString videoCodec;
        QString audioCodec;
    };

    bool getMediaInfo(const QString& filepath, MediaInfo& info);

    // Decoder/Encoder factory
    std::unique_ptr<Decoder> createDecoder(const QString& filepath);
    std::unique_ptr<Encoder> createEncoder(const QString& filepath);

private:
    MediaEngine();
    ~MediaEngine();
    MediaEngine(const MediaEngine&) = delete;
    MediaEngine& operator=(const MediaEngine&) = delete;

    bool m_initialized;
};

} // namespace Media
} // namespace NovaCut

#endif // NOVACUT_MEDIA_MEDIAENGINE_H

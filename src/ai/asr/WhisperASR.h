#ifndef NOVACUT_AI_ASR_WHISPERASR_H
#define NOVACUT_AI_ASR_WHISPERASR_H

#include <QString>
#include <QVector>

namespace NovaCut {
namespace AI {

struct SubtitleSegment {
    double startTime;
    double endTime;
    QString text;
    QString language;
};

class WhisperASR
{
public:
    WhisperASR();
    ~WhisperASR();

    bool initialize();
    void shutdown();

    // Load model
    bool loadModel(const QString& modelPath);

    // Transcribe audio file
    bool transcribe(const QString& audioFilePath, QVector<SubtitleSegment>& segments);

    // Transcribe from raw audio data
    bool transcribeFromBuffer(const float* audioData, int sampleCount, 
                             QVector<SubtitleSegment>& segments);

    // Export subtitles
    bool exportSRT(const QVector<SubtitleSegment>& segments, const QString& filepath);
    bool exportVTT(const QVector<SubtitleSegment>& segments, const QString& filepath);

    // Language detection
    QString detectLanguage(const QString& audioFilePath);

    bool isInitialized() const { return m_initialized; }

private:
    bool m_initialized;
    void* m_whisperContext;  // Pointer to whisper.cpp context
    QString m_modelPath;
};

} // namespace AI
} // namespace NovaCut

#endif // NOVACUT_AI_ASR_WHISPERASR_H

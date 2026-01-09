#ifndef NOVACUT_AI_TTS_TTSENGINE_H
#define NOVACUT_AI_TTS_TTSENGINE_H

#include <QString>
#include <QVector>

namespace NovaCut {
namespace AI {

class TTSEngine
{
public:
    enum class OutputFormat {
        WAV,
        MP3,
        OGG
    };

    enum class Voice {
        Male,
        Female,
        Neutral
    };

    TTSEngine();
    ~TTSEngine();

    bool initialize();
    void shutdown();

    // Load ONNX model
    bool loadModel(const QString& modelPath);

    // Text to speech synthesis
    bool synthesize(const QString& text, const QString& outputPath,
                   Voice voice = Voice::Female,
                   OutputFormat format = OutputFormat::WAV);

    // Synthesize to buffer
    bool synthesizeToBuffer(const QString& text, QVector<float>& audioBuffer,
                          Voice voice = Voice::Female);

    // Configure voice parameters
    void setSpeed(float speed);  // 0.5 - 2.0
    void setPitch(float pitch);  // 0.5 - 2.0
    void setVolume(float volume); // 0.0 - 1.0

    bool isInitialized() const { return m_initialized; }

private:
    bool m_initialized;
    void* m_onnxSession;  // ONNX Runtime session
    QString m_modelPath;
    
    float m_speed;
    float m_pitch;
    float m_volume;
};

} // namespace AI
} // namespace NovaCut

#endif // NOVACUT_AI_TTS_TTSENGINE_H

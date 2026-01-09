#ifndef NOVACUT_AI_AIENGINE_H
#define NOVACUT_AI_AIENGINE_H

#include <QObject>
#include <memory>

namespace NovaCut {
namespace AI {

class WhisperASR;
class OCREngine;
class TTSEngine;

class AIEngine : public QObject
{
    Q_OBJECT

public:
    static AIEngine& instance();

    bool initialize();
    void shutdown();

    // Access to AI components
    WhisperASR* asr() const { return m_asr.get(); }
    OCREngine* ocr() const { return m_ocr.get(); }
    TTSEngine* tts() const { return m_tts.get(); }

private:
    AIEngine();
    ~AIEngine();
    AIEngine(const AIEngine&) = delete;
    AIEngine& operator=(const AIEngine&) = delete;

    bool m_initialized;
    std::unique_ptr<WhisperASR> m_asr;
    std::unique_ptr<OCREngine> m_ocr;
    std::unique_ptr<TTSEngine> m_tts;
};

} // namespace AI
} // namespace NovaCut

#endif // NOVACUT_AI_AIENGINE_H

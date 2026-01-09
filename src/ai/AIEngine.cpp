#include "AIEngine.h"
#include "asr/WhisperASR.h"
#include "ocr/OCREngine.h"
#include "tts/TTSEngine.h"
#include <QDebug>

namespace NovaCut {
namespace AI {

AIEngine::AIEngine()
    : m_initialized(false)
{
}

AIEngine::~AIEngine()
{
    shutdown();
}

AIEngine& AIEngine::instance()
{
    static AIEngine instance;
    return instance;
}

bool AIEngine::initialize()
{
    if (m_initialized) {
        return true;
    }

    qDebug() << "Initializing AIEngine...";

    // Initialize ASR
    m_asr = std::make_unique<WhisperASR>();
    if (!m_asr->initialize()) {
        qWarning() << "Failed to initialize ASR";
    }

    // Initialize OCR
    m_ocr = std::make_unique<OCREngine>();
    if (!m_ocr->initialize()) {
        qWarning() << "Failed to initialize OCR";
    }

    // Initialize TTS
    m_tts = std::make_unique<TTSEngine>();
    if (!m_tts->initialize()) {
        qWarning() << "Failed to initialize TTS";
    }

    m_initialized = true;
    qDebug() << "AIEngine initialized successfully";
    return true;
}

void AIEngine::shutdown()
{
    if (!m_initialized) {
        return;
    }

    qDebug() << "Shutting down AIEngine...";

    m_asr.reset();
    m_ocr.reset();
    m_tts.reset();

    m_initialized = false;
}

} // namespace AI
} // namespace NovaCut

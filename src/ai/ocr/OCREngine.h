#ifndef NOVACUT_AI_OCR_OCRENGINE_H
#define NOVACUT_AI_OCR_OCRENGINE_H

#include <QString>
#include <QVector>
#include <QRect>
#include <QImage>

namespace NovaCut {
namespace AI {

struct TextRegion {
    QRect boundingBox;
    QString text;
    float confidence;
};

class OCREngine
{
public:
    OCREngine();
    ~OCREngine();

    bool initialize();
    void shutdown();

    // Load ONNX model
    bool loadModel(const QString& modelPath);

    // Detect text regions in image
    bool detectTextRegions(const QImage& image, QVector<QRect>& regions);

    // Perform OCR on image
    bool recognizeText(const QImage& image, QVector<TextRegion>& results);

    // Perform OCR on specific region
    bool recognizeTextInRegion(const QImage& image, const QRect& region, QString& text);

    // Comic-specific OCR (detect speech bubbles and text)
    bool processComicPage(const QImage& image, QVector<TextRegion>& results);

    bool isInitialized() const { return m_initialized; }

private:
    bool m_initialized;
    void* m_onnxSession;  // ONNX Runtime session
    QString m_modelPath;
};

} // namespace AI
} // namespace NovaCut

#endif // NOVACUT_AI_OCR_OCRENGINE_H

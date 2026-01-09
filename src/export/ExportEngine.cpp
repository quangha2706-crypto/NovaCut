#include "ExportEngine.h"
#include "../core/Project.h"
#include "../timeline/Timeline.h"
#include "../media/Encoder.h"
#include <QDebug>

namespace NovaCut {
namespace Export {

ExportEngine::ExportEngine(QObject *parent)
    : QObject(parent)
    , m_isExporting(false)
    , m_progress(0)
    , m_cancelled(false)
{
}

ExportEngine::~ExportEngine()
{
}

bool ExportEngine::exportProject(Core::Project* project, const QString& outputPath,
                                 const ExportSettings& settings)
{
    if (!project) {
        qCritical() << "Invalid project";
        return false;
    }

    if (m_isExporting) {
        qWarning() << "Export already in progress";
        return false;
    }

    qDebug() << "Starting export to:" << outputPath;
    qDebug() << "Resolution:" << settings.width << "x" << settings.height;
    qDebug() << "Frame rate:" << settings.frameRate;
    qDebug() << "Quality:" << static_cast<int>(settings.quality);

    m_isExporting = true;
    m_progress = 0;
    m_cancelled = false;
    
    emit exportStarted();

    // Create encoder
    Media::Encoder encoder(outputPath);
    
    Media::Encoder::VideoCodec videoCodec = Media::Encoder::VideoCodec::H264;
    switch (settings.format) {
        case ExportFormat::MP4_H264:
        case ExportFormat::MOV_H264:
            videoCodec = Media::Encoder::VideoCodec::H264;
            break;
        case ExportFormat::MP4_H265:
            videoCodec = Media::Encoder::VideoCodec::H265;
            break;
        case ExportFormat::WEBM_VP9:
            videoCodec = Media::Encoder::VideoCodec::VP9;
            break;
    }

    if (!encoder.open(settings.width, settings.height, settings.frameRate, 
                     videoCodec, Media::Encoder::AudioCodec::AAC)) {
        qCritical() << "Failed to open encoder";
        m_isExporting = false;
        emit exportCompleted(false);
        return false;
    }

    // Get timeline
    Timeline::Timeline* timeline = project->timeline();
    double duration = timeline->duration();
    double currentTime = 0.0;
    double frameInterval = 1.0 / settings.frameRate;

    // Export frames
    while (currentTime < duration && !m_cancelled) {
        // TODO: Render frame at currentTime
        // TODO: Encode frame
        
        currentTime += frameInterval;
        m_progress = static_cast<int>((currentTime / duration) * 100);
        emit progressChanged(m_progress);
    }

    // Finalize
    if (!m_cancelled) {
        encoder.finalize();
        m_progress = 100;
        emit progressChanged(m_progress);
    }

    encoder.close();

    m_isExporting = false;

    if (m_cancelled) {
        qDebug() << "Export cancelled";
        emit exportCancelled();
        return false;
    } else {
        qDebug() << "Export completed successfully";
        emit exportCompleted(true);
        return true;
    }
}

void ExportEngine::cancel()
{
    if (m_isExporting) {
        qDebug() << "Cancelling export...";
        m_cancelled = true;
    }
}

} // namespace Export
} // namespace NovaCut

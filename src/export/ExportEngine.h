#ifndef NOVACUT_EXPORT_EXPORTENGINE_H
#define NOVACUT_EXPORT_EXPORTENGINE_H

#include <QObject>
#include <QString>

namespace NovaCut {
namespace Core {
    class Project;
}

namespace Export {

class ExportEngine : public QObject
{
    Q_OBJECT

public:
    enum class ExportFormat {
        MP4_H264,
        MP4_H265,
        WEBM_VP9,
        MOV_H264
    };

    enum class ExportQuality {
        Low,
        Medium,
        High,
        Ultra
    };

    struct ExportSettings {
        ExportFormat format;
        ExportQuality quality;
        int width;
        int height;
        double frameRate;
        int videoBitrate;
        int audioBitrate;
        bool includeAudio;
    };

    explicit ExportEngine(QObject *parent = nullptr);
    ~ExportEngine();

    // Export project
    bool exportProject(Core::Project* project, const QString& outputPath,
                      const ExportSettings& settings);

    // Export progress
    int progress() const { return m_progress; }
    bool isExporting() const { return m_isExporting; }
    
    // Cancel export
    void cancel();

signals:
    void progressChanged(int progress);
    void exportStarted();
    void exportCompleted(bool success);
    void exportCancelled();

private:
    bool m_isExporting;
    int m_progress;
    bool m_cancelled;
};

} // namespace Export
} // namespace NovaCut

#endif // NOVACUT_EXPORT_EXPORTENGINE_H

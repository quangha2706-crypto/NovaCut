#ifndef NOVACUT_TIMELINE_CLIP_H
#define NOVACUT_TIMELINE_CLIP_H

#include <QObject>
#include <QString>

namespace NovaCut {
namespace Timeline {

enum class ClipType {
    Video,
    Audio,
    Image,
    Subtitle
};

class Clip : public QObject
{
    Q_OBJECT

public:
    explicit Clip(const QString& filepath, ClipType type, QObject *parent = nullptr);
    ~Clip();

    // Properties
    QString filepath() const { return m_filepath; }
    ClipType type() const { return m_type; }
    
    double startTime() const { return m_startTime; }
    void setStartTime(double time);
    
    double duration() const { return m_duration; }
    void setDuration(double duration);
    
    double mediaStartTime() const { return m_mediaStartTime; }
    void setMediaStartTime(double time);
    
    bool isEnabled() const { return m_enabled; }
    void setEnabled(bool enabled);

    // Effects and properties
    double volume() const { return m_volume; }
    void setVolume(double volume);
    
    double opacity() const { return m_opacity; }
    void setOpacity(double opacity);

signals:
    void startTimeChanged(double time);
    void durationChanged(double duration);
    void enabledChanged(bool enabled);
    void volumeChanged(double volume);
    void opacityChanged(double opacity);

private:
    QString m_filepath;
    ClipType m_type;
    double m_startTime;
    double m_duration;
    double m_mediaStartTime;  // Trim start in source media
    bool m_enabled;
    
    // Effects
    double m_volume;
    double m_opacity;
};

} // namespace Timeline
} // namespace NovaCut

#endif // NOVACUT_TIMELINE_CLIP_H

#ifndef NOVACUT_TIMELINE_TRACK_H
#define NOVACUT_TIMELINE_TRACK_H

#include <QObject>
#include <QString>
#include <vector>
#include <memory>

namespace NovaCut {
namespace Timeline {

class Clip;

enum class TrackType {
    Video,
    Audio,
    Subtitle
};

class Track : public QObject
{
    Q_OBJECT

public:
    explicit Track(const QString& name, TrackType type = TrackType::Video, QObject *parent = nullptr);
    ~Track();

    QString name() const { return m_name; }
    void setName(const QString& name);

    TrackType type() const { return m_type; }
    
    bool isEnabled() const { return m_enabled; }
    void setEnabled(bool enabled);

    bool isMuted() const { return m_muted; }
    void setMuted(bool muted);

    // Clip management
    int clipCount() const { return static_cast<int>(m_clips.size()); }
    Clip* clip(int index) const;
    void addClip(std::unique_ptr<Clip> clip);
    void removeClip(int index);
    
    double duration() const;

signals:
    void nameChanged(const QString& name);
    void enabledChanged(bool enabled);
    void mutedChanged(bool muted);
    void clipAdded(int index);
    void clipRemoved(int index);

private:
    QString m_name;
    TrackType m_type;
    bool m_enabled;
    bool m_muted;
    std::vector<std::unique_ptr<Clip>> m_clips;
};

} // namespace Timeline
} // namespace NovaCut

#endif // NOVACUT_TIMELINE_TRACK_H

#ifndef NOVACUT_TIMELINE_TIMELINE_H
#define NOVACUT_TIMELINE_TIMELINE_H

#include <QObject>
#include <vector>
#include <memory>

namespace NovaCut {
namespace Timeline {

class Track;
class Clip;

class Timeline : public QObject
{
    Q_OBJECT

public:
    explicit Timeline(QObject *parent = nullptr);
    ~Timeline();

    // Track management
    int trackCount() const { return static_cast<int>(m_tracks.size()); }
    Track* track(int index) const;
    Track* addTrack(const QString& name = QString());
    void removeTrack(int index);
    void moveTrack(int fromIndex, int toIndex);

    // Playback
    double currentTime() const { return m_currentTime; }
    void setCurrentTime(double time);
    
    double duration() const { return m_duration; }
    
    bool isPlaying() const { return m_playing; }
    void play();
    void pause();
    void stop();

signals:
    void trackAdded(int index);
    void trackRemoved(int index);
    void currentTimeChanged(double time);
    void playbackStateChanged(bool playing);

private:
    void updateDuration();

    std::vector<std::unique_ptr<Track>> m_tracks;
    double m_currentTime;
    double m_duration;
    bool m_playing;
};

} // namespace Timeline
} // namespace NovaCut

#endif // NOVACUT_TIMELINE_TIMELINE_H

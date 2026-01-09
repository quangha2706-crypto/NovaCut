#include "Timeline.h"
#include "Track.h"
#include <QDebug>

namespace NovaCut {
namespace Timeline {

Timeline::Timeline(QObject *parent)
    : QObject(parent)
    , m_currentTime(0.0)
    , m_duration(0.0)
    , m_playing(false)
{
}

Timeline::~Timeline()
{
}

Track* Timeline::track(int index) const
{
    if (index < 0 || index >= static_cast<int>(m_tracks.size())) {
        return nullptr;
    }
    return m_tracks[index].get();
}

Track* Timeline::addTrack(const QString& name)
{
    QString trackName = name;
    if (trackName.isEmpty()) {
        trackName = QString("Track %1").arg(m_tracks.size() + 1);
    }

    auto track = std::make_unique<Track>(trackName);
    Track* trackPtr = track.get();
    
    m_tracks.push_back(std::move(track));
    
    emit trackAdded(static_cast<int>(m_tracks.size()) - 1);
    qDebug() << "Track added:" << trackName;
    
    return trackPtr;
}

void Timeline::removeTrack(int index)
{
    if (index < 0 || index >= static_cast<int>(m_tracks.size())) {
        qWarning() << "Invalid track index:" << index;
        return;
    }

    m_tracks.erase(m_tracks.begin() + index);
    emit trackRemoved(index);
    updateDuration();
}

void Timeline::moveTrack(int fromIndex, int toIndex)
{
    if (fromIndex < 0 || fromIndex >= static_cast<int>(m_tracks.size()) ||
        toIndex < 0 || toIndex >= static_cast<int>(m_tracks.size())) {
        qWarning() << "Invalid track indices:" << fromIndex << toIndex;
        return;
    }

    if (fromIndex == toIndex) {
        return;
    }

    auto track = std::move(m_tracks[fromIndex]);
    m_tracks.erase(m_tracks.begin() + fromIndex);
    m_tracks.insert(m_tracks.begin() + toIndex, std::move(track));
}

void Timeline::setCurrentTime(double time)
{
    if (time < 0.0) {
        time = 0.0;
    }
    
    if (m_currentTime != time) {
        m_currentTime = time;
        emit currentTimeChanged(m_currentTime);
    }
}

void Timeline::play()
{
    if (!m_playing) {
        m_playing = true;
        emit playbackStateChanged(m_playing);
        qDebug() << "Timeline playback started";
    }
}

void Timeline::pause()
{
    if (m_playing) {
        m_playing = false;
        emit playbackStateChanged(m_playing);
        qDebug() << "Timeline playback paused";
    }
}

void Timeline::stop()
{
    if (m_playing) {
        m_playing = false;
    }
    setCurrentTime(0.0);
    emit playbackStateChanged(m_playing);
    qDebug() << "Timeline playback stopped";
}

void Timeline::updateDuration()
{
    double maxDuration = 0.0;
    
    for (const auto& track : m_tracks) {
        double trackDuration = track->duration();
        if (trackDuration > maxDuration) {
            maxDuration = trackDuration;
        }
    }
    
    m_duration = maxDuration;
}

} // namespace Timeline
} // namespace NovaCut

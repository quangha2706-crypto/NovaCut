#include "Track.h"
#include "Clip.h"
#include <QDebug>

namespace NovaCut {
namespace Timeline {

Track::Track(const QString& name, TrackType type, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_type(type)
    , m_enabled(true)
    , m_muted(false)
{
}

Track::~Track()
{
}

void Track::setName(const QString& name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Track::setEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        emit enabledChanged(m_enabled);
    }
}

void Track::setMuted(bool muted)
{
    if (m_muted != muted) {
        m_muted = muted;
        emit mutedChanged(m_muted);
    }
}

Clip* Track::clip(int index) const
{
    if (index < 0 || index >= static_cast<int>(m_clips.size())) {
        return nullptr;
    }
    return m_clips[index].get();
}

void Track::addClip(std::unique_ptr<Clip> clip)
{
    if (!clip) {
        qWarning() << "Cannot add null clip";
        return;
    }

    m_clips.push_back(std::move(clip));
    emit clipAdded(static_cast<int>(m_clips.size()) - 1);
}

void Track::removeClip(int index)
{
    if (index < 0 || index >= static_cast<int>(m_clips.size())) {
        qWarning() << "Invalid clip index:" << index;
        return;
    }

    m_clips.erase(m_clips.begin() + index);
    emit clipRemoved(index);
}

double Track::duration() const
{
    double maxEnd = 0.0;
    
    for (const auto& clip : m_clips) {
        double end = clip->startTime() + clip->duration();
        if (end > maxEnd) {
            maxEnd = end;
        }
    }
    
    return maxEnd;
}

} // namespace Timeline
} // namespace NovaCut

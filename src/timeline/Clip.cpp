#include "Clip.h"

namespace NovaCut {
namespace Timeline {

Clip::Clip(const QString& filepath, ClipType type, QObject *parent)
    : QObject(parent)
    , m_filepath(filepath)
    , m_type(type)
    , m_startTime(0.0)
    , m_duration(0.0)
    , m_mediaStartTime(0.0)
    , m_enabled(true)
    , m_volume(1.0)
    , m_opacity(1.0)
{
}

Clip::~Clip()
{
}

void Clip::setStartTime(double time)
{
    if (time < 0.0) {
        time = 0.0;
    }
    
    if (m_startTime != time) {
        m_startTime = time;
        emit startTimeChanged(m_startTime);
    }
}

void Clip::setDuration(double duration)
{
    if (duration < 0.0) {
        duration = 0.0;
    }
    
    if (m_duration != duration) {
        m_duration = duration;
        emit durationChanged(m_duration);
    }
}

void Clip::setMediaStartTime(double time)
{
    if (time < 0.0) {
        time = 0.0;
    }
    
    m_mediaStartTime = time;
}

void Clip::setEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        emit enabledChanged(m_enabled);
    }
}

void Clip::setVolume(double volume)
{
    if (volume < 0.0) {
        volume = 0.0;
    } else if (volume > 1.0) {
        volume = 1.0;
    }
    
    if (m_volume != volume) {
        m_volume = volume;
        emit volumeChanged(m_volume);
    }
}

void Clip::setOpacity(double opacity)
{
    if (opacity < 0.0) {
        opacity = 0.0;
    } else if (opacity > 1.0) {
        opacity = 1.0;
    }
    
    if (m_opacity != opacity) {
        m_opacity = opacity;
        emit opacityChanged(m_opacity);
    }
}

} // namespace Timeline
} // namespace NovaCut

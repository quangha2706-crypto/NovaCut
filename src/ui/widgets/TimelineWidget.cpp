#include "TimelineWidget.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>

namespace NovaCut {
namespace UI {

TimelineWidget::TimelineWidget(QWidget *parent)
    : QWidget(parent)
    , m_duration(60.0)
    , m_currentTime(0.0)
    , m_zoom(1.0)
    , m_scrollOffset(0.0)
    , m_draggingPlayhead(false)
{
    setMinimumHeight(200);
    setMouseTracking(true);
}

TimelineWidget::~TimelineWidget()
{
}

void TimelineWidget::setDuration(double duration)
{
    m_duration = duration;
    update();
}

void TimelineWidget::setCurrentTime(double time)
{
    if (time < 0.0) time = 0.0;
    if (time > m_duration) time = m_duration;
    
    if (m_currentTime != time) {
        m_currentTime = time;
        emit currentTimeChanged(m_currentTime);
        update();
    }
}

void TimelineWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Background
    painter.fillRect(rect(), QColor(45, 45, 48));

    drawTimeRuler(painter);
    drawTracks(painter);
    drawPlayhead(painter);
}

void TimelineWidget::drawTimeRuler(QPainter& painter)
{
    const int rulerHeight = 30;
    
    painter.fillRect(0, 0, width(), rulerHeight, QColor(30, 30, 30));
    
    painter.setPen(QColor(180, 180, 180));
    
    // Draw time markers
    double pixelsPerSecond = width() / (m_duration * m_zoom);
    int secondInterval = 5;
    
    if (pixelsPerSecond * secondInterval < 50) {
        secondInterval = 10;
    }
    
    for (double t = 0; t <= m_duration; t += secondInterval) {
        int x = static_cast<int>(t * pixelsPerSecond);
        painter.drawLine(x, rulerHeight - 10, x, rulerHeight);
        
        int minutes = static_cast<int>(t / 60);
        int seconds = static_cast<int>(t) % 60;
        QString timeStr = QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QChar('0'));
        painter.drawText(x + 2, rulerHeight - 15, timeStr);
    }
}

void TimelineWidget::drawTracks(QPainter& painter)
{
    const int rulerHeight = 30;
    const int trackHeight = 60;
    const int trackSpacing = 5;
    
    // Draw placeholder tracks
    for (int i = 0; i < 3; ++i) {
        int y = rulerHeight + i * (trackHeight + trackSpacing);
        
        QRect trackRect(0, y, width(), trackHeight);
        painter.fillRect(trackRect, QColor(60, 60, 60));
        
        painter.setPen(QColor(100, 100, 100));
        painter.drawRect(trackRect);
        
        painter.setPen(QColor(200, 200, 200));
        painter.drawText(trackRect.adjusted(10, 0, 0, 0), 
                        Qt::AlignLeft | Qt::AlignVCenter,
                        QString("Track %1").arg(i + 1));
    }
}

void TimelineWidget::drawPlayhead(QPainter& painter)
{
    double pixelsPerSecond = width() / (m_duration * m_zoom);
    int x = static_cast<int>(m_currentTime * pixelsPerSecond);
    
    painter.setPen(QPen(QColor(255, 0, 0), 2));
    painter.drawLine(x, 0, x, height());
    
    // Draw playhead handle
    QPolygon triangle;
    triangle << QPoint(x, 10) << QPoint(x - 8, 25) << QPoint(x + 8, 25);
    painter.setBrush(QColor(255, 0, 0));
    painter.drawPolygon(triangle);
}

void TimelineWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        double pixelsPerSecond = width() / (m_duration * m_zoom);
        double clickedTime = event->pos().x() / pixelsPerSecond;
        
        setCurrentTime(clickedTime);
        m_draggingPlayhead = true;
    }
}

void TimelineWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_draggingPlayhead) {
        double pixelsPerSecond = width() / (m_duration * m_zoom);
        double clickedTime = event->pos().x() / pixelsPerSecond;
        setCurrentTime(clickedTime);
    }
}

void TimelineWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_draggingPlayhead = false;
    }
}

void TimelineWidget::wheelEvent(QWheelEvent *event)
{
    // Zoom in/out with mouse wheel
    double zoomDelta = event->angleDelta().y() > 0 ? 1.1 : 0.9;
    m_zoom *= zoomDelta;
    
    if (m_zoom < 0.1) m_zoom = 0.1;
    if (m_zoom > 10.0) m_zoom = 10.0;
    
    update();
}

} // namespace UI
} // namespace NovaCut

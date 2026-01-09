#ifndef NOVACUT_UI_WIDGETS_TIMELINEWIDGET_H
#define NOVACUT_UI_WIDGETS_TIMELINEWIDGET_H

#include <QWidget>
#include <QPainter>

namespace NovaCut {
namespace UI {

class TimelineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimelineWidget(QWidget *parent = nullptr);
    ~TimelineWidget();

    void setDuration(double duration);
    void setCurrentTime(double time);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

signals:
    void currentTimeChanged(double time);

private:
    void drawTimeline(QPainter& painter);
    void drawTracks(QPainter& painter);
    void drawPlayhead(QPainter& painter);
    void drawTimeRuler(QPainter& painter);

    double m_duration;
    double m_currentTime;
    double m_zoom;
    double m_scrollOffset;
    bool m_draggingPlayhead;
};

} // namespace UI
} // namespace NovaCut

#endif // NOVACUT_UI_WIDGETS_TIMELINEWIDGET_H

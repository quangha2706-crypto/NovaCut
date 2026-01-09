#include "PreviewWidget.h"
#include <QPainter>
#include <QResizeEvent>

namespace NovaCut {
namespace UI {

PreviewWidget::PreviewWidget(QWidget *parent)
    : QWidget(parent)
    , m_hasFrame(false)
{
    setMinimumSize(320, 180);
    setStyleSheet("background-color: black;");
}

PreviewWidget::~PreviewWidget()
{
}

void PreviewWidget::setFrame(const QImage& frame)
{
    m_currentFrame = frame;
    m_hasFrame = true;
    updateScaledFrame();
    update();
}

void PreviewWidget::clear()
{
    m_currentFrame = QImage();
    m_scaledFrame = QImage();
    m_hasFrame = false;
    update();
}

void PreviewWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    if (m_hasFrame && !m_scaledFrame.isNull()) {
        // Center the frame
        int x = (width() - m_scaledFrame.width()) / 2;
        int y = (height() - m_scaledFrame.height()) / 2;
        painter.drawImage(x, y, m_scaledFrame);
    } else {
        // Draw placeholder text
        painter.setPen(QColor(128, 128, 128));
        painter.drawText(rect(), Qt::AlignCenter, tr("No Preview"));
    }
}

void PreviewWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (m_hasFrame) {
        updateScaledFrame();
    }
}

void PreviewWidget::updateScaledFrame()
{
    if (m_currentFrame.isNull()) {
        return;
    }

    // Scale frame to fit widget while maintaining aspect ratio
    m_scaledFrame = m_currentFrame.scaled(size(), 
                                         Qt::KeepAspectRatio, 
                                         Qt::SmoothTransformation);
}

} // namespace UI
} // namespace NovaCut

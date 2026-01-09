#ifndef NOVACUT_UI_WIDGETS_PREVIEWWIDGET_H
#define NOVACUT_UI_WIDGETS_PREVIEWWIDGET_H

#include <QWidget>
#include <QImage>

namespace NovaCut {
namespace UI {

class PreviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewWidget(QWidget *parent = nullptr);
    ~PreviewWidget();

    void setFrame(const QImage& frame);
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QImage m_currentFrame;
    QImage m_scaledFrame;
    bool m_hasFrame;
    
    void updateScaledFrame();
};

} // namespace UI
} // namespace NovaCut

#endif // NOVACUT_UI_WIDGETS_PREVIEWWIDGET_H

#ifndef NOVACUT_CORE_PROJECT_H
#define NOVACUT_CORE_PROJECT_H

#include <QString>
#include <QObject>
#include <memory>

namespace NovaCut {
namespace Timeline {
    class Timeline;
}

namespace Core {

class Project : public QObject
{
    Q_OBJECT

public:
    explicit Project(QObject *parent = nullptr);
    ~Project();

    // Project file operations
    bool load(const QString& filepath);
    bool save(const QString& filepath);

    // Project properties
    QString name() const { return m_name; }
    void setName(const QString& name) { m_name = name; }

    QString filepath() const { return m_filepath; }
    
    // Timeline access
    Timeline::Timeline* timeline() const { return m_timeline.get(); }

    // Project settings
    int width() const { return m_width; }
    int height() const { return m_height; }
    double frameRate() const { return m_frameRate; }

    void setResolution(int width, int height);
    void setFrameRate(double fps);

signals:
    void modified();
    void nameChanged(const QString& name);

private:
    QString m_name;
    QString m_filepath;
    std::unique_ptr<Timeline::Timeline> m_timeline;
    
    // Project settings
    int m_width;
    int m_height;
    double m_frameRate;
    bool m_modified;
};

} // namespace Core
} // namespace NovaCut

#endif // NOVACUT_CORE_PROJECT_H

#include "Project.h"
#include "../timeline/Timeline.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

namespace NovaCut {
namespace Core {

Project::Project(QObject *parent)
    : QObject(parent)
    , m_name("Untitled Project")
    , m_width(1920)
    , m_height(1080)
    , m_frameRate(30.0)
    , m_modified(false)
{
    m_timeline = std::make_unique<Timeline::Timeline>();
}

Project::~Project()
{
}

bool Project::load(const QString& filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Cannot open project file:" << filepath;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        qCritical() << "Invalid project file format";
        return false;
    }

    QJsonObject obj = doc.object();
    m_name = obj["name"].toString("Untitled Project");
    m_width = obj["width"].toInt(1920);
    m_height = obj["height"].toInt(1080);
    m_frameRate = obj["frameRate"].toDouble(30.0);
    m_filepath = filepath;

    // TODO: Load timeline data
    
    m_modified = false;
    qDebug() << "Project loaded successfully:" << m_name;
    return true;
}

bool Project::save(const QString& filepath)
{
    QJsonObject obj;
    obj["name"] = m_name;
    obj["width"] = m_width;
    obj["height"] = m_height;
    obj["frameRate"] = m_frameRate;
    obj["version"] = "1.0";

    // TODO: Save timeline data

    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << "Cannot write project file:" << filepath;
        return false;
    }

    file.write(data);
    file.close();

    m_filepath = filepath;
    m_modified = false;
    
    qDebug() << "Project saved successfully:" << filepath;
    return true;
}

void Project::setResolution(int width, int height)
{
    if (m_width != width || m_height != height) {
        m_width = width;
        m_height = height;
        m_modified = true;
        emit modified();
    }
}

void Project::setFrameRate(double fps)
{
    if (m_frameRate != fps) {
        m_frameRate = fps;
        m_modified = true;
        emit modified();
    }
}

} // namespace Core
} // namespace NovaCut

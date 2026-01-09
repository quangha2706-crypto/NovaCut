#ifndef NOVACUT_CORE_APPLICATION_H
#define NOVACUT_CORE_APPLICATION_H

#include <memory>
#include <QObject>

namespace NovaCut {
namespace Core {

class Project;

class Application : public QObject
{
    Q_OBJECT

public:
    explicit Application(QObject *parent = nullptr);
    ~Application();

    bool initialize();
    void shutdown();

    Project* currentProject() const { return m_currentProject.get(); }
    bool hasProject() const { return m_currentProject != nullptr; }

    // Create/load/save project
    bool createNewProject();
    bool loadProject(const QString& filepath);
    bool saveProject(const QString& filepath);
    void closeProject();

signals:
    void projectCreated();
    void projectLoaded();
    void projectClosed();

private:
    std::unique_ptr<Project> m_currentProject;
    bool m_initialized;
};

} // namespace Core
} // namespace NovaCut

#endif // NOVACUT_CORE_APPLICATION_H

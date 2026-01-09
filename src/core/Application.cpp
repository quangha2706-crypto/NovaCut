#include "Application.h"
#include "Project.h"
#include <QDebug>

namespace NovaCut {
namespace Core {

Application::Application(QObject *parent)
    : QObject(parent)
    , m_currentProject(nullptr)
    , m_initialized(false)
{
}

Application::~Application()
{
    shutdown();
}

bool Application::initialize()
{
    if (m_initialized) {
        qWarning() << "Application already initialized";
        return true;
    }

    qDebug() << "Initializing NovaCut application...";

    // Initialize components
    // TODO: Initialize FFmpeg
    // TODO: Initialize AI engines
    // TODO: Load configuration

    m_initialized = true;
    qDebug() << "Application initialized successfully";
    return true;
}

void Application::shutdown()
{
    if (!m_initialized) {
        return;
    }

    qDebug() << "Shutting down application...";
    closeProject();
    
    // TODO: Cleanup resources
    m_initialized = false;
}

bool Application::createNewProject()
{
    if (m_currentProject) {
        closeProject();
    }

    qDebug() << "Creating new project...";
    m_currentProject = std::make_unique<Project>();
    
    emit projectCreated();
    return true;
}

bool Application::loadProject(const QString& filepath)
{
    if (m_currentProject) {
        closeProject();
    }

    qDebug() << "Loading project from:" << filepath;
    
    auto project = std::make_unique<Project>();
    if (!project->load(filepath)) {
        qCritical() << "Failed to load project:" << filepath;
        return false;
    }

    m_currentProject = std::move(project);
    emit projectLoaded();
    return true;
}

bool Application::saveProject(const QString& filepath)
{
    if (!m_currentProject) {
        qWarning() << "No project to save";
        return false;
    }

    qDebug() << "Saving project to:" << filepath;
    return m_currentProject->save(filepath);
}

void Application::closeProject()
{
    if (!m_currentProject) {
        return;
    }

    qDebug() << "Closing project...";
    m_currentProject.reset();
    emit projectClosed();
}

} // namespace Core
} // namespace NovaCut

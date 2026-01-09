#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include "core/Application.h"
#include "ui/MainWindow.h"

int main(int argc, char *argv[])
{
    // Enable high DPI scaling
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);
    
    // Set application information
    QApplication::setApplicationName("NovaCut");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("NovaCut");
    QApplication::setOrganizationDomain("novacut.app");

    // Parse command line arguments
    QCommandLineParser parser;
    parser.setApplicationDescription("AI-powered video editor");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "Project file to open (optional)");
    parser.process(app);

    qDebug() << "Starting NovaCut Video Editor...";

    // Initialize application core
    NovaCut::Core::Application novaCutApp;
    if (!novaCutApp.initialize()) {
        qCritical() << "Failed to initialize application";
        return 1;
    }

    // Create and show main window
    NovaCut::UI::MainWindow mainWindow;
    mainWindow.show();

    // Open file if specified
    const QStringList args = parser.positionalArguments();
    if (!args.isEmpty()) {
        mainWindow.openProject(args.first());
    }

    return app.exec();
}

#include "MainWindow.h"
#include "widgets/TimelineWidget.h"
#include "widgets/PreviewWidget.h"
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QSplitter>
#include <QDebug>

namespace NovaCut {
namespace UI {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_timelineWidget(nullptr)
    , m_previewWidget(nullptr)
{
    setWindowTitle("NovaCut - AI Video Editor");
    resize(1280, 720);

    createActions();
    createMenus();
    createToolbars();
    createStatusBar();
    setupCentralWidget();
    createDockWidgets();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    // File actions
    m_newProjectAction = new QAction(tr("&New Project"), this);
    m_newProjectAction->setShortcut(QKeySequence::New);
    connect(m_newProjectAction, &QAction::triggered, this, &MainWindow::onNewProject);

    m_openProjectAction = new QAction(tr("&Open Project..."), this);
    m_openProjectAction->setShortcut(QKeySequence::Open);
    connect(m_openProjectAction, &QAction::triggered, this, &MainWindow::onOpenProject);

    m_saveProjectAction = new QAction(tr("&Save Project"), this);
    m_saveProjectAction->setShortcut(QKeySequence::Save);
    connect(m_saveProjectAction, &QAction::triggered, this, &MainWindow::onSaveProject);

    m_saveProjectAsAction = new QAction(tr("Save Project &As..."), this);
    m_saveProjectAsAction->setShortcut(QKeySequence::SaveAs);
    connect(m_saveProjectAsAction, &QAction::triggered, this, &MainWindow::onSaveProjectAs);

    m_exportAction = new QAction(tr("&Export..."), this);
    connect(m_exportAction, &QAction::triggered, this, &MainWindow::onExport);

    m_importMediaAction = new QAction(tr("&Import Media..."), this);
    connect(m_importMediaAction, &QAction::triggered, this, &MainWindow::onImportMedia);

    m_exitAction = new QAction(tr("E&xit"), this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);

    // Edit actions
    m_undoAction = new QAction(tr("&Undo"), this);
    m_undoAction->setShortcut(QKeySequence::Undo);
    connect(m_undoAction, &QAction::triggered, this, &MainWindow::onUndo);

    m_redoAction = new QAction(tr("&Redo"), this);
    m_redoAction->setShortcut(QKeySequence::Redo);
    connect(m_redoAction, &QAction::triggered, this, &MainWindow::onRedo);

    m_cutAction = new QAction(tr("Cu&t"), this);
    m_cutAction->setShortcut(QKeySequence::Cut);
    connect(m_cutAction, &QAction::triggered, this, &MainWindow::onCut);

    m_copyAction = new QAction(tr("&Copy"), this);
    m_copyAction->setShortcut(QKeySequence::Copy);
    connect(m_copyAction, &QAction::triggered, this, &MainWindow::onCopy);

    m_pasteAction = new QAction(tr("&Paste"), this);
    m_pasteAction->setShortcut(QKeySequence::Paste);
    connect(m_pasteAction, &QAction::triggered, this, &MainWindow::onPaste);

    m_deleteAction = new QAction(tr("&Delete"), this);
    m_deleteAction->setShortcut(QKeySequence::Delete);
    connect(m_deleteAction, &QAction::triggered, this, &MainWindow::onDelete);

    // Playback actions
    m_playAction = new QAction(tr("&Play"), this);
    m_playAction->setShortcut(Qt::Key_Space);
    connect(m_playAction, &QAction::triggered, this, &MainWindow::onPlay);

    m_pauseAction = new QAction(tr("Pa&use"), this);
    connect(m_pauseAction, &QAction::triggered, this, &MainWindow::onPause);

    m_stopAction = new QAction(tr("&Stop"), this);
    connect(m_stopAction, &QAction::triggered, this, &MainWindow::onStop);

    // Help actions
    m_aboutAction = new QAction(tr("&About"), this);
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
}

void MainWindow::createMenus()
{
    // File menu
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newProjectAction);
    m_fileMenu->addAction(m_openProjectAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_saveProjectAction);
    m_fileMenu->addAction(m_saveProjectAsAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_importMediaAction);
    m_fileMenu->addAction(m_exportAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    // Edit menu
    m_editMenu = menuBar()->addMenu(tr("&Edit"));
    m_editMenu->addAction(m_undoAction);
    m_editMenu->addAction(m_redoAction);
    m_editMenu->addSeparator();
    m_editMenu->addAction(m_cutAction);
    m_editMenu->addAction(m_copyAction);
    m_editMenu->addAction(m_pasteAction);
    m_editMenu->addAction(m_deleteAction);

    // View menu
    m_viewMenu = menuBar()->addMenu(tr("&View"));

    // Help menu
    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_helpMenu->addAction(m_aboutAction);
}

void MainWindow::createToolbars()
{
    // File toolbar
    m_fileToolbar = addToolBar(tr("File"));
    m_fileToolbar->addAction(m_newProjectAction);
    m_fileToolbar->addAction(m_openProjectAction);
    m_fileToolbar->addAction(m_saveProjectAction);
    m_fileToolbar->addSeparator();
    m_fileToolbar->addAction(m_importMediaAction);
    m_fileToolbar->addAction(m_exportAction);

    // Edit toolbar
    m_editToolbar = addToolBar(tr("Edit"));
    m_editToolbar->addAction(m_undoAction);
    m_editToolbar->addAction(m_redoAction);
    m_editToolbar->addSeparator();
    m_editToolbar->addAction(m_cutAction);
    m_editToolbar->addAction(m_copyAction);
    m_editToolbar->addAction(m_pasteAction);
    m_editToolbar->addAction(m_deleteAction);

    // Playback toolbar
    m_playbackToolbar = addToolBar(tr("Playback"));
    m_playbackToolbar->addAction(m_playAction);
    m_playbackToolbar->addAction(m_pauseAction);
    m_playbackToolbar->addAction(m_stopAction);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::setupCentralWidget()
{
    // Create main splitter
    QSplitter* splitter = new QSplitter(Qt::Vertical, this);

    // Preview widget
    m_previewWidget = new PreviewWidget(this);
    splitter->addWidget(m_previewWidget);

    // Timeline widget
    m_timelineWidget = new TimelineWidget(this);
    splitter->addWidget(m_timelineWidget);

    // Set splitter proportions
    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1, 1);

    setCentralWidget(splitter);
}

void MainWindow::createDockWidgets()
{
    // TODO: Add dock widgets for:
    // - Media library
    // - Effects panel
    // - Properties panel
    // - Audio mixer
}

void MainWindow::openProject(const QString& filepath)
{
    qDebug() << "Opening project:" << filepath;
    // TODO: Implement project opening
    m_currentProjectPath = filepath;
    statusBar()->showMessage(tr("Opened: %1").arg(filepath));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // TODO: Check for unsaved changes
    event->accept();
}

void MainWindow::onNewProject()
{
    qDebug() << "New project";
    // TODO: Implement new project creation
}

void MainWindow::onOpenProject()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open Project"),
                                                   QString(),
                                                   tr("NovaCut Projects (*.ncp)"));
    if (!filepath.isEmpty()) {
        openProject(filepath);
    }
}

void MainWindow::onSaveProject()
{
    if (m_currentProjectPath.isEmpty()) {
        onSaveProjectAs();
    } else {
        qDebug() << "Saving project to:" << m_currentProjectPath;
        // TODO: Implement project saving
    }
}

void MainWindow::onSaveProjectAs()
{
    QString filepath = QFileDialog::getSaveFileName(this, tr("Save Project As"),
                                                   QString(),
                                                   tr("NovaCut Projects (*.ncp)"));
    if (!filepath.isEmpty()) {
        m_currentProjectPath = filepath;
        onSaveProject();
    }
}

void MainWindow::onExport()
{
    qDebug() << "Export";
    // TODO: Show export dialog
}

void MainWindow::onImportMedia()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Import Media"),
                                                      QString(),
                                                      tr("Media Files (*.mp4 *.avi *.mov *.mp3 *.wav *.png *.jpg)"));
    if (!files.isEmpty()) {
        qDebug() << "Importing" << files.size() << "files";
        // TODO: Implement media import
    }
}

void MainWindow::onUndo()
{
    qDebug() << "Undo";
}

void MainWindow::onRedo()
{
    qDebug() << "Redo";
}

void MainWindow::onCut()
{
    qDebug() << "Cut";
}

void MainWindow::onCopy()
{
    qDebug() << "Copy";
}

void MainWindow::onPaste()
{
    qDebug() << "Paste";
}

void MainWindow::onDelete()
{
    qDebug() << "Delete";
}

void MainWindow::onPlay()
{
    qDebug() << "Play";
    // TODO: Implement playback
}

void MainWindow::onPause()
{
    qDebug() << "Pause";
}

void MainWindow::onStop()
{
    qDebug() << "Stop";
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, tr("About NovaCut"),
                      tr("<h2>NovaCut Video Editor</h2>"
                         "<p>Version 1.0.0</p>"
                         "<p>AI-powered video editing application</p>"
                         "<p>Built with Qt and C++</p>"));
}

} // namespace UI
} // namespace NovaCut

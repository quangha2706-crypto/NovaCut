#ifndef NOVACUT_UI_MAINWINDOW_H
#define NOVACUT_UI_MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>

namespace NovaCut {
namespace UI {

class TimelineWidget;
class PreviewWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openProject(const QString& filepath);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onNewProject();
    void onOpenProject();
    void onSaveProject();
    void onSaveProjectAs();
    void onExport();
    void onImportMedia();
    void onUndo();
    void onRedo();
    void onCut();
    void onCopy();
    void onPaste();
    void onDelete();
    void onPlay();
    void onPause();
    void onStop();
    void onAbout();

private:
    void createActions();
    void createMenus();
    void createToolbars();
    void createStatusBar();
    void createDockWidgets();
    void setupCentralWidget();

    // Menus
    QMenu* m_fileMenu;
    QMenu* m_editMenu;
    QMenu* m_viewMenu;
    QMenu* m_helpMenu;

    // Toolbars
    QToolBar* m_fileToolbar;
    QToolBar* m_editToolbar;
    QToolBar* m_playbackToolbar;

    // Actions
    QAction* m_newProjectAction;
    QAction* m_openProjectAction;
    QAction* m_saveProjectAction;
    QAction* m_saveProjectAsAction;
    QAction* m_exportAction;
    QAction* m_importMediaAction;
    QAction* m_exitAction;
    QAction* m_undoAction;
    QAction* m_redoAction;
    QAction* m_cutAction;
    QAction* m_copyAction;
    QAction* m_pasteAction;
    QAction* m_deleteAction;
    QAction* m_playAction;
    QAction* m_pauseAction;
    QAction* m_stopAction;
    QAction* m_aboutAction;

    // Widgets
    TimelineWidget* m_timelineWidget;
    PreviewWidget* m_previewWidget;

    QString m_currentProjectPath;
};

} // namespace UI
} // namespace NovaCut

#endif // NOVACUT_UI_MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include "trafficlightwidget.h"
#include "scripteditor.h"
#include "trafficlight.h"
#include "kernel.h"
#include <QToolBar>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow(){}

    Kernel *kernel();

public Q_SLOTS:
    void disableStopAction();
    void enableStopAction();

signals:
    void transition();

private:
    void setupWidgets();
    void setupActions();


private Q_SLOTS: // script execution
    void executeScript();
    void stopScript();

private:
    QSplitter *m_hSplitter;
    QSplitter *m_vSplitter;

    QToolBar *m_scriptToolbar;

    ScriptEditor *m_scriptEditor;
    TrafficLight *m_trafficLight;

    QAction *m_runScript;
    QAction *m_stopScript;

    Kernel *m_kernel;
};

#endif // MAINWINDOW_H

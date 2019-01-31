#include "mainwindow.h"
#include <QHBoxLayout>
#include <QDebug>


MainWindow::MainWindow() : QMainWindow(),
    m_kernel(new Kernel())

{
    m_scriptEditor = new ScriptEditor(this);
    m_trafficLight = new TrafficLight(this);
    setObjectName("Semáforo controlado por Script Lua");
    setupWidgets();
    setupActions();
    qDebug() << (m_kernel?"Good":"Bad");


}

void MainWindow::setupWidgets(){

    m_scriptToolbar = new QToolBar();
    m_scriptToolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_scriptToolbar->setOrientation(Qt::Horizontal);
    m_runScript = new QAction(QIcon::fromTheme("media-playback-start"), tr("Run"), this);
    m_runScript->setToolTip("Execute currently active script on active graph document.");
    m_stopScript = new QAction(QIcon::fromTheme("process-stop"), tr("Stop"), this);
    m_stopScript->setToolTip("Stop script execution.");
    m_stopScript->setEnabled(false);
    m_scriptToolbar->addAction(m_runScript);
    m_scriptToolbar->addAction(m_stopScript);
    addAction(m_runScript);
    addAction(m_stopScript);

    connect(m_runScript, &QAction::triggered, this, &MainWindow::executeScript);
    connect(m_stopScript, &QAction::triggered, this, &MainWindow::stopScript);


    m_vSplitter = new QSplitter(this);
    m_vSplitter->setOrientation(Qt::Vertical);
    m_vSplitter->addWidget(m_scriptToolbar);
    m_vSplitter->addWidget(m_scriptEditor);

    m_vSplitter->setSizes(QList<int>() << 40 << 440);

    m_hSplitter = new QSplitter(this);
    m_hSplitter->setOrientation(Qt::Horizontal);
    m_hSplitter->addWidget(m_trafficLight);
    m_hSplitter->addWidget(m_vSplitter);

    m_hSplitter->setSizes(QList<int>() << 280 << 400);

    setCentralWidget(m_hSplitter);
}

void MainWindow::setupActions(){}

void MainWindow::executeScript()
{
    /*if (m_outputWidget->isOutputClearEnabled()) {
        m_outputWidget->clear();
    }*/
    QString script = m_scriptEditor->toPlainText();
    qDebug() << script;
    enableStopAction();
    m_kernel->execute(m_trafficLight, script);
}

void MainWindow::stopScript()
{
    m_kernel->stop();
    disableStopAction();
}


void MainWindow::enableStopAction()
{
    m_stopScript->setEnabled(true);
}

void MainWindow::disableStopAction()
{
    m_stopScript->setEnabled(false);
}

Kernel* MainWindow::kernel(){
    return m_kernel;
}

#include <QGridLayout>

#include "mainwindow.h"
//#include "osdefines.h"
#include "ui_mainwindow.h"
#include "workspaceview.h"
#include <fstream>

using namespace TempDataService;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , inner(QWidget())
    , workspaceView(WorkspaceView(&sessionData))
    , menuBar(MenuBar(&sessionData))
    , pageEditView(PageEditView(&sessionData))
    , notebook()
    , sessionData(SessionDataManager())
{
    // 1. Fetch the system configs data
    sessionData.loadSystemData();

    // current notebook location = sessionData.notebook location
    // 2. Fetch the most recent notebook configs, or use defaults
    // 3. Initialize UI based on session data params
    // 4. Load plugins
    // 5. Load most recent page(s)
    // 6. Publish to screen
    setCentralWidget(&inner);
    setWindowTitle("Calliope Dev");

    QGridLayout gridLayout;
    configureChildren(gridLayout);

    // Fetch temp data
    loadUserData();

    // Restore back to where we left off!
    initialize();

    // Demo stuff
//    ui->testTextEdit->setText("Hello world!");
}

MainWindow::~MainWindow()
{

}

void MainWindow::configureChildren(QLayout& gridLayout)
{
    // Individual configures
    workspaceView.configure();
    menuBar.configure();
    workspaceView.configure();
    pageEditView.configure();

    // Add to main widget
//    gridLayout.addWidget(&menuBar);
//    gridLayout.addWidget(&workspaceView);
    gridLayout.addWidget(&pageEditView);

    inner.setLayout(&gridLayout);
}

void MainWindow::initialize()
{
    // Create Notebook object

}

void MainWindow::loadUserData()
{
    sessionData.loadSystemData();
    if(sessionData.autoLoadLastNotebook)
    {
        sessionData.loadNotebookData();
    }

    // Fetch the last user pages
    sessionData.getLastViewedPages(lastActivePages);

    // Restore the last user page(s)
//    pageEditView.setPlainText(QString(lastActivePages[0]->getData().c_str()));
}

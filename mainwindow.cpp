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
    , sessionData(SessionDataManager())
{
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

}

void MainWindow::loadUserData()
{
    sessionData.loadUserData();

    // Fetch the last user pages
    sessionData.getLastViewedPages(lastActivePages);
}

#include <QGridLayout>

#include "mainwindow.h"
//#include "osdefines.h"
#include "ui_mainwindow.h"
#include "workspaceview.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , inner(QWidget())
    , workspaceView(WorkspaceView(&SessionData))
    , menuBar(MenuBar(&SessionData))
    , pageEditView(PageEditView(&SessionData))
    , ui(new Ui::MainWindow)
    , SessionData(SessionDataManager())
{
    ui->setupUi(this);

    QGridLayout gridLayout;
    ConfigureChildren(gridLayout);

    // Fetch temp data
    LoadUserData();

    // Restore back to where we left off!
//    Initialize();

    // Demo stuff
    ui->testTextEdit->setText("Hello world!");
    setCentralWidget(&inner);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConfigureChildren(QLayout& gridLayout)
{
    // Individual configures
    workspaceView.configure();
    menuBar.configure();
    workspaceView.configure();
    pageEditView.configure();

    // Add to main widget
    gridLayout.addWidget(&menuBar);
    gridLayout.addWidget(&workspaceView);
    gridLayout.addWidget(&pageEditView);

    inner.setLayout(&gridLayout);
}

void MainWindow::LoadUserData()
{
    std::filesystem::path sessionDataFile = GetTempDataFileName();
    std::fstream f(sessionDataFile, std::ios_base::in);

}

#include <QGridLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workspaceview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , inner(QWidget())
    , workspaceView(WorkspaceView())
    , menuBar(MenuBar())
    , pageEditView(PageEditView())
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ConfigureChildren();

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->addWidget(&menuBar);
    gridLayout->addWidget(&workspaceView);
    gridLayout->addWidget(&pageEditView);

    inner.setLayout(gridLayout);

    setCentralWidget(&inner);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConfigureChildren()
{
    workspaceView.configure();
    menuBar.configure();
    workspaceView.configure();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "menubar.h"
#include "pageeditview.h"
#include "workspaceview.h"
#include <QMainWindow>

using namespace TempDataService;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ConfigureChildren(QLayout& gridLayout);
    void Initialize();
    void LoadUserData();

    QWidget inner;
    WorkspaceView workspaceView;
    MenuBar menuBar;
    PageEditView pageEditView;

private:
    const SessionDataManager SessionData;
};
#endif // MAINWINDOW_H

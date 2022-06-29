#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "notebook.h"
#include "menubar.h"
#include "pages.h"
#include "pageeditview.h"
#include "workspaceview.h"
#include <QMainWindow>
#include <QString>

using namespace TempDataService;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void configureChildren(QLayout& gridLayout);
    void initialize();
    void loadUserData();

    QWidget inner;
    WorkspaceView workspaceView;
    MenuBar menuBar;
    PageEditView pageEditView;

private:
    Notebook notebook;
    PagePtrList lastActivePages;
    PagePtrList loadedPages;
    SessionDataManager sessionData;
};
#endif // MAINWINDOW_H

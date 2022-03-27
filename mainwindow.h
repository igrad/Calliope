#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "workspaceview.h"
#include "menubar.h"
#include "pageeditview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

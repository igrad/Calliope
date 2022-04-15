#include "workspaceview.h"
#include <QFileSystemModel>
#include <QHBoxLayout>

WorkspaceView::WorkspaceView(const SessionDataManager* sessionData, QWidget* parent)
    : QWidget(parent)
    , SessionData(sessionData)
{
    QFileSystemModel viewer(this);
}

void WorkspaceView::configure()
{
    QPushButton btn;
    btn.setText("Hey it's me I'm a button wowie");

    QHBoxLayout l;
    l.addWidget(&btn);
    setLayout(&l);
}

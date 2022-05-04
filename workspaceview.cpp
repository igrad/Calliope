#include "workspaceview.h"
#include <QFileSystemModel>
#include <QHBoxLayout>

WorkspaceView::WorkspaceView(const SessionDataManager* currentSessionData, QWidget* parent)
    : QWidget(parent)
    , sessionData(currentSessionData)
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

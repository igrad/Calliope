#include <QFileSystemModel>
#include "workspaceview.h"

WorkspaceView::WorkspaceView(QWidget* parent):
    QWidget(parent)
{
    QFileSystemModel viewer(this);
}

void WorkspaceView::configure()
{

}

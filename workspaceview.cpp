#include <QFileSystemModel>
#include "workspaceview.h"

WorkspaceView::WorkspaceView(const SessionDataManager* sessionData, QWidget* parent)
    : QWidget(parent)
    , SessionData(sessionData)
{
    QFileSystemModel viewer(this);
}

void WorkspaceView::configure()
{

}

#ifndef WORKSPACEVIEW_H
#define WORKSPACEVIEW_H

#include "sessiondatamanager.h"
#include <QWidget>

using namespace TempDataService;

class WorkspaceView : public QWidget
{
    Q_OBJECT

public:
    explicit WorkspaceView(const SessionDataManager* SessionData, QWidget* parent = NULL);

    void configure();

signals:
public slots:

private:
    const SessionDataManager* SessionData;
};

#endif // WORKSPACEVIEW_H

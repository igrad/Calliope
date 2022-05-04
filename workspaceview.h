#ifndef WORKSPACEVIEW_H
#define WORKSPACEVIEW_H

#include "sessiondatamanager.h"
#include <QWidget>
#include <QPushButton>

using namespace TempDataService;

class WorkspaceView : public QWidget
{
    Q_OBJECT

public:
    explicit WorkspaceView(const SessionDataManager* currentSessionData, QWidget* parent = NULL);

    void configure();

signals:
public slots:

private:
    const SessionDataManager* sessionData;
};

#endif // WORKSPACEVIEW_H

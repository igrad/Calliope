#ifndef WORKSPACEVIEW_H
#define WORKSPACEVIEW_H

#include <QWidget>

class WorkspaceView : public QWidget
{
    Q_OBJECT

public:
    explicit WorkspaceView(QWidget* parent = NULL);

    void configure();

signals:
public slots:
};

#endif // WORKSPACEVIEW_H

#ifndef MENUBAR_H
#define MENUBAR_H

#include "sessiondatamanager.h"
#include <QWidget>
#include <QPushButton>

using namespace TempDataService;

class MenuBar : public QWidget
{
    Q_OBJECT
public:
    explicit MenuBar(const SessionDataManager* sessionData, QWidget *parent = nullptr);

    void configure();

private:
    QPushButton btn1;
    const SessionDataManager* SessionData;
signals:
};

#endif // MENUBAR_H

#ifndef PAGEEDITVIEW_H
#define PAGEEDITVIEW_H

#include "sessiondatamanager.h"
#include <QPlainTextEdit>

using namespace TempDataService;

class PageEditView : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit PageEditView(const SessionDataManager* loadedSessionData, QWidget *parent = nullptr);

    void configure();

signals:

private:
    const SessionDataManager* sessionData;
};

#endif // PAGEEDITVIEW_H

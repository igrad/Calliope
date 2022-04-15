#ifndef PAGEEDITVIEW_H
#define PAGEEDITVIEW_H

#include "sessiondatamanager.h"
#include <QPlainTextEdit>

using namespace TempDataService;

class PageEditView : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit PageEditView(const SessionDataManager* sessionData, QWidget *parent = nullptr);

    void configure();

signals:

private:
    const SessionDataManager* SessionData;
};

#endif // PAGEEDITVIEW_H

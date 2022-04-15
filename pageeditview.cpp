#include "pageeditview.h"

PageEditView::PageEditView(const SessionDataManager* sessionData, QWidget *parent)
    : QPlainTextEdit(parent)
    , SessionData(sessionData)
{

}

void PageEditView::configure()
{
    setPlainText(QString("Lorem ipsum"));
}

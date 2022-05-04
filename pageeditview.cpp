#include "pageeditview.h"

PageEditView::PageEditView(const SessionDataManager* loadedSessionData, QWidget *parent)
    : QPlainTextEdit(parent)
    , sessionData(loadedSessionData)
{

}

void PageEditView::configure()
{
    setPlainText(QString("Lorem ipsum"));
}

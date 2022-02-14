#ifndef PAGEEDITVIEW_H
#define PAGEEDITVIEW_H

#include <QWidget>

class PageEditView : public QWidget
{
    Q_OBJECT
public:
    explicit PageEditView(QWidget *parent = nullptr);

    void configure();

signals:

};

#endif // PAGEEDITVIEW_H

#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include <QPushButton>

class MenuBar : public QWidget
{
    Q_OBJECT
public:
    explicit MenuBar(QWidget *parent = nullptr);

    void configure();

private:
    QPushButton btn1;
signals:
};

#endif // MENUBAR_H

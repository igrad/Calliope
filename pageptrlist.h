#ifndef PAGEPTRLIST_H
#define PAGEPTRLIST_H

#include <QUuid>
#include <QVector>

class Page;
typedef QVector<Page*> PagePtrVector;

class PagePtrList
{
public:
    PagePtrList();

    void addPage(Page* page);
    Page* getPage(const QUuid& pageIdentifier);
    void removePage(const QUuid& pageIdentifier);

    Page* operator[](int index);

private:
    PagePtrVector vector;
};

#endif // PAGEPTRLIST_H

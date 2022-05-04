#include "pageptrlist.h"
#include "page.h"

PagePtrList::PagePtrList()
{

}

void PagePtrList::addPage(Page* page)
{
    vector.emplaceBack(page);
}

Page* PagePtrList::getPage(const QUuid &pageIdentifier)
{
    PagePtrVector::iterator p = std::find_if(vector.begin(), vector.end(), [&](Page* page){
        return page->getIdentifier() == pageIdentifier;
    });
    return p == vector.end() ? nullptr : *p;
}

void PagePtrList::removePage(const QUuid &pageIdentifier)
{
    vector.removeIf([&](Page* page){
        return pageIdentifier == page->getIdentifier();
    });
}

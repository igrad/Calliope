#include "folder.h"
#include "page.h"

Folder FolderRootFolder();

Folder::Folder():
    identifier(QUuid()),
    displayName(""),
    parent(nullptr)
{

}

Folder::Folder(QUuid identifier,
               const QString displayName,
               Folder* parent):
    identifier(identifier),
    displayName(displayName),
    parent(parent)
{

}

const QUuid& Folder::getIdentifier() const
{
    return identifier;
}

QString Folder::getDisplayName() const
{
    return displayName;
}

int Folder::getPageCount() const
{
    return pages.size();
}

int Folder::getFolderCount() const
{
    return folders.size();
}

int Folder::getItemCount() const
{
    return getPageCount() + getFolderCount();
}

Folder* Folder::getParent() const
{
    return parent;
}

std::string Folder::getRelativePathString() const
{
    if(parent)
    {
        return parent->getRelativePathString() + "/" + path.filename().generic_string();
    }
    else
    {
        return "/";
    }
}

bool Folder::contains(const QUuid& identifier) const
{
    return pages.find(identifier) != pages.end();
}

bool Folder::contains(Page &page) const
{
    return contains(page.getIdentifier());
}

bool Folder::contains(Folder &folder) const
{
    return contains(folder.getIdentifier());
}

bool Folder::add(Page* page)
{
    if(not contains(*page))
    {
        pages.insert({page->getIdentifier(), page});
        return true;
    }

    return false;
}

bool Folder::add(Folder* folder)
{
    if(not contains(*folder))
    {
        folders.insert({folder->getIdentifier(), folder});
        return true;
    }

    return false;
}

void Folder::remove(Page* page)
{
    if(contains(*page))
    {
        pages.erase(page->getIdentifier());
    }
}

void Folder::remove(Folder* folder)
{
    if(contains(*folder))
    {
        folders.erase(folder->getIdentifier());
    }
}

void Folder::ReassignChildrenRefsToParent()
{
    std::map<QUuid, Folder*>::iterator iter = folders.begin();
    do
    {
        iter->second->parent = this;
    } while(iter++ != folders.end());
}

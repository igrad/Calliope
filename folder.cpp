#include "folder.h"

Folder FolderRootFolder();

Folder::Folder(QUuid identifier,
               std::string displayName,
               Folder* parent):
    _identifier(identifier),
    _displayName(displayName),
    _parent(parent)
{
    _ancestry = *(parent->GetAncestry());
    _ancestry.push_back(parent);
}

const QUuid& Folder::GetIdentifier() const
{
    return _identifier;
}

int Folder::GetPageCount()
{
    return _pages.size();
}

int Folder::GetFolderCount()
{
    return _folders.size();
}

int Folder::GetItemCount()
{
    return GetPageCount() + GetFolderCount();
}

Folder* Folder::GetParent()
{
    return _ancestry.back();
}

std::vector<Folder*>* Folder::GetAncestry()
{
    return &_ancestry;
}

std::string Folder::GetRelativePathString()
{
    if(_ancestry.size() > 0)
    {
        return _ancestry.back()->GetRelativePathString() + "/" + _path.filename().generic_string();
    }
    else
    {
        return "";
    }
}

bool Folder::Contains(const QUuid& identifier)
{
    return _pages.find(identifier) != _pages.end();
}

bool Folder::Contains(Page &page)
{
    return Contains(page.GetIdentifier());
}

bool Folder::Contains(Folder &folder)
{
    return Contains(folder.GetIdentifier());
}

bool Folder::Add(Page* page)
{
    if(not Contains(*page))
    {
        _pages.insert({page->GetIdentifier(), page});
        return true;
    }

    return false;
}

bool Folder::Add(Folder* folder)
{
    if(not Contains(*folder))
    {
        _folders.insert({folder->GetIdentifier(), folder});
        return true;
    }

    return false;
}

void Folder::Remove(Page* page)
{
    if(Contains(*page))
    {
        _pages.erase(page->GetIdentifier());
    }
}

void Folder::Remove(Folder* folder)
{
    if(Contains(*folder))
    {
        _folders.erase(folder->GetIdentifier());
    }
}

#include "folderptrlist.h"
#include "folder.h"

FolderPtrList::FolderPtrList()
{

}

Folder* FolderPtrList::getFolder(const QUuid& identifier)
{
    FolderPtrVector::iterator f = std::find_if(vector.begin(), vector.end(), [&](Folder* folder){
            return folder->getIdentifier() == identifier;
        });
    return f == vector.end() ? nullptr : *f;
}

void FolderPtrList::removeFolder(const QUuid& identifier)
{
    vector.removeIf([&](Folder* f){
       return f->getIdentifier() == identifier;
    });
}

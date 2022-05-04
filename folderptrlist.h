#ifndef FOLDERPTRLIST_H
#define FOLDERPTRLIST_H

#include <QUuid>
#include <QVector>

class Folder;

typedef QVector<Folder*> FolderPtrVector;

class FolderPtrList
{
public:
    FolderPtrList();

    Folder* getFolder(const QUuid& identifier);
    void removeFolder(const QUuid& identifier);

private:
    FolderPtrVector vector;
};

#endif // FOLDERPTRLIST_H

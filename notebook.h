#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include "folder.h"
#include <QUuid>

class Notebook: public Folder
{
public:
    Notebook(QUuid identifier,
             const QString displayName,
             Folder* parent);

    void addFolder(const Folder &folder);
    void addPage(const Page &page);

private:
    FolderPtrVector folders;
    PagePtrVector pages;

    QString displayName;
    QUuid identifier;

    std::filesystem::path dataFilePath;
};

#endif // NOTEBOOK_H

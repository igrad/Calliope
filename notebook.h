#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include "folder.h"


class Notebook: public Folder
{
public:
    Notebook(const std::string identifier,
             const std::string displayName,
             Folder* parent);

    void AddFolder(const Folder &folder);
    void AddPage(const Page &page);

private:
    std::vector<Folder*> _folders;
    std::vector<Page*> _pages;

    std::string _displayName;
    std::string _identifier;

    std::string _dataFilePath;
};

#endif // NOTEBOOK_H

#ifndef FOLDER_H
#define FOLDER_H

#include <map>
#include "page.h"
#include <QUuid>
#include <string>
#include <vector>

// Filesystem (and other classes that use filesystem) is put last due to a Qt bug.
// See https://bugreports.qt.io/browse/QTBUG-73263
#include <filesystem>

class Page;


class Folder
{
public:
    Folder(QUuid identifier,
           std::string displayName,
           Folder* parent = nullptr);

    const QUuid& GetIdentifier() const;
    int GetPageCount();
    int GetFolderCount();
    int GetItemCount();
    Folder* GetParent();
    std::vector<Folder*>* GetAncestry();
    std::string GetRelativePathString();

    bool Contains(Page &page);
    bool Contains(const QUuid& identifier);
    bool Contains(Folder &folder);

    bool Add(Page* page);
    bool Add(Folder* folder);

    void Remove(Page* page);
    void Remove(Folder* folder);

    static Folder RootFolder;

protected:
    QUuid _identifier;
    std::string _displayName;
    std::filesystem::path _path;
    std::vector<Folder*> _ancestry;
    Folder* _parent;
    std::map<QUuid, Folder*> _folders;
    std::map<QUuid, Page*> _pages;
};


struct DetachedFolder : public std::exception
{
    DetachedFolder(const std::string msg)
    {
        _msg = "Folder \"" + msg + "\" does not have a parent";
    }

    const char* what() const throw()
    {
        return _msg.c_str();
    }

    std::string _msg;
};

#endif // FOLDER_H

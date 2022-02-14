#ifndef FOLDER_H
#define FOLDER_H

#include "page.h"

class Page;


class Folder
{
public:
    Folder(std::string displayName,
           std::string identifier,
           Folder* parent = nullptr);

    std::string GetIdentifier() const;
    int GetPageCount();
    int GetFolderCount();
    int GetItemCount();
    Folder* GetParent();
    std::vector<Folder*>* GetAncestry();
    std::string GetRelativePathString();

    bool Contains(Page &page);
    bool Contains(const std::string identifier);
    bool Contains(Folder &folder);

    bool Add(Page* page);
    bool Add(Folder* folder);

    void Remove(Page* page);
    void Remove(Folder* folder);

    static Folder RootFolder;

protected:
    std::string _identifier;
    std::string _displayName;
    std::filesystem::path _path;
    std::vector<Folder*> _ancestry;
    Folder* _parent;
    std::map<std::string, Folder*> _folders;
    std::map<std::string, Page*> _pages;
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

#ifndef FOLDER_H
#define FOLDER_H

#include "pages.h"
#include "folders.h"
#include <map>
#include <QUuid>
#include <QObject>
#include <string>
#include <vector>

// Filesystem (and other classes that use filesystem) is put last due to a Qt bug.
// See https://bugreports.qt.io/browse/QTBUG-73263
#include <filesystem>

class Page;

class Folder: public QObject
{
    Q_OBJECT

public:
    Folder();
    Folder(QUuid newIdentifier,
           const QString newDisplayName,
           Folder* newParent = nullptr);

    const QUuid& getIdentifier() const;
    QString getDisplayName() const;
    int getPageCount() const;
    int getFolderCount() const;
    int getItemCount() const;
    Folder* getParent() const;
    std::string getRelativePathString() const;

    bool contains(Page &page) const;
    bool contains(const QUuid& identifier) const;
    bool contains(Folder &folder) const;

    bool add(Page* page);
    bool add(Folder* folder);

    void remove(Page* page);
    void remove(Folder* folder);

    static Folder RootFolder;

protected:
    QUuid identifier;
    QString displayName;
    std::filesystem::path path;
    Folder* parent;
    std::map<QUuid, Folder*> folders;
    std::map<QUuid, Page*> pages;

private:
    void ReassignChildrenRefsToParent();
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

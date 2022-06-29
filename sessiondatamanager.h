#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include "page.h"
#include "pages.h"
#include "osdefines.h"
#include <QObject>
#include <QDebug>

namespace TempDataService
{
    // Add most recent notebook here.
    // Minor note, we'll need a system-wide session data file to maintain a few things, and a notebook session file to keep this stuff
    // System temp data:
    // - Most recent Notebook
    // - List of managed Notebooks
    // - Theme preferences
    // -
    enum class SaveVarKey
    {
        UNKNOWN = 0,
        COMMENT,
        CONTINUATION,
        LAST_LOGIN,
        FONT_SIZE,
        ZOOM,
        ACTIVE_PAGES,
        AUTO_LOAD_LAST_NOTEBOOK,
        LAST_VIEWED_PAGES,
        LAST_NOTEBOOK,
        MANAGED_NOTEBOOKS,
        THEME
    };

    // If this does not directly match the names of the SaveVarKey enum values,
    // the world will explode
    const std::map<std::string, SaveVarKey> SaveVarNames = {
        {"UNKNOWN", SaveVarKey::UNKNOWN},
        {"COMMENT", SaveVarKey::COMMENT},
        {"CONTINUATION", SaveVarKey::CONTINUATION},
        {"LAST_LOGIN", SaveVarKey::LAST_LOGIN},
        {"FONT_SIZE", SaveVarKey::FONT_SIZE},
        {"ZOOM", SaveVarKey::ZOOM},
        {"ACTIVE_PAGES", SaveVarKey::ACTIVE_PAGES},
        {"AUTO_LOAD_LAST_NOTEBOOK", SaveVarKey::AUTO_LOAD_LAST_NOTEBOOK},
        {"LAST_VIEWED_PAGES", SaveVarKey::LAST_VIEWED_PAGES},
        {"LAST_NOTEBOOK", SaveVarKey::THEME},
        {"MANAGED_NOTEBOOKS", SaveVarKey::LAST_NOTEBOOK},
        {"THEME", SaveVarKey::MANAGED_NOTEBOOKS},
    };


    class SessionDataManager : public QObject
    {
        Q_OBJECT
    public:
        explicit SessionDataManager();

        void loadSystemData();
        void saveSystemData();
        void loadNotebookData();
        void saveNotebookData();

        std::string getStrVar(SaveVarKey key);
        void setStrVar(SaveVarKey key, std::string value);

        void getLastActivePages(PagePtrList& pageList);
        void getLastViewedPages(PagePtrList& pageList);
        void getPreviousNotebooks(FolderPtrList& folderList);

        bool autoLoadLastNotebook;

    signals:
        void systemDataLoaded();
        void systemDataSaved();
        void userDataLoaded();
        void userDataSaved();

    private:
        std::string _get(SaveVarKey key);
        void _set(SaveVarKey key, std::string value);

        std::map<SaveVarKey, std::string> cachedStringVars;
        std::vector<std::string> cachedActivePages;
        std::vector<std::string> cachedViewedPages;
        std::vector<std::string> cachedPreviousNotebooks;
        std::filesystem::path systemConfigFilePath;
        std::filesystem::path activeNotebookFilePath;
    };
}

#endif // SESSIONDATA_H

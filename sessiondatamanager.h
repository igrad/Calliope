#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include "page.h"
#include "pages.h"
#include "osdefines.h"
#include <QObject>

namespace TempDataService
{
    enum class SaveVarKey
    {
        UNKNOWN = 0,
        COMMENT,
        CONTINUATION,
        LAST_LOGIN,
        FONT_SIZE,
        ZOOM,
        ACTIVE_PAGES,
        LAST_VIEWED_PAGES,
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
        {"LAST_VIEWED_PAGES", SaveVarKey::LAST_VIEWED_PAGES},
    };


    class SessionDataManager : public QObject
    {
        Q_OBJECT
    public:
        explicit SessionDataManager();

        void loadUserData();
        void saveUserData();

        template <class ValType>
        ValType getVar(SaveVarKey key);
        template <class ValType>
        void setVar(SaveVarKey key, ValType value);

        void getLastViewedPages(PagePtrList& pageList);

    signals:
        void userDataLoaded();
        void userDataSaved();

    private:
        std::string _get(SaveVarKey key);
        void _set(SaveVarKey key, std::string value);

        std::map<SaveVarKey, std::string> cachedStringVars;
        std::vector<std::string> cachedActivePages;
        std::vector<std::string> cachedViewedPages;
    };
}

#endif // SESSIONDATA_H

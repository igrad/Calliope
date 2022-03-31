#ifndef SESSIONDATA_H
#define SESSIONDATA_H

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
        LAST_OPEN_PAGES,
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
        {"LAST_OPEN_PAGES", SaveVarKey::LAST_OPEN_PAGES},
    };


    class SessionDataManager : public QObject
    {
        Q_OBJECT
    public:
        explicit SessionDataManager();

        void LoadUserData();
        void SaveUserData();

        template <class ValType>
        ValType GetVar(SaveVarKey key);
        template <class ValType>
        void SetVar(SaveVarKey key, ValType value);

    signals:
        void UserDataLoaded();
        void UserDataSaved();

    private:
        std::string _Get(SaveVarKey key);
        void _Set(SaveVarKey key, std::string value);

        std::map<SaveVarKey, std::string> cachedStringVars;
        std::vector<std::string> cachedActivePages;
        std::vector<std::string> cachedOpenPages;
    };
}

#endif // SESSIONDATA_H

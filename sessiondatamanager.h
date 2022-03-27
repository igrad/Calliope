#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <string>
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

        static void LoadUserData();
        static void SaveUserData();

        template <class ValType>
        static ValType GetVar(SaveVarKey key);
        template <class ValType>
        static void SetVar(SaveVarKey key, ValType value);

    signals:
        static void UserDataLoaded();
        static void UserDataSaved();

    private:
        static std::string _Get(SaveVarKey key);
        static void _Set(SaveVarKey key, std::string value);

        static std::map<SaveVarKey, std::string> cachedStringVars;
        static std::vector<std::string> cachedActivePages;
        static std::vector<std::string> cachedOpenPages;
    };
}

#endif // SESSIONDATA_H

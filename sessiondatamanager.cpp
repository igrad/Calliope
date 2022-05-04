#include "sessiondatamanager.h"

#include <fstream>


using namespace TempDataService;

namespace
{
    std::pair<SaveVarKey, std::string> attemptParse(std::string line)
    {
        SaveVarKey key;
        std::string val = "";

        if(val.substr(0, 2) == "//")
        {
            // If a line starts with "//", it's a comment, which shouldn't
            // even be needed.
            key = SaveVarKey::COMMENT;
            val = line.substr(4);
        }
        else if(val.substr(0, 1) == "\t" ||
                val.substr(0, 1) == " ")
        {
            // If a line starts with an indent, it's a continuation of the
            // previous line.
            key = SaveVarKey::CONTINUATION;
            int valueStart = 1 + line.find_first_of('=');
            int valueEnd = line.find_first_of('\n');
            val = line.substr(valueStart, (valueEnd - valueStart));
        }
        else
        {
            // If not a comment or continuation, it should be a predictable
            // value to be parsed.
            int eqPos = line.find_first_of('=');
            std::string rawKey = line.substr(0, eqPos);
            if(SaveVarNames.find(rawKey) != SaveVarNames.end())
            {
                key = (SaveVarNames.find(rawKey))->second;
                val = line.substr(eqPos + 1);
            }
            else
            {
                key = SaveVarKey::UNKNOWN;
                // TODO: Log an error message here
            }
        }

        return std::pair(key, val);
    }
}


SessionDataManager::SessionDataManager()
    : QObject{nullptr}
{

}

void SessionDataManager::loadUserData()
{
    cachedStringVars.clear();
    cachedActivePages.clear();
    cachedViewedPages.clear();

    std::filesystem::path sessionDataFile = getTempDataFileName();
    std::fstream inFile(sessionDataFile, std::ios_base::in);
    std::string buf;

    SaveVarKey lastKey = SaveVarKey::UNKNOWN;
    while(getline(inFile, buf))
    {
        SaveVarKey key;
        std::string val;

        std::pair(key,val) = attemptParse(buf);

        switch(key)
        {
        case SaveVarKey::UNKNOWN: {
            // TODO: Does any error handling need to be done here?
            break;
        }
        case SaveVarKey::COMMENT: {
            // Nothing needs to be done!
            break;
        }
        case SaveVarKey::CONTINUATION: {
            // internal switch
            if(lastKey == SaveVarKey::ACTIVE_PAGES)
            {
                // Handle continuation of last active pages
                cachedActivePages.push_back(val);
            }
            else if(lastKey == SaveVarKey::LAST_VIEWED_PAGES)
            {
                // Handle continuation of last open pages
                cachedViewedPages.push_back(val);
            }

            break;
        }
        case SaveVarKey::LAST_LOGIN: {
            cachedStringVars[key] = val;
            lastKey = key;
            break;
        }
        case SaveVarKey::FONT_SIZE: {
            cachedStringVars[key] = val;
            lastKey = key;
            break;
        }
        case SaveVarKey::ZOOM: {
            cachedStringVars[key] = val;
            lastKey = key;
            break;
        }
        case SaveVarKey::ACTIVE_PAGES: {
            cachedActivePages.push_back(val);
            lastKey = key;
            break;
        }
        case SaveVarKey::LAST_VIEWED_PAGES: {
            cachedViewedPages.push_back(val);
            lastKey = key;
            break;
        }
        }
    }

}

void SessionDataManager::saveUserData()
{

}

template <class ValType>
ValType SessionDataManager::getVar(SaveVarKey key)
{
    try
    {
        static_cast<ValType>(_get(key));
    }
    catch (...)
    {
        // TODO: What exception does this throw?
    }
}

template <class ValType>
void SessionDataManager::setVar(SaveVarKey key, ValType value)
{
    try
    {
        _set(key, static_cast<std::string>(value));
    }
    catch (...)
    {
        // TODO: What exception does this throw?
    }
}

void SessionDataManager::getLastViewedPages(PagePtrList& pageList)
{
    for(std::string pageStr : cachedViewedPages)
    {
        // Create record
        // Create Page ptr
        // Add page ptr to the pageList
        pageList.addPage(nullptr);
    }
}

std::string SessionDataManager::_get(SaveVarKey key)
{
    return cachedStringVars[key];
}

void SessionDataManager::_set(SaveVarKey key, std::string value)
{
    cachedStringVars[key] = value;
}

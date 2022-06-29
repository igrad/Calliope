#include "sessiondatamanager.h"
#include <Helpers/fileoperationshelper.h>

#include <fstream>
#include <stdio.h>
#include <string.h>


using namespace TempDataService;

namespace
{
    std::pair<SaveVarKey, std::string> attemptParse(std::string line)
    {
        SaveVarKey key;
        std::string val = "";

        if(val.compare(0, 2, "//") == 0)
        {
            // If a line starts with "//", it's a comment, which shouldn't
            // even be needed.
            key = SaveVarKey::COMMENT;
            val = line.substr(4);
        }
        else if(val.compare(0, 1, "\t") == 0 ||
                val.compare(0, 1, " "))
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

    std::string toLower(std::string s)
    {
        for(std::string::size_type iter = 0; iter < s.length(); ++iter)
        {
            s[iter] = std::tolower(s[iter]);
        }

        return s;
    }

    bool strEq(std::string l, std::string r)
    {
        return !std::strcmp(toLower(l).c_str(), toLower(r).c_str());
    }
}


SessionDataManager::SessionDataManager()
    : QObject{nullptr}
{

}

void SessionDataManager::loadSystemData()
{
    cachedStringVars.clear();
    cachedActivePages.clear();
    cachedViewedPages.clear();

    systemConfigFilePath = getGlobalConfigFileName();
    std::fstream inFile(systemConfigFilePath, std::ios_base::in);
    std::string buf;

    SaveVarKey lastKey = SaveVarKey::UNKNOWN;
    while(getline(inFile, buf))
    {
        SaveVarKey key;
        std::string val;

        std::pair(key,val) = attemptParse(buf);

        switch(key)
        {
        case SaveVarKey::LAST_NOTEBOOK: {
            // Attempt to create a path to the specified notebook config file
            std::filesystem::path notebookPath(val);
            if(isFilePathValid(notebookPath))
            {
                activeNotebookFilePath = notebookPath;
            }
            break;
        }
        case SaveVarKey::AUTO_LOAD_LAST_NOTEBOOK: {
            cachedStringVars[key] = val;
            autoLoadLastNotebook = strEq(val, "true");
            break;
        }
        case SaveVarKey::THEME: {
            cachedStringVars[key] = val;
            break;
        }
        case SaveVarKey::MANAGED_NOTEBOOKS: {
            cachedPreviousNotebooks.push_back(val);
            break;
        }
        case SaveVarKey::CONTINUATION: {
            if(lastKey == SaveVarKey::MANAGED_NOTEBOOKS)
            {
                cachedPreviousNotebooks.push_back(val);
            }
            break;
        }
        default: {
            break;
        }
        }
        lastKey = key;
    }
}

void SessionDataManager::saveSystemData()
{

}

void SessionDataManager::loadNotebookData()
{
    std::filesystem::path sessionDataFile = getNotebookConfigFileName();
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
            break;
        }
        case SaveVarKey::FONT_SIZE: {
            cachedStringVars[key] = val;
            break;
        }
        case SaveVarKey::ZOOM: {
            cachedStringVars[key] = val;
            break;
        }
        case SaveVarKey::ACTIVE_PAGES: {
            cachedActivePages.push_back(val);
            break;
        }
        case SaveVarKey::LAST_VIEWED_PAGES: {
            cachedViewedPages.push_back(val);
            break;
        }
        default: {
            break;
        }
        }
        lastKey = key;
    }
}

void SessionDataManager::saveNotebookData()
{

}

std::string SessionDataManager::getStrVar(SaveVarKey key)
{
    return _get(key);
}

void SessionDataManager::setStrVar(SaveVarKey key, std::string value)
{
    _set(key, static_cast<std::string>(value));
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

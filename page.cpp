#include "page.h"


// Static Constants
const std::string Page::NULL_ID = "NULL_IDENTIFIER";
int Page::PAGE_COUNT = 0;
std::map<std::string, std::string> Page::ID_MAP;
const std::string Page::PAGE_FILE_EXTENSION = ".md";


// Constructor Definitions
Page::Page(const std::string identifier,
           Folder* parent)
{
    if(PageRecord::IdentifierIsInUse(identifier))
    {
        throw PageIdentifierInUse(identifier);
    }
    else
    {
        _relativePath = parent->GetRelativePathString();
        FileManager::MakeFileNameValid(_identifier);
        _pageRecord = PageRecord::MakePageRecord(identifier, _relativePath, _fileName);
        _identifier = _pageRecord->identifier;
        _filePath = _pageRecord->filePath;
    }
}

Page::Page(PageRecord* record, Folder* parent)
    : _identifier(record->identifier)
    , _filePath(record->filePath)
    , _pageRecord(record)
{
    _relativePath = parent->GetRelativePathString();
    FileManager::MakeFileNameValid(_identifier);
}


std::string Page::GetIdentifier() const
{
    return _identifier;
}

std::filesystem::path Page::GetFilePath() const
{
    return _filePath;
}

std::string Page::GetData() const
{
    return _pageData;
}

void Page::SetData(const std::string data)
{
    _pageData = data;
}

void Page::_SetIdentifier(const std::string identifier)
{
    // If the identifier is not within the ID_MAP already, it's usable
    if(IsIdentifierValid(identifier))
    {
        _identifier = identifier;

        const std::string path = "";
        ID_MAP[identifier] = path;

        _pageRecord->SetIdentifier(identifier);
    }
}

void Page::_LoadPageContentFromFile()
{

}

void Page::_SavePageContentToFile()
{
    FileManager::SavePageToFile(*this);
}


// Static Methods
bool Page::IsIdentifierValid(const std::string identifier)
{
    return ID_MAP.find(identifier) != ID_MAP.end();
}

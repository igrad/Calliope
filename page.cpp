#include "page.h"


// Static Constants
int Page::PAGE_COUNT = 0;
std::map<QUuid, std::string> Page::ID_MAP;
const std::string Page::PAGE_FILE_EXTENSION = ".md";


// Constructor Definitions
Page::Page(QUuid& identifier,
           std::string fileName,
           Folder* parent)
    : _identifier(identifier)
    , _fileName(fileName)
{
    if(PageRecord::IdentifierIsInUse(identifier))
    {
        throw PageIdentifierInUse(identifier);
    }
    else
    {
        _relativePath = parent->GetRelativePathString();
        MakePageNameValid(_fileName);
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
    MakePageNameValid(_fileName);
}


const QUuid Page::GetIdentifier() const
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

bool Page::LoadFromFile()
{
    return _LoadPageContentFromFile();
}

bool Page::SaveToFile()
{
    return true;
}

bool Page::DeleteFile()
{
    if(_FileExists())
    {
        return remove(_filePath) != 0;
    }
    else
    {
        qDebug() << "Page::DeleteFile: Cannot delete page file that does not exist!";
        return false;
    }
}

bool Page::_FileExists()
{
    return std::filesystem::exists(_filePath);
}

void Page::_SetIdentifier(const QUuid& identifier)
{
    // If the identifier is not within the ID_MAP already, it's usable
    if(IsIdentifierValid(identifier))
    {
        _identifier = identifier;

        const std::string path = "";
        ID_MAP[identifier] = path;

        _pageRecord->SetIdentifier(_identifier);
    }
}

bool Page::_LoadPageContentFromFile()
{
    std::fstream openFile;
    _isOpen = false;

    try
    {
        openFile.open(_filePath, std::ios::in);

        if(openFile.is_open())
        {
            std::stringstream pageData;
            pageData << openFile.rdbuf();
            SetData(pageData.str());
            openFile.close();

            _isOpen = true;

            return true;
        }
        return false;
    }
    catch (...)
    {
        if(openFile.is_open())
        {
            openFile.close();
        }

        // TODO: Elaborate on this error readout
        std::cout << "Error reading data from file! path: " << _filePath
                  << std::endl;
        return false;
    }
}

bool Page::_SavePageContentToFile()
{
    std::fstream openFile;

    try
    {
        openFile.open(_filePath, std::ios::out);

        if(openFile.is_open())
        {
            openFile << _pageData;
            openFile.close();
        }

        return true;
    }
    catch (...)
    {
        if(openFile.is_open())
        {
            openFile.close();
        }

        // TODO: Elaborate on this error readout
        std::cout << "Error writing data to file! path: " << _filePath << std::endl;
        return false;
    }

    return true;
}


// Static Methods
bool Page::IsIdentifierValid(const QUuid& identifier)
{
    return ID_MAP.find(identifier) != ID_MAP.end();
}

void Page::MakePageNameValid(std::string& fileName)
{
    char forbiddenChars[10] = {'<', '>', ':', ';', '\"', '/', '\\', '|', '?', '*'};
    int numForbiddenChars = 10;

    for(int iter = 0; iter < numForbiddenChars; ++iter)
    {
        char ch = forbiddenChars[iter];
        std::remove_if(fileName.begin(), fileName.end(), [ch](char x){return x == ch;});
    }
}


// Operators
bool Page::operator==(const Page &rhs)
{
    return _identifier == rhs.GetIdentifier();
}

bool Page::operator==(const QUuid &rhs)
{
    return _identifier == rhs;
}

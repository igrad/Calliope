#include "page.h"
#include "folder.h"

// Static Constants
int Page::PAGE_COUNT = 0;
std::map<QUuid, std::string> Page::ID_MAP;
const std::string Page::PAGE_FILE_EXTENSION = ".md";


// Constructor Definitions
Page::Page()
    : identifier(QUuid::createUuid())
    , fileName("")
{
}

Page::Page(QUuid& newIdentifier,
           std::string fileName,
           Folder* parent)
    : identifier(newIdentifier)
    , fileName(fileName)
{
    if(PageRecord::identifierIsInUse(identifier))
    {
        throw PageIdentifierInUse(identifier);
    }
    else
    {
        relativePath = parent->getRelativePathString();
        makePageNameValid(fileName);
        pageRecord = PageRecord::makePageRecord(identifier, relativePath, fileName);
        identifier = pageRecord->identifier;
        filePath = pageRecord->filePath;
    }
}

Page::Page(PageRecord* record, Folder* parent)
    : identifier(record->identifier)
    , filePath(record->filePath)
    , pageRecord(record)
{
    relativePath = parent->getRelativePathString();
    makePageNameValid(fileName);
}


const QUuid Page::getIdentifier() const
{
    return identifier;
}

std::filesystem::path Page::getFilePath() const
{
    return filePath;
}

std::string Page::getData() const
{
    return pageData;
}

PageRecord* Page::getPageRecord() const
{
    return nullptr;
}

bool Page::isOpen() const
{
    return open;
}

void Page::setData(const std::string data)
{
    pageData = data;
}

bool Page::loadFromFile()
{
    return _loadPageContentFromFile();
}

bool Page::saveToFile()
{
    return true;
}

bool Page::deleteFile()
{
    if(_fileExists())
    {
        return remove(filePath) != 0;
    }
    else
    {
        qDebug() << "Page::DeleteFile: Cannot delete page file that does not exist!";
        return false;
    }
}

bool Page::_fileExists()
{
    return std::filesystem::exists(filePath);
}

void Page::_setIdentifier(const QUuid& newIdentifier)
{
    // If the identifier is not within the ID_MAP already, it's usable
    if(isIdentifierValid(identifier))
    {
        identifier = newIdentifier;

        const std::string path = "";
        ID_MAP[identifier] = path;

        pageRecord->setIdentifier(identifier);
    }
}

bool Page::_loadPageContentFromFile()
{
    std::fstream openFile;
    open = false;

    try
    {
        openFile.open(filePath, std::ios::in);

        if(openFile.is_open())
        {
            std::stringstream pageData;
            pageData << openFile.rdbuf();
            setData(pageData.str());
            openFile.close();

            open = true;

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
        std::cout << "Error reading data from file! path: " << filePath
                  << std::endl;
        return false;
    }
}

bool Page::_savePageContentToFile()
{
    std::fstream openFile;

    try
    {
        openFile.open(filePath, std::ios::out);

        if(openFile.is_open())
        {
            openFile << pageData;
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
        std::cout << "Error writing data to file! path: " << filePath << std::endl;
        return false;
    }

    return true;
}


// Static Methods
bool Page::isIdentifierValid(const QUuid& identifier)
{
    return ID_MAP.find(identifier) != ID_MAP.end();
}

void Page::makePageNameValid(std::string& fileName)
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
    return identifier == rhs.getIdentifier();
}

bool Page::operator==(const QUuid &rhs)
{
    return identifier == rhs;
}

void Page::operator=(const Page &rhs)
{
    identifier = rhs.getIdentifier();
    open = rhs.isOpen();
    filePath = rhs.getFilePath();
    fileName = filePath.filename().string();
    pageData = rhs.getData();
    pageRecord = rhs.getPageRecord();
}

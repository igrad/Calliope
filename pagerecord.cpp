#include "pagerecord.h"

#include <algorithm>

std::string PAGERECORDFILEPATH = "";

std::vector<PageRecord> PageRecord::ALL_PAGE_RECORDS;

PageRecord::PageRecord(std::string m_identifier,
                       std::string m_relativePath,
                       std::string m_fileName)
  : identifier(m_identifier)
{
    if(m_identifier == "")
    {
        _GenerateIdentifier();
    }

    filePath = PAGERECORDFILEPATH + m_relativePath + m_fileName;
}

PageRecord::PageRecord(const PageRecord& record)
    : QObject(nullptr)
    , identifier(record.identifier)
    , filePath(record.filePath)
{

}

PageRecord::~PageRecord()
{
    RemoveRecord(this);
}

bool PageRecord::SetIdentifier(std::string m_identifier)
{
    if(!IdentifierIsInUse(m_identifier))
    {
        identifier = m_identifier;



        return true;
    }

    return false;
}

PageRecord& GetPageRecord(const std::string identifier)
{
    // For now, use a dumb linear search function. This can be improved later on
    for(auto iter = PageRecord::ALL_PAGE_RECORDS.begin();
        iter != PageRecord::ALL_PAGE_RECORDS.end();
        iter++)
    {
        if(iter->identifier == identifier)
        {
            return *iter;
        }
    }

    throw PageRecordNotFound(identifier);
}

PageRecord* PageRecord::GetPageRecord(const std::string identifier)
{
    return &(*std::find(ALL_PAGE_RECORDS.begin(), ALL_PAGE_RECORDS.end(), identifier));
}

PageRecord* PageRecord::MakePageRecord(const std::string identifier,
                                       std::string relativePath,
                                       std::string fileName)
{
    if(IdentifierIsInUse(identifier))
    {
        throw PageIdentifierInUse(identifier);
    }

    ALL_PAGE_RECORDS.push_back(PageRecord(identifier, relativePath, fileName));
    return &ALL_PAGE_RECORDS.back();
}

void PageRecord::RemoveRecord(PageRecord *record)
{
    std::remove(ALL_PAGE_RECORDS.begin(), ALL_PAGE_RECORDS.end(), record);
}

bool PageRecord::IdentifierIsInUse(const std::string identifier)
{
    return ALL_PAGE_RECORDS.end() == std::find(ALL_PAGE_RECORDS.begin(), ALL_PAGE_RECORDS.end(), identifier);
}

bool PageRecord::operator==(const std::string identifier) const
{
    return this->identifier == identifier;
}

bool PageRecord::operator==(const PageRecord *record) const
{
    return identifier == record->identifier;
}

void PageRecord::operator=(const PageRecord& record)
{
    if(IdentifierIsInUse(identifier))
    {
        throw PageIdentifierInUse("Cannot reassign a pageRecord without proper teardown first, might cause duplication!");
    }
    identifier = record.identifier;
    filePath = record.filePath;
}

void PageRecord::_GenerateIdentifier()
{
    bool generating = true;

    while(generating)
    {
        int randNum = rand();

        if(randNum == 0)
        {
            continue;
        }
        else if(!IdentifierIsInUse(std::to_string(randNum)))
        {
            char hexString[8];
            sprintf(hexString, "%X", randNum);
            identifier = hexString;

            generating = false;
        }
        else
        {
            continue;
        }
    }
}

void PageRecord::_LoadRecordsFromFile()
{

}

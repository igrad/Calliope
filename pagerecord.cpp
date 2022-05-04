#include "pagerecord.h"

#include <algorithm>

std::string PAGERECORDFILEPATH = "";
QUuid NULLPAGEID = QUuid();

std::vector<PageRecord> PageRecord::ALL_PAGE_RECORDS;

PageRecord::PageRecord(QUuid& m_identifier,
                       std::string m_relativePath,
                       std::string m_fileName)
  : identifier(m_identifier)
{
    if(m_identifier.isNull())
    {
        identifier = QUuid::createUuid();
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
    removeRecord(this);
}

bool PageRecord::setIdentifier(QUuid& m_identifier)
{
    if(!identifierIsInUse(m_identifier))
    {
        identifier = m_identifier;



        return true;
    }

    return false;
}

PageRecord& GetPageRecord(const QUuid& identifier)
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

    throw PageRecordNotFound(identifier.toString().toStdString());
}

PageRecord* PageRecord::getPageRecord(const QUuid& identifier)
{
    return &(*std::find(ALL_PAGE_RECORDS.begin(), ALL_PAGE_RECORDS.end(), identifier));
}

PageRecord* PageRecord::makePageRecord(QUuid& identifier,
                                       std::string relativePath,
                                       std::string fileName)
{
    if(identifierIsInUse(identifier))
    {
        throw PageIdentifierInUse(identifier);
    }

    ALL_PAGE_RECORDS.push_back(PageRecord(identifier, relativePath, fileName));
    return &ALL_PAGE_RECORDS.back();
}

void PageRecord::removeRecord(PageRecord *record)
{
    std::remove(ALL_PAGE_RECORDS.begin(), ALL_PAGE_RECORDS.end(), record);
}

bool PageRecord::identifierIsInUse(const QUuid& identifier)
{
    return ALL_PAGE_RECORDS.end() == std::find(ALL_PAGE_RECORDS.begin(), ALL_PAGE_RECORDS.end(), identifier);
}

bool PageRecord::operator==(const QUuid& rhs) const
{
    return identifier == rhs;
}

bool PageRecord::operator==(const PageRecord *record) const
{
    return identifier == record->identifier;
}

void PageRecord::operator=(const PageRecord& record)
{
    if(identifierIsInUse(identifier))
    {
        throw PageIdentifierInUse(identifier);
    }
    identifier = record.identifier;
    filePath = record.filePath;
}

void PageRecord::_loadRecordsFromFile()
{
    return;
}

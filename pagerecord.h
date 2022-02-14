#ifndef PAGERECORD_H
#define PAGERECORD_H

#include <QObject>
#include <iostream>
#include <vector>
#include <filesystem>

extern std::string PAGERECORDFILEPATH;

class PageRecord: QObject
{
    Q_OBJECT
public:
    PageRecord(std::string m_identifier = "",
               std::string m_relativePath = "",
               std::string m_fileName = "");
    PageRecord(const PageRecord& record);
    ~PageRecord();

    bool SetIdentifier(std::string m_identifier);

    std::string identifier;
    std::filesystem::path filePath;

    // Static members
    static PageRecord* GetPageRecord(const std::string identifier);
    static PageRecord* MakePageRecord(const std::string identifier,
                                      const std::string relativePath,
                                      const std::string fileName);

    static void RemoveRecord(PageRecord* record);
    static bool IdentifierIsInUse(const std::string identifier);

    static std::vector<PageRecord> ALL_PAGE_RECORDS;

    bool operator== (const std::string identifier) const;
    bool operator== (const PageRecord* record) const;
    void operator= (const PageRecord& record);

signals:
    void IdentifierChanged(std::string newIdentifier);

private:
    void _GenerateIdentifier();
    void _LoadRecordsFromFile();
};



struct PageRecordException : public std::exception
{
    PageRecordException(const std::string msg)
        : _msg(msg)
    {

    }

    const char* what() const throw()
    {
        return (_msg == "") ? "Undefined PageRecord exception" : _msg.c_str();
    }

    std::string _msg;
};

struct PageRecordNotFound : public PageRecordException
{
    PageRecordNotFound(const std::string msg)
        : PageRecordException("PageRecord not found: " + msg)
    {

    }
};

struct PageIdentifierInUse : public PageRecordException
{
    PageIdentifierInUse(const std::string identifier)
        : PageRecordException("Page identifier \"" + identifier + "\" is already in use!")
    {

    }
};


#endif // PAGERECORD_H

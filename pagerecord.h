#ifndef PAGERECORD_H
#define PAGERECORD_H

#include <iostream>
#include <QObject>
#include <QUuid>
#include <vector>

// Filesystem (and other classes that use filesystem) is put last due to a Qt bug.
// See https://bugreports.qt.io/browse/QTBUG-73263
#include <filesystem>

extern std::string PAGERECORDFILEPATH;
extern QUuid NULLPAGEID;

class PageRecord: QObject
{
    Q_OBJECT
public:
    PageRecord(QUuid& m_identifier = NULLPAGEID,
               std::string m_relativePath = "",
               std::string m_fileName = "");
    PageRecord(const PageRecord& record);
    ~PageRecord();

    bool SetIdentifier(QUuid& m_identifier);

    // Static members
    static PageRecord* GetPageRecord(const QUuid& identifier);
    static PageRecord* MakePageRecord(QUuid& identifier,
                                      const std::string relativePath,
                                      const std::string fileName);

    static void RemoveRecord(PageRecord* record);
    static bool IdentifierIsInUse(const QUuid& identifier);

    // Operators
    bool operator== (const QUuid& rhs) const;
    bool operator== (const PageRecord* record) const;
    void operator= (const PageRecord& record);

    static std::vector<PageRecord> ALL_PAGE_RECORDS;
    QUuid& identifier;
    std::filesystem::path filePath;

signals:
    void IdentifierChanged(const QUuid& newIdentifier);

private:
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
    PageIdentifierInUse(const QUuid& identifier)
        : PageRecordException("Page identifier \"" + identifier.toString().toStdString() + "\" is already in use!")
    {

    }
};


#endif // PAGERECORD_H

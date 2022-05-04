#ifndef PAGE_H
#define PAGE_H

#include "folders.h"
#include <fstream>
#include <iostream>
#include "pagerecord.h"
#include <QDebug>
#include <QObject>
#include <QUuid>
#include <string>
#include <sstream>

class Folder;
class PageRecord;

class Page : public QObject
{
    Q_OBJECT

public:
    Page();
    explicit Page(QUuid& newIdentifier = NULLPAGEID,
                  std::string newFileName = "NewPage." + PAGE_FILE_EXTENSION,
                  Folder* newParent = nullptr);
    Page(PageRecord* newRecord, Folder* newParent = nullptr);

    // Getters
    std::string getData() const;
    const QUuid getIdentifier() const;
    std::filesystem::path getFilePath() const;
    PageRecord* getPageRecord() const;
    bool isOpen() const;

    // Setters
    void setData(const std::string data);

    // Static Methods
    static bool isIdentifierValid(const QUuid& identifier);
    static void makePageNameValid(std::string& fileName);

    // Operators
    bool operator== (const Page& rhs);
    bool operator== (const QUuid& rhs);
    void operator= (const Page& rhs);

    // Static Constants
    static int PAGE_COUNT;
    static std::map<QUuid, std::string> ID_MAP;
    static const std::string PAGE_FILE_EXTENSION;

public slots:
    // Persistence
    bool deleteFile();
    bool loadFromFile();
    bool saveToFile();

signals:
    void identifierChanged(const QUuid& newIdentifier);

protected:
    bool _fileExists();
    bool _loadPageContentFromFile();
    bool _savePageContentToFile();
    void _setIdentifier(const QUuid& identifier);

    QUuid identifier;
    bool open;
    std::filesystem::path filePath;
    std::string fileName;
    std::string pageData;
    PageRecord* pageRecord;
    Folder* parent;
    std::string relativePath;
};

#endif // PAGE_H

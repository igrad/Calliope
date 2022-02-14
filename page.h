#ifndef PAGE_H
#define PAGE_H

#include <QObject>
#include <iostream>
#include <string>
#include <sstream>
#include "pagerecord.h"
#include "filemanager.h"
#include "folder.h"

class Folder;
class PageRecord;

class Page : public QObject
{
    Q_OBJECT
public:
    // Instanced Functions
    explicit Page(const std::string identifier = Page::NULL_ID,
                  Folder* parent = nullptr);
    Page(PageRecord* record, Folder* parent = nullptr);
    void Open();
    std::string GetIdentifier() const;
    std::filesystem::path GetFilePath() const;
    std::string GetData() const;
    bool IsOpen() const;
    void SetData(const std::string data);

    // Static Methods
    static bool IsIdentifierValid(const std::string identifier);

    // Static Constants
    static const std::string NULL_ID;
    static int PAGE_COUNT;
    static std::map<std::string, std::string> ID_MAP;
    static const std::string PAGE_FILE_EXTENSION;

signals:

private slots:
    // void IdentifierChanged(std::string newIdentifier);

protected:
    void _SetIdentifier(const std::string identifier);
    void _LoadPageContentFromFile();
    void _SavePageContentToFile();

    std::string _identifier;
    std::string _relativePath;
    std::string _fileName;
    std::filesystem::path _filePath;

    bool _isOpen;

    std::string _pageData;
    PageRecord* _pageRecord;
};

#endif // PAGE_H

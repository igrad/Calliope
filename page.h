#ifndef PAGE_H
#define PAGE_H

#include "folder.h"
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
    explicit Page(const QUuid& identifier = NULLPAGEID,
                  std::string fileName = "NewPage." + PAGE_FILE_EXTENSION,
                  Folder* parent = nullptr);
    Page(PageRecord* record, Folder* parent = nullptr);

    // Getters
    QUuid GetIdentifier();
    std::filesystem::path GetFilePath() const;
    std::string GetData() const;
    bool IsOpen() const;

    // Setters
    void SetData(const std::string data);

    // Static Methods
    static bool IsIdentifierValid(const QUuid& identifier);
    static void MakePageNameValid(QString& fileName);

    // Operators
    bool operator== (const Page& rhs);
    bool operator== (const QUuid& rhs);

    // Static Constants
    static int PAGE_COUNT;
    static std::map<QUuid, std::string> ID_MAP;
    static const std::string PAGE_FILE_EXTENSION;

public slots:
    // Persistence
    bool LoadFromFile();
    bool SaveToFile();
    bool DeleteFile();

signals:
    void IdentifierChanged(const QUuid& newIdentifier);

protected:
    bool _FileExists();
    void _SetIdentifier(const QUuid& identifier);
    bool _LoadPageContentFromFile();
    bool _SavePageContentToFile();

    QUuid _identifier;
    std::string _relativePath;
    std::string _fileName;
    std::filesystem::path _filePath;

    bool _isOpen;

    std::string _pageData;
    PageRecord* _pageRecord;
};

#endif // PAGE_H

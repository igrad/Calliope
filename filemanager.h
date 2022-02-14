#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <iostream>
#include <fstream>
#include "page.h"

class Page;

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);

    static bool SavePageToFile(Page& page);
    static bool LoadPageFromFile(Page& page);
    static bool DeleteFile(Page& page);
    static bool Exists(Page& page);

    static void MakeFileNameValid(std::string& fileName);

signals:

private:
    static bool _SaveDataToFile(const std::string &data, const std::filesystem::path path);
};

#endif // FILEMANAGER_H

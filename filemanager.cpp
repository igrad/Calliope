#include "filemanager.h"
#include <stdio.h>
#include <filesystem>
#include <regex>
#include <algorithm>

FileManager::FileManager(QObject *parent) : QObject(parent)
{

}

bool FileManager::SavePageToFile(Page &page)
{
    return _SaveDataToFile(page.GetData(), page.GetFilePath());
}



bool FileManager::_SaveDataToFile(const std::string &data, const std::filesystem::path path)
{
    std::ofstream openFile;

    try
    {
        openFile.open(path, std::ios::out);

        if(openFile.is_open())
        {
            openFile << data;
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

        std::cout << "Error writing data to file! path: " << path << std::endl;
        return false;
    }
}

bool FileManager::LoadPageFromFile(Page& page)
{
    // Load page contents from file into the page object
    std::ifstream openFile;

    try
    {
        openFile.open(page.GetFilePath(), std::ios::in);

        if(openFile.is_open())
        {
            std::stringstream pageData;
            pageData << openFile.rdbuf();
            page.SetData(pageData.str());
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

        std::cout << "Error reading data from file! path: " << page.GetFilePath()
                  << std::endl;
        return false;
    }
}

bool FileManager::DeleteFile(Page &page)
{
    return remove(page.GetFilePath()) != 0;
}

bool FileManager::Exists(Page &page)
{
    return std::filesystem::exists(page.GetFilePath());
}

void FileManager::MakeFileNameValid(std::string& fileName)
{
    char forbiddenChars[10] = {'<', '>', ':', ';', '\"', '/', '\\', '|', '?', '*'};
    int numForbiddenChars = 10;

    for(int iter = 0; iter < numForbiddenChars; ++iter)
    {
        char ch = forbiddenChars[iter];
        std::remove_if(fileName.begin(), fileName.end(), [ch](char x){return x == ch;});
    }
}

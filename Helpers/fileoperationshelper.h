#ifndef FILEOPERATIONSHELPER_H
#define FILEOPERATIONSHELPER_H

#include <fstream>
#include <filesystem>

bool isFilePathValid(std::filesystem::path path)
{
    std::fstream f(path, std::ios_base::in);
    try {
        return f.good();
    }  catch (...) {
        return false;
    }
}

#endif // FILEOPERATIONSHELPER_H

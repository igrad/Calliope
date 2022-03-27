#ifndef OSDEFINES_H
#define OSDEFINES_H

#include <string>
#include <filesystem>

using namespace std;

extern const string SESSIONDATAFILENAME = "sessiondata";
extern const string SESSIONDATAFILEEXTENSION = ".json";

string GetOperatingSystem()
{
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}

filesystem::path GetTempDirPath()
{
    return filesystem::temp_directory_path();
}

string GetTempDirPathString()
{
    return GetTempDirPath().string();
}

filesystem::path GetTempDataFileName()
{
    return GetTempDirPath().replace_filename(SESSIONDATAFILENAME).replace_extension(SESSIONDATAFILEEXTENSION);
}

string GetTempDataFileNameString()
{
    return GetTempDataFileName().string();
}

#endif // OSDEFINES_H

#ifndef OSDEFINES_H
#define OSDEFINES_H

#include <string>
#include <filesystem>


namespace TempDataService
{
    constexpr char SESSIONDATAFILENAME[] = "sessiondata";
    constexpr char SESSIONDATAFILEEXTENSION[] = ".json";

    inline std::string GetOperatingSystem()
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

    inline std::filesystem::path GetTempDirPath()
    {
        return std::filesystem::temp_directory_path();
    }

    inline std::string GetTempDirPath(std::string)
    {
        return GetTempDirPath().string();
    }

    inline std::filesystem::path GetTempDataFileName()
    {
        return GetTempDirPath().replace_filename(SESSIONDATAFILENAME).replace_extension(SESSIONDATAFILEEXTENSION);
    }

    inline std::string GetTempDataFileName(std::string)
    {
        return GetTempDataFileName().string();
    }
}

#endif // OSDEFINES_H

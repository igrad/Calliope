#ifndef OSDEFINES_H
#define OSDEFINES_H

#include <string>
#include <filesystem>


namespace TempDataService
{
    constexpr char SESSIONDATAFILENAME[] = "sessiondata";
    constexpr char SESSIONDATAFILEEXTENSION[] = ".json";

    inline std::string getOperatingSystem()
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

    inline std::filesystem::path getTempDirPath()
    {
        return std::filesystem::temp_directory_path();
    }

    inline std::string getTempDirPath(std::string)
    {
        return getTempDirPath().string();
    }

    inline std::filesystem::path getTempDataFileName()
    {
        return getTempDirPath().replace_filename(SESSIONDATAFILENAME).replace_extension(SESSIONDATAFILEEXTENSION);
    }

    inline std::string getTempDataFileName(std::string)
    {
        return getTempDataFileName().string();
    }
}

#endif // OSDEFINES_H

#ifndef OSDEFINES_H
#define OSDEFINES_H

#include <string>
#include <filesystem>


namespace TempDataService
{
    constexpr char GLOBAL_CONFIG_FILENAME[] = "CalliopeUniversalConfigs";
    constexpr char NOTEBOOK_CONFIG_FILENAME[] = "sessiondata";
    constexpr char CONFIG_FILE_EXTENSION[] = ".txt";

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

    inline std::filesystem::path getCurrentPath()
    {
        return std::filesystem::current_path();
    }

    inline std::string getTempDirPath(std::string)
    {
        return getTempDirPath().string();
    }

    inline std::filesystem::path getGlobalConfigFileName()
    {
        return getTempDirPath().replace_filename(GLOBAL_CONFIG_FILENAME).replace_extension(CONFIG_FILE_EXTENSION);
    }

    inline std::filesystem::path getNotebookConfigFileName()
    {
        return getCurrentPath().replace_filename(NOTEBOOK_CONFIG_FILENAME).replace_extension(CONFIG_FILE_EXTENSION);
    }
}

#endif // OSDEFINES_H

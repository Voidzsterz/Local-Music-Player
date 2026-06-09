#pragma once

#include <vector>
#include <filesystem>

class Directories
{
public:
    void promptDirectorySelect(); // Long/confusing name, might change
    void allocateDirectory();
    void deallocateDirectory();
    void clearDirectories();
    void scanDirectories();
private:
    // Vector array containing all directories
    std::vector<std::filesystem::path> m_directories;
};
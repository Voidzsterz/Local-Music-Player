#pragma once

#include <vector>
#include <filesystem>

class Directories
{
public:
    using Path = std::filesystem::path; // Creates a "type alias" for std::filesystem::path (nothing changes, just easier for me to read)
    const std::vector<Path>& getDirectories() const { return m_directories; } // Essentially returns a read-only REFERENCE to the directories array

    void promptDirectorySelect(); // Long/confusing name, might change
    void addDirectory(const std::string& path);
    void removeDirectory(const std::string& path);
    void clearDirectories();
    void scanDirectories();
private:
    // Vector array containing all directories
    std::vector<Path> m_directories;
}; 
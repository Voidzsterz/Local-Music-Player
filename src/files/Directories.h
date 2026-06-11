#pragma once

#include <imgui.h>

#include <vector>
#include <filesystem>

struct DirectoryItem
{
    ImGuiID ID;
    std::string path;
};

struct PathNode
{
    std::string name;
    std::filesystem::path fullPath;
    bool isDirectory;
    std::vector<PathNode> children;
};

class Directories
{
public:
    using Path = std::filesystem::path; // Creates a "type alias" for std::filesystem::path (nothing changes, just easier for me to read)
    const std::vector<Path>& getDirectories() const { return m_directories; } // Essentially returns a read-only REFERENCE to the directories array

    void promptDirectorySelect();
    void addDirectory(const std::string& path);
    void removeDirectory(const std::string& path);
    void removeDirectories(const std::vector<std::string>& paths);
    void clearDirectories();

    PathNode scanPath(const std::filesystem::path& path) const;
private:
    // Vector array containing all directories
    std::vector<Path> m_directories;

    // Helper function, might make public if other files want it
    bool isSupportedFormat(const std::string& path) const;
}; 
#include "filesystem"
#include <iostream>

#include "portable-file-dialogs.h"

#include "Directories.h"

void Directories::promptDirectorySelect()
{
    // TODO: Make this return the selection rather than add the directory for us, making it more "independant"
    // PFD handles this for us, great library :)
    auto selection = pfd::select_folder("Select a Directory").result();

    if (!selection.empty())
    {
        addDirectory(selection);
    }
}

void Directories::addDirectory(const std::string &path)
{
    std::cout << "Attempting addition of directory: " << path.c_str() << std::endl;
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
        if (std::find(m_directories.begin(), m_directories.end(), path) == m_directories.end())
        {
          m_directories.push_back(path);
          std::cout << "Successfully added directory: " << path.c_str()<< std::endl;
        }
    }
    m_needsRescan = true;
}

void Directories::removeDirectory(const std::string &path)
{
    // We can simply use ".erase" for this, no need to loop through everything
    // like in addDirectory If erase doesn't find anything, nothing happens, it
    // works out whether the directory exists or not
    std::cout << "Attempting removal of directory: " << path.c_str() << std::endl;
    m_directories.erase(std::remove(m_directories.begin(), m_directories.end(), path), m_directories.end());
    m_needsRescan = true;
}

void Directories::clearDirectories()
{
    std::cout << "Clearing all directories..." << std::endl;
    m_directories.clear();
    m_needsRescan = true;
}

bool Directories::needsRescan() const
{
    return (m_needsRescan == 1);
}

void Directories::clearRescan()
{
    m_needsRescan = 0;
}

PathNode Directories::scanPath(const std::filesystem::path& path) const
{
    // Recursive function, calls itself for each "child"
    std::cout << "Scanning: " << path << std::endl;
    PathNode node;
    node.name = path.filename().string();
    node.fullPath = path;
    node.isDirectory = std::filesystem::is_directory(path);

    if (node.isDirectory)
    {
        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            std::cout << "Found: " << entry.path() << std::endl;
            // This will create recursion in the function, eventually it will find every "child" of path following this procedure
            node.children.push_back(scanPath(entry.path()));
        }
    }

    return node;
}

bool Directories::isSupportedFormat(const std::string& path) const
{
    std::string extension = std::filesystem::path(path).extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    return extension == ".mp3" || extension == ".wav" || extension == ".flac";
}
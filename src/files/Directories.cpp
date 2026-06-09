#include "filesystem"
#include <vector>
#include <algorithm>
#include <iostream>

#include "Directories.h"

void Directories::promptDirectorySelect()
{
    // This will be added later, for now "test" directories will be used for debugging (or directly inputting directories via a string maybe)
}

void Directories::addDirectory(const std::string& path)
{
    std::cout << "Attempting addition of directory: " << path.c_str() << std::endl;
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
    {
        if (std::find(m_directories.begin(), m_directories.end(), path) == m_directories.end())
        {
            m_directories.push_back(path);
            std::cout << "Successfully added directory: " << path.c_str() << std::endl;
        }
    }
}

void Directories::removeDirectory(const std::string& path)
{
    // We can simply use ".erase" for this, no need to loop through everything like in addDirectory
    // If erase doesn't find anything, nothing happens, it works out whether the directory exists or not
    std::cout << "Attempting removal of directory: " << path.c_str() << std::endl;
    m_directories.erase
    (
        std::remove(m_directories.begin(), m_directories.end(), path), m_directories.end()
    );
}

void Directories::clearDirectories()
{
    std::cout << "Clearing all directories..." << std::endl;
    m_directories.clear();
}

void Directories::scanDirectories()
{
    // not sure how im gonna make this work
    // TODO: MAKE THIS WORK
    std::cout << "(WIP) This is a test print for scanDirectories" << std::endl;
}
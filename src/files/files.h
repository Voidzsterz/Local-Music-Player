#pragma once

#include <vector>
#include <filesystem>

/*
Name of these files are a little confusing and misleading so I want to clarify
files.h and files.cpp manage and handle directories.
I'd prefer not to name it "Directories", since thats already used in src/ui/contents

TODO:
Potentially change name of these files to "Directories", and have the UI ones called "DirectoriesUI"
*/

class Files
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
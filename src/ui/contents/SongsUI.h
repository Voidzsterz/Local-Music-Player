#pragma once

#include "../../files/Directories.h"

class SongsUI
{
public:
    SongsUI(Directories& directories);
    void render();
private:
    Directories& m_directories;

    void renderTopbar();
    void renderTree(const PathNode& node);

    // Caching allows huge performance increases (The program was crashing when the songs tab opened originally)
    std::vector<PathNode> m_cachedTrees;
};
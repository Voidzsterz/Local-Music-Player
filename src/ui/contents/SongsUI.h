#pragma once

#include "../../files/Directories.h"

class Renderer;

class SongsUI
{
public:
    SongsUI(Renderer& renderer, Directories& directories);
    void render();
private:
    Renderer& m_renderer;
    Directories& m_directories;

    void renderTopbar();
    void renderTree(const PathNode& node);

    // Caching allows huge performance increases (The program was crashing when the songs tab opened originally)
    std::vector<PathNode> m_cachedTrees;
};
#pragma once

#include "../../files/Directories.h"



class Renderer;

struct SongItem
{
    ImGuiID ID;
    std::string path;
};

class SongsUI
{
public:
    SongsUI(Renderer& renderer, Directories& directories);
    void render();
private:
    Renderer& m_renderer;
    Directories& m_directories;

    ImGuiSelectionBasicStorage m_selection;
    std::vector<SongItem> m_songItems;

    void renderTopbar();
    void renderTree(const PathNode& node, int& songIndex);

    void collectSongs(PathNode& node, int& index);
    
    // Caching allows huge performance increases (The program was crashing when the songs tab opened originally)
    std::vector<PathNode> m_cachedTrees;
};
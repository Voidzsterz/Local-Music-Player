#pragma once

#include "../../files/Directories.h"

class Renderer;

class DirectoriesUI
{
public:
    DirectoriesUI(Renderer& renderer, Directories& directories);
    void render();
private:
    Renderer& m_renderer;
    Directories& m_directories;

    ImGuiSelectionBasicStorage m_selection;
    std::vector<DirectoryItem> m_items;

    void renderTopbar();
    void renderTable();
};
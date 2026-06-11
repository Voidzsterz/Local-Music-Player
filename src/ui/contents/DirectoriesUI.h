#pragma once

#include "../../files/Directories.h"

class DirectoriesUI
{
public:
    DirectoriesUI(Directories& directories);
    void render();
private:
    Directories& m_directories;

    ImGuiSelectionBasicStorage m_selection;
    std::vector<DirectoryItem> m_items;

    void renderTopbar();
    void renderTable();
};
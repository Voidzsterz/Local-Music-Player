#pragma once

#include "contents/DirectoriesUI.h"

class UI
{
public:
    void render();
private:
    // m_activeTab will decide what to render inside the "content" page
    enum class ActiveTab { Home, Songs, Library, Directories, Settings, };
    ActiveTab m_activeTab = ActiveTab::Home;

    // Contents
    DirectoriesUI m_directoriesUI;

    void renderSidebar();
    void renderContents();
    void renderPlaying();
    void renderDockspace();
};
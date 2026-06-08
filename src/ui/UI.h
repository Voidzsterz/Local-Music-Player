#pragma once

#include "contents/Directories.h"

class UI
{
public:
    void render();
private:
    // m_activeTab will decide what to render inside the "content" page
    enum class ActiveTab { Home, Songs, Library, Directories, Settings, };
    ActiveTab m_activeTab = ActiveTab::Home;

    // Contents
    Directories m_directories;

    void renderSidebar();
    void renderContents();
    void renderPlaying();
    void renderDockspace();
};
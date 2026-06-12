#pragma once

#include "../renderer/Renderer.h"

#include "contents/SongsUI.h"
#include "contents/DirectoriesUI.h"

class UI
{
public:
    UI(Renderer& renderer, Directories& directories);

    void render();
private:
    // m_activeTab will decide what to render inside the "content" page
    enum class ActiveTab { Home, Songs, Library, Directories, Settings, };
    ActiveTab m_activeTab = ActiveTab::Home;

    Renderer& m_renderer;
    Directories& m_directories;

    // Contents
    SongsUI m_songsUI;
    DirectoriesUI m_directoriesUI;

    void renderSidebar();
    void renderContents();
    void renderPlaying();
    void renderDockspace();
};
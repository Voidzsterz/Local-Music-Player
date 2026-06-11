#pragma once

#include "contents/SongsUI.h"
#include "contents/DirectoriesUI.h"

class UI
{
public:
    UI(Directories& directories);
    ~UI();
    void createTextures();

    void render();
private:
    // m_activeTab will decide what to render inside the "content" page
    enum class ActiveTab { Home, Songs, Library, Directories, Settings, };
    ActiveTab m_activeTab = ActiveTab::Home;

    Directories& m_directories;

    // Images (Texture IDs)
    unsigned int m_homeIcon = 0;
    unsigned int m_songsIcon = 0;
    unsigned int m_libraryIcon = 0;
    unsigned int m_directoriesIcon = 0;
    unsigned int m_settingsIcon = 0;

    // Contents
    SongsUI m_songsUI;
    DirectoriesUI m_directoriesUI;

    void renderSidebar();
    void renderContents();
    void renderPlaying();
    void renderDockspace();
};
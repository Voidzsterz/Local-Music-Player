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
    unsigned int icon_home = 0;
    unsigned int icon_songs = 0;
    unsigned int icon_library = 0;
    unsigned int icon_directories = 0;
    unsigned int icon_settings = 0;

    unsigned int icon_folder = 0;
    unsigned int icon_musicFile = 0;

    // Contents
    SongsUI m_songsUI;
    DirectoriesUI m_directoriesUI;

    void renderSidebar();
    void renderContents();
    void renderPlaying();
    void renderDockspace();
};
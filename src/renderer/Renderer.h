#pragma once

#include <imgui.h>

struct GLFWwindow;

class Renderer
{
public:
    Renderer(GLFWwindow* window);
    ~Renderer();
    
    void newFrame();
    void presentFrame();

    // Maybe not the best idea to store fonts and textures here, but the next best solution was passing Renderer into UI.cpp
    // AS LONG AS RENDERER IS ONLY INCLUDED FOR THESE FONTS, NO ISSUES SHOULD OCCUR
    // (dependency injection is ignored in some files for this reason)
    
    // Fonts
    // Numbers at the equals the size of the font
    static ImFont* font_soraBold13; // 13px, Sora, Bold (Standard font, used pretty much everywhere)
    static ImFont* font_soraBold20; // 20px, Sora, Bold
    static ImFont* font_soraExtraLight20; // 13px, Sora, Extra Light Bold

    // Icons
    static unsigned int icon_home;
    static unsigned int icon_songs;
    static unsigned int icon_library;
    static unsigned int icon_directories;
    static unsigned int icon_settings;

    static unsigned int icon_folder;
    static unsigned int icon_musicFile;
private:
    GLFWwindow* m_window = nullptr;

    bool init();
    void shutdown();
};
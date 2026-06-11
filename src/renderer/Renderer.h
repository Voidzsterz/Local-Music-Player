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

    // Maybe not the best idea to store fonts here, but the next best solution was passing Renderer into UI.cpp
    // AS LONG AS RENDERER IS ONLY INCLUDED FOR THESE FONTS, NO ISSUES SHOULD OCCUR
    // (dependency injection is ignored in some files for this reason)
    
    // Numbers at the equals the size of the font
    static ImFont* font_soraBold13; // Sora, Normal size, Bold (Standard font, used pretty much everywhere)
    static ImFont* font_soraExtraLight20; // Sora, Extra Light size, Bold
private:
    GLFWwindow* m_window = nullptr;

    bool init();
    void shutdown();
};
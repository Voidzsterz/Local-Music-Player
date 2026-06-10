#pragma once

#include "../ui/UI.h"

struct GLFWwindow;
class Renderer;

class App
{
public:
    App(int width, int height);     // Constructor
    ~App();                         // Destructor
    
    void run();
private:
    GLFWwindow* m_window = nullptr;

    // List of header files, these will be passed down via "Dependency Injection" to whatever files need it (like a tree)
    Directories m_directories;
    UI m_ui;
    Renderer* m_renderer = nullptr;

    int m_windowWidth  = 1280;
    int m_windowHeight = 720;

    void init();
    void loop();
    void shutdown();
};
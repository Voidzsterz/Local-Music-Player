#pragma once

#include "../ui/UI.h"

struct GLFWwindow;
class Renderer;

class App
{
public:
    App(int width, int height);  // Constructor
    ~App(); // Destructor
    
    void run();
private:
    GLFWwindow* m_window = nullptr;
    Renderer* m_renderer = nullptr;
    UI m_ui;

    int m_windowWidth  = 1280;
    int m_windowHeight = 720;

    void init();
    void loop();
    void shutdown();
};
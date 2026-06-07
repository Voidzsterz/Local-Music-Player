#pragma once

struct GLFWwindow;
class Renderer;

class App
{
public:
    App();  // Constructor
    ~App(); // Destructor
    
    void run();
private:
    GLFWwindow* m_window = nullptr;
    Renderer* m_renderer = nullptr;

    void init();
    void loop();
    void shutdown();
};
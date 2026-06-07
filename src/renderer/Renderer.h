#pragma once

struct GLFWwindow;

class Renderer
{
public:
    Renderer(GLFWwindow* window);
    ~Renderer();
    
    void newFrame();
    void presentFrame();
private:
    GLFWwindow* m_window = nullptr;

    bool init();
    void shutdown();
};
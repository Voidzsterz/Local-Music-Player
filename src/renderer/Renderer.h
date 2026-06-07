#pragma once

struct GLFWwindow;

class Renderer
{
public:
    Renderer(GLFWwindow* window);
    ~Renderer();
    
    void createFrame();
    void presentFrame();
private:
    GLFWwindow* m_window = nullptr;

    bool init();
    void shutdown();
};
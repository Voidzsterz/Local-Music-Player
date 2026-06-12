#include <GLFW/glfw3.h>

#include <iostream>

#include "App.h"
#include "../renderer/Renderer.h"
/*
Constructor "App::App()"
App::App() is called automatically when App is created (App x;)

Destructor "App::~App()"
App::~App() is called automatically when App goes out of scope

"Out of scope" refers to when the brackets "{}" App is nested in ends
App itself lives on the stack so its destructor is called automatically when out of scope
TLDR: Stack handles the destructor for us, destructor is called when the app is closing

Heap allocated members dont have those benefits (m_window, m_renderer)
They must be manually deleted through the "delete" method
*/

// This constructor in particular uses initalizer lists, documentation for that can be found in Renderer.cpp

App::App(int width, int height)
    : m_windowWidth(width), m_windowHeight(height)
{ 
    init();
    m_ui = std::make_unique<UI>(*m_renderer, m_directories);
}

App::~App() { shutdown(); } // Destructor

void App::init()
{
    // Window creatioon
    std::cout << "Initalizing GLFW" << std::endl;
    if (!glfwInit())
    {
        std::cout << "Failed to initalize GLFW, refusing to continue." << std::endl;
        return;
    }

    std::cout << "GLFW initalized" << std::endl;
    
    std::cout << "Creating GLFWwindow" << std::endl;
    m_window = glfwCreateWindow(1080, 720, "Music Player", NULL, NULL);
    if (!m_window)
    {
        std::cout << "Failed to create GLFW window, refusing to continue." << std::endl;
        glfwTerminate();
        return;
    }
    glfwSetWindowSizeLimits(m_window, 800, 200, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwMakeContextCurrent(m_window);
    std::cout << "GLFW window created" << std::endl;

    // Renderer initalization
    m_renderer = new Renderer(m_window);
}

void App::run()
{
    std::cout << "Beginning runtime loop" << std::endl;

    while (!glfwWindowShouldClose(m_window))
    {    
        glfwPollEvents();

        m_renderer->newFrame();
        m_ui->render();
        m_renderer->presentFrame();
        glfwSwapBuffers(m_window);
    }
}

void App::shutdown()
{
    std::cout << "Closing..." << std::endl;

    delete m_renderer;
    m_renderer = nullptr;
    glfwTerminate();
}
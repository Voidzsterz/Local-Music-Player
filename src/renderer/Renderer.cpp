#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

#include "Renderer.h"
#include "../ui/UI.h"

/*
Initalizer lists runs before the constructor body

They can allow the initatization of members with no default constructor
("members" refer to the variables in the .h file)

This also has the positive of preventing cases where the member has a value assgined twice
*/

Renderer::Renderer(GLFWwindow* window)
    : m_window(window)
{ init(); }

Renderer::~Renderer(){ shutdown(); }

bool Renderer::init()
{
    // Initalize GLAD and ImGui
    std::cout << "Initalizing GLAD" << std::endl;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    std::cout << "GLAD initalized" << std::endl;
    std::cout << "Initalizing ImGui" << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    std::cout << "ImGui Initalized" << std::endl;

    // ImGui configuration
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    return true;
}

void Renderer::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // UI is NOT drawn here, everything for UI is handled in the "ui" folder
}

void Renderer::presentFrame()
{
    // Clear the canvas/screen
    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);
    glViewport(0, 0, w, h);

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Render the frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::shutdown()
{
    // clean up imgui
}
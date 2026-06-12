#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

#include "Renderer.h"
#include "../image/Image.h"

// Fonts
ImFont* Renderer::font_soraBold13 = nullptr;
ImFont* Renderer::font_soraBold20 = nullptr;
ImFont* Renderer::font_soraExtraLight20 = nullptr;

// Icons
unsigned int Renderer::icon_home = 0;
unsigned int Renderer::icon_songs = 0;
unsigned int Renderer::icon_library = 0;
unsigned int Renderer::icon_directories = 0;
unsigned int Renderer::icon_settings = 0;

unsigned int Renderer::icon_folder = 0;
unsigned int Renderer::icon_musicFile = 0;

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

    // Texture IDs
    icon_home = loadTexture("assets/images/home.png");
    icon_songs = loadTexture("assets/images/audio-lines.png");
    icon_library = loadTexture("assets/images/library-big.png");
    icon_directories = loadTexture("assets/images/folder-open.png");
    icon_settings = loadTexture("assets/images/settings.png");

    icon_folder = loadTexture("assets/images/folder.png");
    icon_musicFile = loadTexture("assets/images/file-music.png");

    // ImGui configuration
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // 13.0f is the size of the default ImGui font I believe
    font_soraBold13 = io.Fonts->AddFontFromFileTTF("assets/fonts/Sora-Bold.ttf", 13.0f);
    font_soraBold20 = io.Fonts->AddFontFromFileTTF("assets/fonts/Sora-Bold.ttf", 20.0f);
    font_soraExtraLight20 = io.Fonts->AddFontFromFileTTF("assets/fonts/Sora-ExtraLight.ttf", 20.0f);

    ImGui::StyleColorsDark();
 
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_TableRowBg] = ImVec4(0.1f,0.1f,0.1f,1.0f);

    return true;
}

void Renderer::newFrame()
{
    // UI is NOT drawn here, everything for UI is handled in the "ui" folder
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
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
    std::cout << "Shutting down Renderer..." << std::endl;

    glDeleteTextures(1, &icon_home);
    glDeleteTextures(1, &icon_songs);
    glDeleteTextures(1, &icon_library);
    glDeleteTextures(1, &icon_directories);
    glDeleteTextures(1, &icon_settings);

    glDeleteTextures(1, &icon_folder);
    glDeleteTextures(1, &icon_musicFile);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    std::cout << "Successfully shutdown Renderer" << std::endl;
}
#include <imgui.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "UI.h"
#include "../image/Image.h"

#include <iostream>

static const float SIDEBAR_WIDTH  = 200.0f;
static const float PLAYING_HEIGHT = 200.0f;

UI::UI(Directories& directories)
    : m_directories(directories), m_songsUI(directories), m_directoriesUI(directories)
{} // basically a init

UI::~UI()
{
    
    glDeleteTextures(1, &m_homeIcon);
    //glDeleteTextures(1, &m_songsIcon);
}

void UI::createTextures() // Called in App.cpp after the renderer is initiated, not very clean but good enough for now
{
    m_homeIcon = loadTexture("assets/images/home.png");
    //m_songsIcon = loadTexture("assets/images/audio-lines.png");
}

void UI::render()
{
    renderDockspace();
    renderSidebar();
    renderContents();
    renderPlaying();
}

void UI::renderSidebar()
{
  ImGuiViewport* viewport = ImGui::GetMainViewport();

  ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x, viewport->WorkPos.y));
  ImGui::SetNextWindowSize(ImVec2(SIDEBAR_WIDTH, viewport->WorkSize.y));

  ImGuiWindowFlags flags =
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoCollapse;


  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("Sidebar", nullptr, flags);
    
  ImGui::BeginChild("##sidebar", ImVec2(200, 0), true);
      //if (ImGui::Selectable("Home", m_activeTab == ActiveTab::Home)) m_activeTab = ActiveTab::Home;

      // Temporary test draw for home icon
      ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 20.0f); // leave room for icon
      if (ImGui::Selectable("Home", m_activeTab == ActiveTab::Home))
          m_activeTab = ActiveTab::Home;
      ImGui::SameLine(8.0f); // go back and draw icon, i dont even know tbh
      ImGui::Image((ImTextureID)(uintptr_t)m_homeIcon, ImVec2(16, 16));

      if (ImGui::Selectable("Songs", m_activeTab == ActiveTab::Songs)) m_activeTab = ActiveTab::Songs;
      if (ImGui::Selectable("Library", m_activeTab == ActiveTab::Library)) m_activeTab = ActiveTab::Library;
      if (ImGui::Selectable("Directories", m_activeTab == ActiveTab::Directories)) m_activeTab = ActiveTab::Directories;

      ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 24);
      if (ImGui::Selectable("Settings", m_activeTab == ActiveTab::Settings)) m_activeTab = ActiveTab::Settings;
  ImGui::EndChild();

  ImGui::PopStyleVar();  
  ImGui::End();
}

void UI::renderContents()
{
  ImGuiViewport* viewport = ImGui::GetMainViewport();

  ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + 200.0f, 0));
  ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x - 200.0f,viewport->WorkSize.y - 200.0f /*PLAYIING_HEIGHT*/));

  ImGuiWindowFlags flags =
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoCollapse;


  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));
  ImGui::Begin("Contents", nullptr, flags);
  ImGui::PopStyleVar();

  switch (m_activeTab)
  {
      case ActiveTab::Home:
          // draw home
          ImGui::Text("Hardcoded text, no real contents");
          break;
      case ActiveTab::Songs:
          // draw songs
          m_songsUI.render();
          break;
      case ActiveTab::Library:
          // draw library
          ImGui::Text("Hardcoded text, no real contents");
          break;
      case ActiveTab::Directories:
          // draw directories
          m_directoriesUI.render();
          break;
      case ActiveTab::Settings:
          // draw settings
          ImGui::Text("Hardcoded text, no real contents");
          break;
  }
  ImGui::End();
}

void UI::renderPlaying()
{
  ImGuiViewport* viewport = ImGui::GetMainViewport();

  ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + 200.0f, viewport->WorkSize.y - 200));
  ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x - 200.0f,PLAYING_HEIGHT));

  ImGuiWindowFlags flags =
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoCollapse;


  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("Playing", nullptr, flags);
  ImGui::PopStyleVar();

  ImGui::Text("No songs playing. (hardcoded, potentially shoould be hidden)");

  ImGui::End();
}

void UI::renderDockspace()
{
  ImGuiViewport* viewport = ImGui::GetMainViewport();

  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);

  ImGuiWindowFlags flags =
    ImGuiWindowFlags_NoDocking |
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoBringToFrontOnFocus |
    ImGuiWindowFlags_NoNavFocus |
    ImGuiWindowFlags_NoBackground;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("Dockspace", nullptr, flags);
  ImGui::PopStyleVar();

  ImGui::DockSpace(ImGui::GetID("MyDockspace"));

  ImGui::End();
}

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
{}

UI::~UI()
{
    
    glDeleteTextures(1, &m_homeIcon);
    glDeleteTextures(1, &m_songsIcon);
    glDeleteTextures(1, &m_libraryIcon);
    glDeleteTextures(1, &m_directoriesIcon);
    glDeleteTextures(1, &m_settingsIcon);
}

void UI::createTextures() // Called in App.cpp after the renderer is initiated, not very clean but good enough for now
{
    m_homeIcon = loadTexture("assets/images/home.png");
    m_songsIcon = loadTexture("assets/images/audio-lines.png");
    m_libraryIcon = loadTexture("assets/images/library-big.png");
    m_directoriesIcon = loadTexture("assets/images/folder-open.png");
    m_settingsIcon = loadTexture("assets/images/settings.png");
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
      // Variable to adjust selectable size
      float SELECTABLE_SIZE = 24.0f;
      // Variable to adjust how much to offset the icons to the right by
      float ICON_OFFSET = 7.5f;

      // Home Selectable
      if (ImGui::Selectable("##Home", m_activeTab == ActiveTab::Home,ImGuiWindowFlags_None,ImVec2(0,SELECTABLE_SIZE)))
          m_activeTab = ActiveTab::Home;
      ImGui::SameLine(ICON_OFFSET);
      ImGui::Image((ImTextureID)(uintptr_t)m_homeIcon, ImVec2(SELECTABLE_SIZE, SELECTABLE_SIZE));
      ImGui::SameLine();
      ImGui::Text("Home");

      // Songs Selectable
      if (ImGui::Selectable("##Songs", m_activeTab == ActiveTab::Songs,ImGuiWindowFlags_None,ImVec2(0,SELECTABLE_SIZE)))
          m_activeTab = ActiveTab::Songs;
      ImGui::SameLine(ICON_OFFSET);
      ImGui::Image((ImTextureID)(uintptr_t)m_songsIcon, ImVec2(SELECTABLE_SIZE, SELECTABLE_SIZE));
      ImGui::SameLine();
      ImGui::Text("Songs");

      // Library Selectable
      if (ImGui::Selectable("##Library", m_activeTab == ActiveTab::Library,ImGuiWindowFlags_None,ImVec2(0,SELECTABLE_SIZE)))
          m_activeTab = ActiveTab::Library;
      ImGui::SameLine(ICON_OFFSET);
      ImGui::Image((ImTextureID)(uintptr_t)m_libraryIcon, ImVec2(SELECTABLE_SIZE, SELECTABLE_SIZE));
      ImGui::SameLine();
      ImGui::Text("Library");

      // Library Selectable
      if (ImGui::Selectable("##Directories", m_activeTab == ActiveTab::Directories,ImGuiWindowFlags_None,ImVec2(0,SELECTABLE_SIZE)))
          m_activeTab = ActiveTab::Directories;
      ImGui::SameLine(ICON_OFFSET);
      ImGui::Image((ImTextureID)(uintptr_t)m_directoriesIcon, ImVec2(SELECTABLE_SIZE, SELECTABLE_SIZE));
      ImGui::SameLine();
      ImGui::Text("Directories");
      

      ImGui::SetCursorPosY(ImGui::GetWindowHeight() - SELECTABLE_SIZE); // Personally think it looks a little weird this way but whatever
 
      if (ImGui::Selectable("##Settings", m_activeTab == ActiveTab::Settings,ImGuiWindowFlags_None,ImVec2(0,SELECTABLE_SIZE)))
          m_activeTab = ActiveTab::Settings;
      ImGui::SameLine(ICON_OFFSET);
      ImGui::Image((ImTextureID)(uintptr_t)m_settingsIcon, ImVec2(SELECTABLE_SIZE, SELECTABLE_SIZE));
      ImGui::SameLine();
      ImGui::Text("Settings");

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

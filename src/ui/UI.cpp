#include <imgui.h>

#include "UI.h"

static const float SIDEBAR_WIDTH  = 200.0f;
static const float PLAYING_HEIGHT = 200.0f;

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
      if (ImGui::Selectable("Home", m_activeTab == ActiveTab::Home)) m_activeTab = ActiveTab::Home;

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
          break;
      case ActiveTab::Songs:
          // draw songs
          break;
      case ActiveTab::Library:
          // draw library
          break;
      case ActiveTab::Directories:
          // draw directories
          m_directories.render();
          break;
      case ActiveTab::Settings:
          // draw settings
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

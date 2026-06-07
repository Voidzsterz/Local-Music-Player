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
          break;
      case ActiveTab::Settings:
          // draw settings
          break;
  }
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
  // get the main viewport — this represents the entire application window
  ImGuiViewport* viewport = ImGui::GetMainViewport();

  // position and size the next window to cover the entire application window
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);

  // flags that make the window invisible and non-interactive
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

  // create the actual dockspace inside this invisible window
  // everything else will dock into this
  ImGui::DockSpace(ImGui::GetID("MyDockspace"));

  ImGui::End();
}

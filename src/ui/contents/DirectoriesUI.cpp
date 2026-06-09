#include "imgui.h"
#include "DirectoriesUI.h"

// Potentially temporary variables to store the padding created in UI.cpp's renderContents() function
// Easier to read this way

static const float WINDOW_PADDING = 5.0f;
// static const float BUTTON_PADDING = 8.0f; 

// TEMPORARY DEBUGGING PATH, ENTER YOUR OWN DESIRED DIRECTORY
// This is a path on Linux, Windows would be something like "C:\\Users\\UserHere\\Music", not quite sure though
static const std::string TEST_DIR = "/home/UserHere/Music/";

void DirectoriesUI::render()
{
  // Top buttons
  ImGui::Button("Rescan Directories");

  ImGui::SameLine();

  // Push green button style
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.5f, 0.1f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f,0.75f,0.1f,1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f,0.65f,0.1f,1.0f));


  if (ImGui::Button("Create"))
  {
    // For now temporarily, use the test directory
    m_directories.addDirectory(TEST_DIR);
  }
  ImGui::PopStyleColor(3);

  ImGui::SameLine();

  // Push red button style
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.1f, 0.1f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.75f,0.1f,0.1f,1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.65f,0.1f,0.1f,1.0f));

  if (ImGui::Button("Remove"))
  {
    // TODO: Check the currently selected button and remove it
    // For now temporarily, use the test directory
    m_directories.removeDirectory(TEST_DIR);
  }

  ImGui::SameLine();

  // manageDirWidth gets the buttons "width" before it is created
  float manageDirWidth = ImGui::CalcTextSize("Manage directories here").x;

  // clearButtonWidth gets the buttons "width" before it is created
  float clearButtonWidth = ImGui::CalcTextSize("Clear all Directories").x + ImGui::GetStyle().FramePadding.x * 2; 

  // The code below calculates where to place the "Manage directories here" text (i love working on random useless things)
  float clearButtonStart = ImGui::GetWindowWidth() - clearButtonWidth - WINDOW_PADDING;

  // CursorPosX stays the same even after creating the "Remove" button, so we can do this
  float centerPos = (ImGui::GetCursorPosX() + clearButtonStart) / 2.0f - (manageDirWidth / 2.0f);

  ImGui::SetCursorPosX(centerPos);
  ImGui::Text("Manage directories here");

  ImGui::SameLine();

  ImGui::SetCursorPosX(ImGui::GetWindowWidth() - clearButtonWidth - WINDOW_PADDING);

  if (ImGui::Button("Clear all Directories"))
  {
    m_directories.clearDirectories();
  }
  
  ImGui::PopStyleColor(3);

  // Tables
  // TODO: Potentially add functionality for multi-select using ImGui::BeginMultiSelect()
  // Basic documentation for multi-selecting can be found here: https://github.com/ocornut/imgui/wiki/Multi-Select
  if (ImGui::BeginTable("DirectoriesTable", 1, ImGuiTableFlags_RowBg))
  {
      for (const auto& dir : m_directories.getDirectories())
      {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Selectable(dir.c_str());
      }
      ImGui::EndTable();
  }
}
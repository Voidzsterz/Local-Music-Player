#include "imgui.h"
#include "Directories.h"

void Directories::render()
{
  // Top buttons
  ImGui::Button("Rescan Directories");

  ImGui::SameLine();

  // Push green button style
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.5f, 0.1f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f,0.75f,0.1f,1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f,0.65f,0.1f,1.0f));


  ImGui::Button("Create");
  ImGui::PopStyleColor(3);

  ImGui::SameLine();

  // Push red button style
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.1f, 0.1f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.75f,0.1f,0.1f,1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.65f,0.1f,0.1f,1.0f));

  ImGui::Button("Remove");
  ImGui::SameLine();

  // The "5.0f"s you'll see throughout the code from now on refers to the padding that was pushed in renderContents()
  // I should create a variable for clarity but for now I'll leave it like this

  // manageDirWidth gets the buttons "width" before it is created
  float manageDirWidth = ImGui::CalcTextSize("Manage directories here").x;
  // clearButtonWidth gets the buttons "width" before it is created
  float clearButtonWidth = ImGui::CalcTextSize("Clear all Directories").x + ImGui::GetStyle().FramePadding.x * 2; 

  // The code below calculates where to place the "Manage directories here" text (i love working on random useless things)
  float clearButtonStart = ImGui::GetWindowWidth() - clearButtonWidth - 5.0f;
  // CursorPosX stays the same even after creating the "Remove" button, so we can do this
  float centerPos = (ImGui::GetCursorPosX() + clearButtonStart) / 2.0f - (manageDirWidth / 2.0f);

  ImGui::SetCursorPosX(centerPos);
  ImGui::Text("Manage directories here");
  ImGui::SameLine();

  ImGui::SetCursorPosX(ImGui::GetWindowWidth() - clearButtonWidth - 5.0f);
  ImGui::Button("Clear all Directories");
  ImGui::PopStyleColor(3);

  // Tables
  if (ImGui::BeginTable("DirectoriesTable", 1, ImGuiTableFlags_RowBg))
  {
      // Temporary tables to see how it looks
      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      ImGui::Selectable("path/path/path/1");

      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      ImGui::Selectable("path/path/path/2");

      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      ImGui::Selectable("path/path/path/3");

      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      ImGui::Selectable("path/path/path/4");

      ImGui::EndTable();
  }
}
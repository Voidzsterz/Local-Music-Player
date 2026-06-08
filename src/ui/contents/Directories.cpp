#include "imgui.h"
#include "Directories.h"

void Directories::render()
{
  // Top buttons
  ImGui::Button("Rescan Directories");

  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.6f, 0.1f, 1.0f));
  ImGui::Button("Add");
  ImGui::PopStyleColor();

  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.1f, 0.1f, 1.0f));
  ImGui::Button("Remove");
  ImGui::SameLine();
  ImGui::Text("         Manage directories here."); // temporary lazy method to see how this would look, will look bad if window is scaled
  ImGui::SameLine();

  // buttonWidth gets the buttons "size" before it is created
  float clearButtonWidth = ImGui::CalcTextSize("Clear all Directories").x + ImGui::GetStyle().FramePadding.x * 2; 
  // "5.0f" refers to the padding that was pushed in renderContents(), I should create a variable for clarity but for now I'll leave it like this
  ImGui::SetCursorPosX(ImGui::GetWindowWidth() - clearButtonWidth - 5.0f);

  ImGui::Button("Clear all Directories");
  ImGui::PopStyleColor();
}
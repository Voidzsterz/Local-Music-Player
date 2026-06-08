#include "imgui.h"
#include "Directories.h"

#include <iostream>

void Directories::render()
{
  ImGuiViewport* viewport = ImGui::GetMainViewport();

  ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + 200.0f, 0));
  ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x - 200.0f,viewport->WorkSize.y - 200.0f /*PLAYIING_HEIGHT*/));

  ImGuiWindowFlags flags =
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoCollapse;


  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("Directories", nullptr, flags);
  ImGui::PopStyleVar();

  ImGui::Text("No directories added (hardcoded)");

  ImGui::End();
}
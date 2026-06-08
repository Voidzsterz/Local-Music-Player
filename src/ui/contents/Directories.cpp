#include "imgui.h"
#include "Directories.h"

#include <iostream>

void Directories::render()
{
    std::cout << "iostream" << std::endl;
    ImGui::SetNextWindowSize(ImVec2(0,0));
    ImGui::Begin("Directories");
    ImGui::End();
}
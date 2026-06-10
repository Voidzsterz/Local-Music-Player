#include "imgui.h"
#include "SongsUI.h"

// Potentially temporary variables to store the padding created in UI.cpp's renderContents() function
// Easier to read this way
static const float WINDOW_PADDING = 5.0f;

SongsUI::SongsUI(Directories& directories)
    : m_directories(directories)
{}

void SongsUI::render()
{
    ImGui::Text("Hello World!");
    ImGui::Text("This text is created by SongsUI.cpp");
}
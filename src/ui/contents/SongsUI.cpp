#include "imgui.h"
#include "SongsUI.h"

// Only include renderer to get fonts, not proud of it but I think its acceptable
#include "../../renderer/Renderer.h"

// Potentially temporary variables to store the padding created in UI.cpp's renderContents() function
// Easier to read this way
static const float WINDOW_PADDING = 5.0f;

SongsUI::SongsUI(Renderer& renderer, Directories& directories)
    : m_renderer(renderer), m_directories(directories)
{}

void SongsUI::render()
{
    renderTopbar();
}

void SongsUI::renderTopbar()
{
    ImGui::Text("Find your songs here");
}
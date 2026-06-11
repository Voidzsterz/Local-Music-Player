#include "imgui.h"
#include "SongsUI.h"
#include <iostream>

// Potentially temporary variables to store the padding created in UI.cpp's renderContents() function
// Easier to read this way
static const float WINDOW_PADDING = 5.0f;

SongsUI::SongsUI(Directories& directories)
    : m_directories(directories)
{}

void SongsUI::render()
{
    renderTopbar();

    // Genuinely sorry if this part of the code specifically with the "needs rescan" stuff is confusing, I'll try my best to clean it up soon enough
    if (m_directories.needsRescan())
    {
        m_cachedTrees.clear();
        for (const auto& dir : m_directories.getDirectories())
            m_cachedTrees.push_back(m_directories.scanPath(dir));
        m_directories.clearRescan();
    }

    if (ImGui::BeginTable("SongsTree", 1, ImGuiTableFlags_RowBg))
    {
        for (const auto& root : m_cachedTrees)
            renderTree(root);
        ImGui::EndTable();
    }
}

void SongsUI::renderTopbar()
{
    ImGui::Text("Find your songs here");
}

void SongsUI::renderTree(const PathNode& node)
{
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);

    if (node.isDirectory)
    {
        if (ImGui::TreeNode(node.name.c_str()))
        {
            for (const auto& child : node.children)
            renderTree(child);
            ImGui::TreePop();
        }
    }
    else
    {
        // "%s" prevents it from being a securiy risk, since it'll treat it as a plain string
        ImGui::Text("%s", node.name.c_str());
    }
}
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

    if (m_directories.getDirectories().empty())
    {
        ImGui::PushFont(Renderer::font_soraExtraLight20);
        const char* noDirectoriesMsg = "No directories added. Add one in the Directories tab.";
        ImVec2 textSize = ImGui::CalcTextSize(noDirectoriesMsg);
        ImVec2 windowSize = ImGui::GetWindowSize();

        ImGui::SetCursorPos(ImVec2
        (
            (windowSize.x - textSize.x) / 2.0f,
            (windowSize.y - textSize.y) / 2.0f
        ));
        
        ImGui::Text("%s", noDirectoriesMsg);
        ImGui:ImGui::PopFont();

        return;
    }

    if (m_directories.needsRescan())
    {
        m_cachedTrees.clear();
        m_songItems.clear();

        for (const auto& dir : m_directories.getDirectories())
            m_cachedTrees.push_back(m_directories.scanPath(dir));

        // collectSongs scans the cached tree, so it is necessary to "rescan" here
        int index = 0;
        for (auto& root : m_cachedTrees)
            collectSongs(root, index);

        m_directories.clearRescan();
    }

    // Wrap all the renderTree logic inside a ImGui multi-select
    m_selection.UserData = (void*)&m_songItems;
    m_selection.AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self, int index)
    {
        auto* items = static_cast<std::vector<SongItem>*>(self->UserData);
        return (*items)[index].ID;
    };

    ImGuiMultiSelectIO* multiSelectIO = ImGui::BeginMultiSelect(ImGuiMultiSelectFlags_None, m_selection.Size, m_songItems.size());
    m_selection.ApplyRequests(multiSelectIO);

    if (ImGui::BeginTable("SongsTree", 1, ImGuiTableFlags_RowBg))
    {
        int songIndex = 0;
        for (auto& root : m_cachedTrees)
            renderTree(root, songIndex);
        ImGui::EndTable();
    }

    multiSelectIO = ImGui::EndMultiSelect();
    m_selection.ApplyRequests(multiSelectIO);
}

void SongsUI::renderTopbar()
{
    ImGui::Text("Find your songs here");
}

void SongsUI::renderTree(const PathNode& node, int& songIndex)
{
    // Variable to adjust the node height
    float NODE_HEIGHT = 16.0f;

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);

    if (node.isDirectory)
    {
        if (ImGui::TreeNode(node.name.c_str()))
        {
            for (const auto& child : node.children)
                renderTree(child, songIndex);
            ImGui::TreePop();
        }
    }
    else
    {
        bool selected = m_selection.Contains(m_songItems[songIndex].ID);    

        ImGui::Image((ImTextureID)(uintptr_t)m_renderer.icon_musicFile, ImVec2(NODE_HEIGHT,NODE_HEIGHT));
        ImGui::SameLine();

        ImGui::SetNextItemSelectionUserData(songIndex);
        ImGui::Selectable(node.name.c_str(), selected,ImGuiSelectableFlags_None,ImVec2(0,NODE_HEIGHT));

        songIndex++;
    }
}

void SongsUI::collectSongs(PathNode& node, int& index)
{
    if (!node.isDirectory)
    {
        node.songIndex = index;
        m_songItems.push_back({(ImGuiID)index, node.fullPath.string()});
        index++;
        return;
    }

    for (auto& child : node.children)
        collectSongs(child, index);
}
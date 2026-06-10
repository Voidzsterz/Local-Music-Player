#include "imgui.h"
#include "DirectoriesUI.h"

// Potentially temporary variables to store the padding created in UI.cpp's renderContents() function
// Easier to read this way
static const float WINDOW_PADDING = 5.0f;

DirectoriesUI::DirectoriesUI(Directories& directories)
    : m_directories(directories)
{}

void DirectoriesUI::render()
{
    renderTopButtons();
    renderTable();
}

void DirectoriesUI::renderTopButtons()
{
    // Push green button style
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.0f,0));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.5f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f,0.75f,0.1f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f,0.65f,0.1f,1.0f));


    if (ImGui::Button("Create"))
    {
        // For now temporarily, use the test directory
        m_directories.promptDirectorySelect();
        m_items.clear(); // Clear items so they repopulate (refresh) next frame
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();

    // Push red button style
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.75f,0.1f,0.1f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.65f,0.1f,0.1f,1.0f));

    if (ImGui::Button("Remove"))
    {
        for (const auto& item : m_items)
        {
            if (m_selection.Contains(item.ID))
            {
                m_directories.removeDirectory(item.path);
            }
        }
        m_items.clear(); // Clear items so they repopulate (refresh) next frame
    }

    ImGui::SameLine();

    // manageDirWidth gets the buttons "width" before it is created
    float manageDirWidth = ImGui::CalcTextSize("Manage directories here").x;

    // clearButtonWidth gets the buttons "width" before it is created
    float clearButtonWidth = ImGui::CalcTextSize("Clear Directories").x + ImGui::GetStyle().FramePadding.x * 2; 

    // The code below calculates where to place the "Manage directories here" text (i love working on random useless things)
    float clearButtonStart = ImGui::GetWindowWidth() - clearButtonWidth - WINDOW_PADDING;

    // CursorPosX stays the same even after creating the "Remove" button, so we can do this
    float centerPos = (ImGui::GetCursorPosX() + clearButtonStart) / 2.0f - (manageDirWidth / 2.0f);

    ImGui::SetCursorPosX(centerPos);
    ImGui::Text("Manage directories here");

    ImGui::SameLine();

    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - clearButtonWidth - WINDOW_PADDING);
    if (ImGui::Button("Clear Directories"))
    {
        m_directories.clearDirectories();
        m_items.clear(); // Clear items so they repopulate (refresh) next frame
    }

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();
}

void DirectoriesUI::renderTable()
{
    // Basic documentation for multi-selecting can be found here: https://github.com/ocornut/imgui/wiki/Multi-Select
    const std::vector<std::filesystem::path>& directoryList = m_directories.getDirectories();

    // Gives a unique ID to each directory in the list
    if (m_items.empty())
    {
        ImGuiID id = 0;
        for (const auto& dir : directoryList)
        {
            m_items.push_back({id++, dir.string()});
        }
    }

    m_selection.UserData = (void*)&m_items;
    m_selection.AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self, int index)
    {
        auto* item_array = static_cast<std::vector<DirectoryItem>*>(self->UserData);
        return (*item_array)[index].ID;
    };

    // Begin multi-select
    ImGuiMultiSelectIO* multiSelectIO = ImGui::BeginMultiSelect(ImGuiMultiSelectFlags_None, m_selection.Size, m_items.size());
    m_selection.ApplyRequests(multiSelectIO);
    
    // Creation of the table
    if (ImGui::BeginTable("DirectoriesTable", 1, ImGuiTableFlags_RowBg))
    {
        for (int index = 0; index < m_items.size(); index++)
        {
            bool item_is_selected = m_selection.Contains(m_items[index].ID);
            ImGui::SetNextItemSelectionUserData(index);
            
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Selectable(m_items[index].path.c_str(), item_is_selected);
        }
        ImGui::EndTable();
    }

    multiSelectIO = ImGui::EndMultiSelect();
    m_selection.ApplyRequests(multiSelectIO);
}
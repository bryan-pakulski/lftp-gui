#pragma once

#include <imgui.h>
#include <imgui_stdlib.h>
#include "imgui_internal.h"
#include <filesystem>
#include <string>

#include "Display/ErrorHandler.h"
#include "Helpers/QLogger.h"
#include "Helpers/States.h"
#include "Config/Config.h"

#include "Display/QDisplay_Base.h"

// Simple storage to output a dummy file-system.
struct FileTreeNode {
  const char *Name;
  const char *Type;
  int Size;
  int ChildIdx;
  int ChildCount;

  static void displayNode(const FileTreeNode *node, const FileTreeNode *all_nodes) {
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    const bool is_folder = (node->ChildCount > 0);
    if (is_folder) {
      bool open = ImGui::TreeNodeEx(node->Name, ImGuiTreeNodeFlags_SpanFullWidth);
      ImGui::TableNextColumn();
      ImGui::TextDisabled("--");
      ImGui::TableNextColumn();
      ImGui::TextUnformatted(node->Type);
      if (open) {
        for (int child_n = 0; child_n < node->ChildCount; child_n++)
          displayNode(&all_nodes[node->ChildIdx + child_n], all_nodes);
        ImGui::TreePop();
      }
    } else {
      ImGui::TreeNodeEx(node->Name, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet |
                                        ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth);
      ImGui::TableNextColumn();
      ImGui::Text("%d", node->Size);
      ImGui::TableNextColumn();
      ImGui::TextUnformatted(node->Type);
    }
  }
};

class QDisplay_LocalBrowser : public QDisplay_Base {

public:
  // Initialise render manager references
  QDisplay_LocalBrowser(GLFWwindow *w) : QDisplay_Base(w) {
    m_windowName = "local_browser";

    // Initialise content browser
    m_current_directory = std::filesystem::path(c_base_content_directory);
  }

  void TreeViewPanel() {

    ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Reorderable |
                            ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders;

    // Show files / folders in current working directory
    if (ImGui::BeginTable("local", COLUMNS_COUNT, flags)) {
      ImGui::TableSetupColumn("Filename");
      ImGui::TableSetupColumn("Size");
      ImGui::TableSetupColumn("Type");

      // We can right click to sort and order our filesystem table
      ImGui::TableHeadersRow();

      for (auto &directoryEntry : std::filesystem::directory_iterator(m_current_directory)) {
        const auto &path = directoryEntry.path();

        std::string filenameString = path.filename().string();
        std::string fileType;
        std::string fileSize;

        if (directoryEntry.is_directory()) {
          fileType = "Folder";
          fileSize = "-";
        } else {
          fileType = "File";
          fileSize = "-";
        }

        ImGui::TableNextRow();

        ImGui::TableNextColumn();
        ImGui::Selectable(filenameString.data(), false, ImGuiSelectableFlags_SpanAllColumns);
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
          if (directoryEntry.is_directory()) {
            m_current_directory = path;
          }
        }
        ImGui::TableNextColumn();
        ImGui::Text("%s", fileSize.data());
        ImGui::TableNextColumn();
        ImGui::Text("%s", fileType.data());
      }

      ImGui::EndTable();
    }
  }

  virtual void render() {
    m_window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
    ImGui::SetNextWindowClass(&m_window_class);
    ImGui::Begin(m_windowName.c_str());

    { // Toolbar
      ImGui::Text("Local | ");
      ImGui::SameLine();

      if (ImGui::Button("<-")) {
        if (m_current_directory != std::filesystem::path("/")) {
          m_current_directory = m_current_directory.parent_path();
        }
      }
      ImGui::SameLine();

      if (ImGui::Button("New Folder")) {
        // TODO: Create new folder
      }
    }
    ImGui::Separator();

    TreeViewPanel();

    ImGui::End();
  }

private:
  // Content Browser Config
  const char *c_base_content_directory = "/";
  std::filesystem::path m_current_directory;
  std::filesystem::path m_selected_file;

  const int COLUMNS_COUNT = 3;
};

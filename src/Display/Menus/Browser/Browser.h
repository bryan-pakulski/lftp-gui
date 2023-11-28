#pragma once

#include <fstream>
#include <imgui.h>
#include "imgui_internal.h"
#include <filesystem>
#include <memory>

#include "Helpers/States.h"
#include "Display/ErrorHandler.h"
#include "Helpers/QLogger.h"
#include "Config/Config.h"

#include "Display/QDisplay_Base.h"
#include "LocalBrowser.h"
#include "RemoteBrowser.h"

class QDisplay_Browser : public QDisplay_Base {

public:
  // Initialise render manager references
  QDisplay_Browser(GLFWwindow *w) : QDisplay_Base(w) {

    // Initialise sub menus
    m_localBrowserWindow = std::unique_ptr<QDisplay_LocalBrowser>(new QDisplay_LocalBrowser(w));
    m_remoteBrowserWindow = std::unique_ptr<QDisplay_RemoteBrowser>(new QDisplay_RemoteBrowser(w));

    // Set drag drop callback
    glfwSetDropCallback(w, drop_callback);
  }

  // Drag Drop callback
  static void drop_callback(GLFWwindow *window, int count, const char **paths) {
    // TODO: do something with drag/drop operations
  }

  void update_dock() {
    browser_panel = ImGui::GetID(c_dockName.c_str());

    dock_size.x = m_windowSize.first;
    dock_size.y = m_windowSize.second;

    ImGui::DockBuilderSetNodeSize(browser_panel, dock_size);
    ImGui::DockBuilderSetNodePos(browser_panel, dock_pos);
    ImGui::DockBuilderFinish(browser_panel);
  }

  void dock_init() {

    // Create main dock node
    browser_panel = ImGui::GetID(c_dockName.c_str());

    ImGui::DockBuilderRemoveNode(browser_panel); // Clear any preexisting layouts associated with the ID we just chose
    ImGui::DockBuilderAddNode(browser_panel);    // Create a new dock node to use

    dock_size.y = m_windowSize.second;

    ImGui::DockBuilderSetNodeSize(browser_panel, dock_size);
    ImGui::DockBuilderSetNodePos(browser_panel, dock_pos);

    ImGuiID local_browser = ImGui::DockBuilderSplitNode(browser_panel, ImGuiDir_Left, 0.5f, nullptr, &browser_panel);
    ImGuiID remote_browser = ImGui::DockBuilderSplitNode(local_browser, ImGuiDir_Right, 0.5f, nullptr, &local_browser);

    ImGui::DockBuilderDockWindow(m_localBrowserWindow->m_windowName.c_str(), local_browser);
    ImGui::DockBuilderDockWindow(m_remoteBrowserWindow->m_windowName.c_str(), remote_browser);

    ImGui::DockBuilderFinish(browser_panel);

    m_dock_init = false;
  }

  virtual void render() {
    getWindowSize(m_windowSize);

    if (m_dock_init) {
      dock_init();
    }

    m_localBrowserWindow->render();
    m_remoteBrowserWindow->render();

    update_dock();
  }

private:
  std::unique_ptr<QDisplay_LocalBrowser> m_localBrowserWindow;
  std::unique_ptr<QDisplay_RemoteBrowser> m_remoteBrowserWindow;

  std::pair<int, int> m_windowSize{};

  const std::string c_dockName = "browser";
  ImGuiID browser_panel;
  ImVec2 dock_pos{0, CONFIG::IMGUI_TASKBAR_HEIGHT_OFFSET.get()};
  ImVec2 dock_size{(float)CONFIG::WINDOW_WIDTH.get(),
                   (float)CONFIG::WINDOW_HEIGHT.get() - CONFIG::IMGUI_TASKBAR_HEIGHT_OFFSET.get()};
  bool m_dock_init = true;
};
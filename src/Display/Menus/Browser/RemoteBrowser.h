#pragma once

#include <imgui.h>
#include <imgui_stdlib.h>
#include "LFTPHandler.h"
#include "imgui_internal.h"
#include <filesystem>

#include "Display/ErrorHandler.h"
#include "Helpers/QLogger.h"
#include "Helpers/States.h"
#include "Config/Config.h"
#include "Display/QDisplay_Base.h"

class QDisplay_RemoteBrowser : public QDisplay_Base {

public:
  // Initialise render manager references
  QDisplay_RemoteBrowser(GLFWwindow *w) : QDisplay_Base(w) { m_windowName = "remote_browser"; }

  virtual void render() {
    m_window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
    ImGui::SetNextWindowClass(&m_window_class);
    ImGui::Begin(m_windowName.c_str());

    ImGui::Text("Remote");
    ImGui::Separator();

    ImGui::End();
  }

private:
};

#pragma once

#include "Display/ErrorHandler.h"
#include "Helpers/QLogger.h"
#include "Config/Config.h"
#include "Display/QDisplay_Base.h"
#include "Helpers/States.h"
#include "LFTPHandler.h"
#include "imgui.h"

class QDisplay_ContextMenu : public QDisplay_Base {
public:
  // Initialise render manager reference
  QDisplay_ContextMenu(GLFWwindow *w) : QDisplay_Base(w) {}

  virtual void render() {
    if (ImGui::BeginPopup("context menu")) {
      {

        if (ImGui::Selectable("Upload")) {
          // TODO: upload selected file
        }

        if (ImGui::Selectable("Delete")) {
          std::cout << LFTPHandler::GetInstance().getActiveFile() << std::endl;
        }

        ImGui::EndPopup();
        LFTPHandler::GetInstance().setContextWindowVisible(false);
      }
    }

    setPopup();
  }

  void setPopup() {
    if (LFTPHandler::GetInstance().contextWindowVisible()) {
      ImGui::OpenPopup("context menu");
    }
  }
};

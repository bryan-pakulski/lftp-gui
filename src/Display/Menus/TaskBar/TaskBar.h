#pragma once

#include "Helpers/GL/GLImage.h"
#include "Helpers/States.h"
#include "LFTPHandler.h"
#include "Config/Config.h"
#include "Helpers/QLogger.h"
#include "Helpers/GL/GLHelper.h"
#include "Display/ErrorHandler.h"
#include "Display/QDisplay_Base.h"

#include <imgui.h>
#include <imgui_stdlib.h>

class QDisplay_TaskBar : public QDisplay_Base {
public:
  QDisplay_TaskBar(GLFWwindow *w);

  virtual void render();

private:
  // Window triggers
  bool m_logFileOpen = false;
  bool m_connectPopup = false;

  // Connection status icons
  std::unique_ptr<GLImage> m_connected_icon;
  std::unique_ptr<GLImage> m_connecting_icon;
  std::unique_ptr<GLImage> m_disconnected_icon;
  std::unique_ptr<GLImage> m_timeout_icon;

  GLImage m_icon;
  std::string m_connString;
  float c_iconSize = 15.0f;

  // Log config
  std::ifstream logStream;
  std::stringstream logFileBuffer;
  bool logUpdated = true;
  clock_t lastLogReadTime;

private:
  void QDisplay_LogFile();
  void QDisplay_ConnectModal();
};
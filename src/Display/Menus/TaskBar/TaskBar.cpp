#include "TaskBar.h"

QDisplay_TaskBar::QDisplay_TaskBar(GLFWwindow *w) : QDisplay_Base(w) {

  // Load images
  m_connected_icon = std::unique_ptr<GLImage>(new GLImage(32, 32, "connected_icon"));
  m_disconnected_icon = std::unique_ptr<GLImage>(new GLImage(32, 32, "disconnected_icon"));
  m_connecting_icon = std::unique_ptr<GLImage>(new GLImage(32, 32, "connecting_icon"));
  m_timeout_icon = std::unique_ptr<GLImage>(new GLImage(32, 32, "timeout_icon"));

  m_connected_icon->loadFromImage("data/images/connected.png");
  m_disconnected_icon->loadFromImage("data/images/disconnected.png");
  m_connecting_icon->loadFromImage("data/images/connecting.png");
  m_timeout_icon->loadFromImage("data/images/timeout.png");

  m_icon = *m_disconnected_icon;
}

void QDisplay_TaskBar::render() {
  if (ImGui::BeginMainMenuBar()) {

    if (ImGui::BeginMenu("File")) {

      if (ImGui::MenuItem("Connect To Server")) {
        ImGui::OpenPopup("CONNECT");
        m_connectPopup = true;
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Debug")) {

      if (ImGui::MenuItem("Open Log")) {
        m_logFileOpen = true;
      }

      ImGui::EndMenu();
    }

    // Docker connection state
    ImGui::Separator();
    {

      int state = LFTPHandler::GetInstance().getConnectionState();
      switch (state) {
      case Q_CONNECTION_STATE::CONNECTED:
        m_icon = *m_connected_icon;
        m_connString = "Connected";
      case Q_CONNECTION_STATE::PENDING:
        m_icon = *m_disconnected_icon;
        m_connString = "Not Connected";
      case Q_CONNECTION_STATE::CONNECTING:
        m_icon = *m_connecting_icon;
        m_connString = "Connecting";
      case Q_CONNECTION_STATE::TIMEOUT:
        m_icon = *m_timeout_icon;
        m_connString = "Timed Out";
      default:
        m_icon = *m_disconnected_icon;
        m_connString = "Not Connected";
      }

      ImGui::Image((void *)(intptr_t)m_icon.m_texture, {c_iconSize, c_iconSize}, {1, 0}, {0, 1});
      ImGui::MenuItem(m_connString.c_str());
    }

    ImGui::EndMainMenuBar();
  }

  // These will only render if their corresponding flags are set
  QDisplay_LogFile();
}

void QDisplay_TaskBar::QDisplay_ConnectModal() {
  if (m_connectPopup) {
    ImGui::SetNextWindowSize(ImVec2(480.0f, 260.0f));

    if (ImGui::BeginPopupModal("CONNECT", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {

      auto windowWidth = ImGui::GetWindowSize().x;
      ImGui::SetCursorPosX(((windowWidth)*0.5f) - (150.0f / 2.0f));
      if (ImGui::Button("Okay", ImVec2(150, 40))) {
        m_connectPopup = false;
      }
      ImGui::EndPopup();
    }
  }
}

void QDisplay_TaskBar::QDisplay_LogFile() {

  if (m_logFileOpen) {
    ImGui::SetNextWindowBgAlpha(0.9f);
    ImGui::Begin("Log");

    if (ImGui::Button("Close")) {
      m_logFileOpen = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Clear")) {
      logStream.close();
      QLogger::GetInstance().resetLog();
    }

    ImGui::Separator();

    ImGui::BeginChild("ScrollingLog");

    // Only update text if required
    if (QLogger::GetInstance().m_LAST_WRITE_TIME != lastLogReadTime) {
      logStream.open(CONFIG::LOG_FILE.get(), std::ios::in);

      logFileBuffer.clear();
      logFileBuffer.str(std::string());

      lastLogReadTime = QLogger::GetInstance().m_LAST_WRITE_TIME;
      logFileBuffer << logStream.rdbuf();
      logStream.close();
      logUpdated = true;
    }

    // ImGui::TextWrapped("%s", logFileBuffer.str().c_str());
    ImGui::TextUnformatted(logFileBuffer.str().c_str());

    // Move to bottom of screen
    if (logUpdated) {
      ImGui::SetScrollY(ImGui::GetScrollMaxY() + ImGui::GetStyle().ItemSpacing.y * 2);
      logUpdated = false;
    }
    ImGui::EndChild();

    ImGui::End();
  }
}
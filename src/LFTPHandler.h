#pragma once

#include "Helpers/States.h"

#include <filesystem>
#include <memory>
#include <thread>
#include <vector>

struct contentAction {
  int panel;
};

class LFTPHandler {
public:
public:
  static LFTPHandler &GetInstance() {
    static LFTPHandler s_lftpHandler;
    return s_lftpHandler;
  }

  // Prohibit external replication constructs
  LFTPHandler(LFTPHandler const &) = delete;
  // Prohibit external assignment operations
  void operator=(LFTPHandler const &) = delete;

  // Main update loop
  void update() {}

  int getConnectionState() { return m_connectionState; }
  void setConnectionState(int state) { m_connectionState = state; }

  void setActiveFile(const std::filesystem::path &filepath) { m_activeFilePath = filepath; }
  std::filesystem::path getActiveFile() { return m_activeFilePath; }
  void setContextWindowVisible(bool visible) { m_contextWindowVisible = visible; }
  bool contextWindowVisible() { return m_contextWindowVisible; }

private:
  int m_connectionState = Q_CONNECTION_STATE::DISCONNECTED;
  bool m_contextWindowVisible = false;
  std::thread m_Thread;

  std::filesystem::path m_activeFilePath;

private:
  explicit LFTPHandler();
  ~LFTPHandler();
};
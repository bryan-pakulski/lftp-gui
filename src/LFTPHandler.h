#pragma once

#include "Helpers/States.h"

#include <memory>
#include <thread>
#include <vector>

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

private:
  int m_connectionState = Q_CONNECTION_STATE::DISCONNECTED;
  std::thread m_Thread;

private:
  explicit LFTPHandler();
  ~LFTPHandler();
};
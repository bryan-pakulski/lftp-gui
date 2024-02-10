#include "LFTPHandler.h"
#include "Helpers/QLogger.h"
#include <format>

LFTPHandler::LFTPHandler() {
  QLogger::GetInstance().Log(LOGLEVEL::TRACE, "LFTPHandler::LFTPHandler");
  lftp.SendCommand("help");
}

LFTPHandler::~LFTPHandler() {}

bool LFTPHandler::connect(const std::string &host, const std::string &user, const std::string &pwd) {
  std::string connect = lftp.SendCommand(std::format("lftp {}:{}@{}", user, pwd, host));

  std::cout << connect << std::endl;

  return true;
}
#include "LFTPHandler.h"
#include "Helpers/QLogger.h"
#include <format>

LFTPHandler::LFTPHandler() {
  QLogger::GetInstance().Log(LOGLEVEL::TRACE, "LFTPHandler::LFTPHandler");
  lftp.SendCommand("help");
}

LFTPHandler::~LFTPHandler() {}

bool LFTPHandler::connect(const std::string &host, const std::string &user, const std::string &pwd) {
  std::string connect = lftp.SendCommand(std::format("lftp {}", host));
  std::string login = lftp.SendCommand(std::format("user {} {}", user, pwd));
  std::string ls = lftp.SendCommand("ls");

  std::cout << connect << std::endl;
  std::cout << login << std::endl;
  std::cout << ls << std::endl;

  return true;
}
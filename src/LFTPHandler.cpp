#include "LFTPHandler.h"
#include "Helpers/QLogger.h"

LFTPHandler::LFTPHandler() { QLogger::GetInstance().Log(LOGLEVEL::TRACE, "LFTPHandler::LFTPHandler"); }

LFTPHandler::~LFTPHandler() {}
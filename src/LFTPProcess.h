#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "Helpers/QLogger.h"
#include "Display/ErrorHandler.h"

#define READ_END 0
#define WRITE_END 1

class LftpProcess {
private:
  int in_fd[2];  // Input pipe file descriptors ( 0: read , 1: write )
  int out_fd[2]; // Output pipe file descriptors ( 0: read , 1: write )
  pid_t child_pid;

public:
  LftpProcess() {
    if (pipe(in_fd) == -1 || pipe(out_fd) == -1) {
      ErrorHandler::GetInstance().setError("Process Failure", "Failed to create pipe for lftp process!");
      return;
    }

    child_pid = fork();
    if (child_pid == -1) {
      ErrorHandler::GetInstance().setError("Process Failure", "Failed to create child process!");
      return;
    }

    QLogger::GetInstance().Log(LOGLEVEL::TRACE, "lftp child process initialising... pid[", child_pid, "]");
    if (child_pid == 0) {
      childProc();
    } else {
      parentProc();
    }
  }

  void childProc() {
    close(in_fd[WRITE_END]);
    close(out_fd[READ_END]);

    dup2(in_fd[READ_END], STDIN_FILENO);
    dup2(out_fd[WRITE_END], STDOUT_FILENO);

    execl("lftp", "lftp", nullptr);

    QLogger::GetInstance().Log(LOGLEVEL::ERR, "execl error!");
    exit(1);
  }

  void parentProc() {
    close(in_fd[READ_END]);
    close(out_fd[WRITE_END]);

    fcntl(out_fd[READ_END], F_SETFL, fcntl(out_fd[READ_END], F_GETFL) | O_NONBLOCK);
  }

  std::string SendCommand(std::string cmd) {
    QLogger::GetInstance().Log(LOGLEVEL::DBG2, "lftp process: ", child_pid, "SendCommand: ", cmd);

    cmd += "\n";
    write(in_fd[WRITE_END], cmd.c_str(), cmd.size());

    sleep(1);

    return ReadResponse();
  }

  ~LftpProcess() {
    // Send quit command to ftp
    SendCommand("quit");

    int status;
    close(in_fd[WRITE_END]);
    close(out_fd[READ_END]);

    waitpid(child_pid, &status, 0);

    QLogger::GetInstance().Log(LOGLEVEL::TRACE, "killed lftp process: ", child_pid, "with status: ", status);
  }

private:
  std::string ReadResponse() {
    char buffer[256];
    std::string result;

    while (read(out_fd[READ_END], buffer, 255) > 0) {
      buffer[255] = '\0';
      result += buffer;
    }

    QLogger::GetInstance().Log(LOGLEVEL::DBG2, "lftp process: ", child_pid, "ReadResponse: ", result);
    return result;
  }
};
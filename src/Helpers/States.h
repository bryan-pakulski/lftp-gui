#pragma once

// LFTP Connection Status
struct Q_CONNECTION_STATE {
  const static int DISCONNECTED = 0;
  const static int CONNECTING = 1;
  const static int CONNECTED = 2;
  const static int TIMEOUT = 3;
};

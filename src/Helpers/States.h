#pragma once

// LFTP Connection Status
struct Q_CONNECTION_STATE {
  const static int PENDING = 0;
  const static int CONNECTING = 1;
  const static int CONNECTED = 2;
  const static int TIMEOUT = 3;
};

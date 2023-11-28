#!/bin/bash

if [ ! -d "build/lftp-ui-bin" ]; then
    echo "build/lftp-ui-bin directory not present, please build & package the project first"
    exit 1
fi

cd build/lftp-ui-bin
./lftp-ui
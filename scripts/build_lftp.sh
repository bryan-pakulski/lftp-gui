#!/bin/bash

set -e pipefail

if [ ! -d "build/lftp" ]; then
    git clone --depth 1 --branch v4.9.2 https://github.com/lavv17/lftp.git build/lftp
    ./autogen.sh
    ./configure --without-gnutls --with-openssl
fi

pushd build/lftp
    echo "Running LFTP build..."
    make -j $(nproc)
popd

cp -uv build/lftp/src/lftp .
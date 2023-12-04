#!/bin/bash

set -e pipefail

if [ ! -d "src" ]; then
    echo "please run this script from the root directory"
    exit 1
fi

echo "Building lftp-ui..."
mkdir -p build

pushd build
    if [[ $1 == "-r" ]]; then
        echo "Running in release mode..."
        cmake .. -DCMAKE_BUILD_TYPE=Release
    else
        echo "Running in debug mode..."
        cmake .. -DCMAKE_BUILD_TYPE=Debug
    fi

    cmake --build . -- -j $(nproc)
popd


if [ ! -f "lftp" ]; then
    echo "Building lftp..."

    if [ ! -d "build/lftp" ]; then
        git clone --depth 1 --branch v4.9.2 https://github.com/lavv17/lftp.git build/lftp
    fi

    pushd build/lftp
        echo "Running configure for LFTP..."
        ./configure --without-gnutls --with-openssl
        make
    popd

    echo "Done!"
else
    echo "LFTP binary found!"
fi

echo "Packing release..."
bash -c "./scripts/pipeline/package.sh"
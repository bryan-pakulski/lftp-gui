#!/bin/bash

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

echo "Packing release..."
bash -c "./scripts/pipeline/package.sh"
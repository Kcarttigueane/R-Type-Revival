#!/bin/bash

./vcpkg/bootstrap-vcpkg.sh

./vcpkg/vcpkg integrate install
./vcpkg/vcpkg install

if [ -d "build" ]; then
  echo "Build folder exists. Clearing contents..."
  rm -rf build/*
else
  echo "Build folder does not exist. Creating..."
  mkdir build
fi

cd build

# Run cmake
cmake ..

make


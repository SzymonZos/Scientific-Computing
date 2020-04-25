#!/bin/bash

rm -rf build*/

mkdir build-gcc-debug
cd build-gcc-debug
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..
cmake --build . --target all -- -j 8
cd ..

mkdir build-gcc-release
cd build-gcc-release
cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ..
cmake --build . --target all -- -j 8
cd ..

mkdir build-clang-debug
cd build-clang-debug
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/mingw64/bin/clang.exe -DCMAKE_CXX_COMPILER=/mingw64/bin/clang++.exe -G "MinGW Makefiles" ..
cmake --build . --target all -- -j 8
cd ..

mkdir build-clang-release
cd build-clang-release
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=/mingw64/bin/clang.exe -DCMAKE_CXX_COMPILER=/mingw64/bin/clang++.exe -G "MinGW Makefiles" ..
cmake --build . --target all -- -j 8
cd ..

cd ProducerConsumerThreads
./RunAll.sh ./bin "*.exe"

# Scientific-Computing

## Introduction

This repository consists of two main parts:

* Playground for standard library implementation of threads - ```<thread>```
and the implementation of Message Passing Interface - ```MPICH```.
* Simple comparison of producer consumer scheme using different number of
working threads and libraries.

To make life easier simple C++ wrapper around archaic ```MPICH``` C API was
created.

## Description

There are 4 projects and 1 library available. The Reports contain specific
information of build types, timed execution, comparison and conclusions of the
results. It can be found in the following submodules:

* [Basics of C++ threads](BasicCppThreads/Report.md).
* [Basics of MPI library](BasicMpi/Report.md).
* [The producer and consumers scheme using C++
  threads](ProducerConsumer/Threads/Report.md).
* [The producer and consumers scheme using
  MPI](ProducerConsumer/Mpi/Report.md).

## Installation 

### Windows 

As for now, MPI projects were not tested using the most beloved OS ever. 
To run others usage of ```MSYS2``` is recommended. 

1. Follow [this 
guide](https://github.com/orlp/dev-on-windows/wiki/Installing-GCC--&-MSYS2)
to install desired toolchain ```MinGW```. Note that CMake 3.16 comes with great
opportunity to lose developer's mind under Windows. A nice feature that prevents
CMake from working was added there. One **cannot** include *sh.exe* in the path 
or simply use one of newer versions (3.17 was tested and worked quite nice).

2. Using ```MSYS2``` shell execute following commands in the desired directory.
   ```shell script
   git clone https://github.com/SzymonZos/Scientific-Computing.git
   cd Scientific-Computing
   git submodule update --init --recursive
   ```

3. Then run following commands using ```cmd``` from Scientific-Computing dir.
   ```shell script
   mkdir build
   cd build
   cmake -G "MinGW Makefiles" ..
   cmake --build . 
   ```

4. Choose desired built binary and run it.

### Normal operating systems

Run following commands. Note that default system generator, compiler and build
type are chosen in this way. To change this behavior, proceed with standard 
CMake command ```-D```.

```shell script
git clone https://github.com/SzymonZos/Scientific-Computing.git
cd Scientific-Computing
git submodule update --init --recursive
mkdir build
cd build
cmake ..
cmake --build . 
```
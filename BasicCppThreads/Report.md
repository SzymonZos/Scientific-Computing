---
---

# **Basics of C++ threads**

## 0. Given tasks
1. Using a global function, function object, class method, and lambda function create 4 threads that display on the screen information about the thread and an additional text (being an argument passed when creating a thread).

2. Create a global function that prints 50 times (each time on a separate line) the text passed as a function’s argument. Create 20 threads using this function. Using the std::mutex, ensure that messages output by threads is placed in separate lines.

3. Create a function that increments 10,000,000 times a certain global integer variable. Measure the time (using std::chrono) of its one-time execution. Create a vector of 10 threads with this function. Check the time and the effect of these threads on the incremented global variable. Use the \<atomic\> and \<mutex\> to ensure the correct result of the threads. Compare the operation times of the \<atomic\>, \<mutex\> and unsynchronized variants (for the executable compiled in the debug and release configuration).

## 1. Information about hardware
### 1.1. Host operating system
1. Processor:
 * Intel Core i7-9850H
 * Clock Rate - 2.60 GHz
 * Number of physical cores - 6
 * Number of logical processors - 12
2. RAM: 16 GB

### 1.2. Guest operating system
1. Processor:
 * Number of processors - 1
 * Number of cores per processor - 4
2. RAM: 8 GB

## 2. Information about software
### 2.1. Host operating system
1. Operating system: Microsoft Windows 10 Enterprise
2. Virtualization: VMware Workstation 15.5 Pro

### 2.2. Guest operating system
1. Operating system: Manjaro
2. Project type: CMake (version 3.16.5)
3. Toolchain: GNU GCC (version 9.2.1)
4. Build: make \-\- -j 8
5. IDE: CLion

## 3. Source code
Source code is available [there](https://github.com/SzymonZos/Scientific-Computing/blob/master/BasicCppThreads/main.cpp). I believe it is self-explanatory enough.

## 4. Possible output
Due to a **huge** amount of logs possible output is attached [there](Output.md).

## 5. Measured times
|               |**Single thread**| **Mutex** | **Atomic** |
|:-------------:|:---------------:|:---------:|:----------:|
| **Debug**     |       11 m      |  617 ms   |   134 ms   |
| **Release**   |       0 ms      |  388 ms   |   96 ms    |

## 6. Comments and conclusions
For a such trivial operation multi-threading comes with significant overhead especially if it is implemented using mutexes. Due to release build enabling optimization operations are performed faster. Case in the single thread version (0 ms) is connected with compiler cutting off whole loop because of its meaningless.

---
---

# **The producer and consumers scheme**

## 0. Given tasks

1. Write a program, that tests:
 * point-to-point routines MPI_Send() and MPI_Recv() (but use also MPI_ANY_SOURCE for the latter)
 * non-blocking routines MPI_Isend() and MPI_Irecv() (use also MPI_Wait() and MPI_Test())
 * MPI_Barrier()

2. Write a program that finds the number of prime numbers smaller or equal than a given number. For instance, the program should find 78498 primes up to 1000000, 664579 up to 10^7, and 5761455 up to 10^8. Use MPI_Reduce() to sum numbers of primes found by MPI processes. Compare the time of counting prime numbers using various numbers of MPI processes.

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
 * Number of processors - 2
 * Number of cores per processor - 4
2. RAM: 8 GB

## 2. Information about software
### 2.1. Host operating system
1. Operating system: Microsoft Windows 10 Enterprise
2. Virtualization: VMware Workstation 15.5 Pro

### 2.2. Guest operating system
1. Operating system: Manjaro (kernel version 5.6.10)
2. Project type: CMake (version 3.17.2)
3. Toolchain: GNU GCC (version 9.3.0)
4. Build: ```cmake --build . --target all -- -j 8```
5. IDE: CLion
6. MPI distribution: mpich 3.3.2
```
sudo pacman -S yay
yay -S mpich
```

## 3. Source code
Source code is available [there](https://github.com/SzymonZos/Scientific-Computing/tree/master/BasicMpi).

Features:

* Wrapped ugly and unnecessary C API to modern C++ interface.
* Quasi optimized IsPrime() function.
* 2 prime checking methods: loop unrolling (Duff's device style) and MPI messages.

Future improvements:

* Code cleanup

## 4. Input values

1. Demo
* Number of processes = 8

2. Comparison
* Number of processes = 1-8 (due to implementation limit)
* Test values: 1'000'000, 10'000'000, 100'000'000

## 5. Possible output
Due to a **huge** amount of logs possible output is limited to demo version:
```
2^1 = 2
2^5 = 32
2^2 = 4
2^7 = 128
2^3 = 8
2^6 = 64
2^4 = 16
4
16
36
81
121
169
256
324
400
529
625
729
900
1024
1156
1369
1681
1936
2304
2601
3025
1521
...
Test: true got: 2
Test: true got: 14
Test: true got: 16
Test: true got: 6
Test: true got: 8
Test: true got: 10
Test: true got: 30
Test: true got: 22
Test: true got: 44
Test: true got: 36
Test: true got: 58
Test: true got: 50
Test: true got: 72
Test: true got: 64
Test: true got: 86
Test: true got: 78
Test: true got: 100
Test: true got: 92
Test: true got: 114
Test: true got: 106
...
78498
Elapsed time: 0.054 s
Elapsed time: 0.342 s
78498
664579
Elapsed time: 1.281 s
Elapsed time: 3.649 s
664579
5761455
Elapsed time: 31.871 s
Elapsed time: 37.73 s
5761455
```

## 6. Comparison - release
1. 1'000'000
2. 10'000'000
3. 100'000'000

|**Threads**|**Unroll 1**|**Messages 1**|**Unroll 2**|**Messages 2**|**Unroll 3**|**Messages 3**|
|:---------:|:----------:|:------------:|:----------:|:------------:|:----------:|:------------:|
|   **1**   |    0.126   |       -      |    3.172   |       -      |   82.103   |       -      |
|   **2**   |    0.127   |     0.548    |    3.256   |     5.652    |   87.363   |    113.532   |
|   **3**   |    0.068   |     0.346    |    1.741   |     3.601    |   45.685   |    63.27     |
|   **4**   |    0.071   |     0.312    |    1.835   |     3.162    |   48.709   |    47.284    |
|   **5**   |    0.036   |     0.312    |    0.984   |     3.154    |   25.988   |    40.825    |
|   **6**   |    0.096   |     0.333    |    2.077   |     3.225    |   54.909   |    38.065    |
|   **7**   |    0.036   |     0.387    |    0.805   |     3.299    |   19.843   |    38.356    |
|   **8**   |    0.053   |     0.342    |    1.281   |     3.649    |   31.871   |    37.73     |


## 8. Comments and conclusions
* Loop unrolling depends heavily on problem automatic division due to lack of distributing calculations.
* In this trivial example it is better to just unroll loop in most cases.
* Message system shines with huge amount of computations and running threads.

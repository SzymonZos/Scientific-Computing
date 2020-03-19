#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include "Timer.hpp"

#define PRINT_LOG(str) std::cout << (str) << '\n'

#define PRINT_THREAD_INFO(str) \
    std::cout << std::this_thread::get_id() << ": " << (str) << "\n"

static std::mutex g_mutex;
static int g_counter;
static const int g_maxCounterValue = 10000000;
static std::atomic<int> g_atomicCounter;

struct FunctionObject {
    void operator()(std::string&& str) {
        PRINT_THREAD_INFO(str);
    }
};

class Class {
public:
    void Method(std::string&& str) {
        PRINT_THREAD_INFO(str);
    }
};

void GlobalFunction(std::string&& str) {
    PRINT_THREAD_INFO(str);
}

void PrintStrings(std::string&& str) {
    const uint8_t numberOfStrings = 50;
    for (uint8_t i = 0; i < numberOfStrings; i++) {
        std::lock_guard<std::mutex> lock(g_mutex);
        PRINT_THREAD_INFO(str);
    }
}

void IncrementLockedCounter() {
    while (g_counter < g_maxCounterValue) {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_counter++;
    }
}

void IncrementAtomicCounter() {
    while (g_atomicCounter++ < g_maxCounterValue);
}

void SingleThreadCounter() {
    Timer timer;
    while (g_counter++ < g_maxCounterValue);
}

void MultipleThreadsCounter(const std::function<void()>& counter) {
    std::vector<std::thread> threads;
    const uint32_t numberOfThreads = 10;
    threads.reserve(numberOfThreads);
    Timer timer;
    for (uint32_t i = 0; i < numberOfThreads; i++) {
        threads.emplace_back(counter);
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

void FirstTask() {
    std::thread globalFunctionThread{GlobalFunction, "Global function  "};
    std::thread functionObjectThread{FunctionObject(), "Function object  "};
    std::thread classMethodThread{&Class::Method, Class(), "Class method  "};
    std::thread lambdaThread{[=](std::string&& str) {
        PRINT_THREAD_INFO(str);
    }, "Lambda function  "};

    globalFunctionThread.join();
    functionObjectThread.join();
    classMethodThread.join();
    lambdaThread.join();
}

void SecondTask() {
    const uint32_t numberOfThreads = 20;
    std::array<std::thread, numberOfThreads> threads;
    for (uint32_t i = 0; i < numberOfThreads; i++) {
        threads[i] = std::thread{PrintStrings, "Some string  "};
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

void ThirdTask() {
    PRINT_LOG("Single thread counter:  ");
    SingleThreadCounter();
    g_counter = 0;
    PRINT_LOG("Locked multiple threads counter:  ");
    MultipleThreadsCounter(std::cref(IncrementLockedCounter));
    g_counter = 0;
    PRINT_LOG("Atomic multiple threads counter:  ");
    MultipleThreadsCounter(std::cref(IncrementAtomicCounter));
}

int main() {
    PRINT_LOG("--First task--  ");
    FirstTask();
    PRINT_LOG("--Second task--  ");
    SecondTask();
    PRINT_LOG("--Third task--  ");
    ThirdTask();
    return 0;
}

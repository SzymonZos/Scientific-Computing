#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#define PRINT_THREAD_INFO(str) \
    std::cout << std::this_thread::get_id() << ": " << (str) << '\n';

static std::mutex g_mutex;
static int g_counter;
static const int g_maxCounterValue = 10000000;

struct FunctionObject {
    void operator()(const std::string& str) {
        PRINT_THREAD_INFO(str);
    }
};

class Class {
public:
    void Method(const std::string& str) {
        PRINT_THREAD_INFO(str);
    }
};

void GlobalFunction(const std::string& str) {
    PRINT_THREAD_INFO(str);
}

void PrintStrings(const std::string& str) {
    const uint8_t numberOfStrings = 50;
    std::lock_guard<std::mutex> lock(g_mutex);
    for (uint8_t i = 0; i < numberOfStrings; i++) {
        PRINT_THREAD_INFO(str);
    }
}

void IncrementCounter() {
    while (g_counter < g_maxCounterValue) {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_counter++;
    }
}

void FirstTask() {
    std::thread globalFunctionThread{GlobalFunction, "Global function"};
    std::thread functionObjectThread{FunctionObject(), "Function object"};
    std::thread classMethodThread{&Class::Method, Class(), "Class method"};
    std::thread lambdaThread{[=](const std::string& str) {
        PRINT_THREAD_INFO(str);
    }, "Lambda function"};

    globalFunctionThread.join();
    functionObjectThread.join();
    classMethodThread.join();
    lambdaThread.join();
}

void SecondTask() {
    const uint32_t numberOfThreads = 20;
    std::array<std::thread, numberOfThreads> threads;
    for (uint32_t i = 0; i < numberOfThreads; i++) {
        threads[i] = std::thread{PrintStrings, "Some string"};
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

void ThirdTask() {
    std::vector<std::thread> threads;
    const uint32_t numberOfThreads = 10;
    threads.reserve(numberOfThreads);
    for (uint32_t i = 0; i < numberOfThreads; i++) {
        threads.emplace_back(IncrementCounter);
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

int main() {
    FirstTask();
    SecondTask();
    ThirdTask();
    return 0;
}
